import time
import pandas as pd
import numpy as np
import torch
import torch.nn as nn
from torch.nn.modules import Dropout, Linear
from torch.nn.modules.activation import ReLU
from torch.utils.data import DataLoader, TensorDataset
import matplotlib.pyplot as plt
import os

class Accumulator:

    def __init__(self, n):
        self.data = [0.0] * n

    def add(self, *args):
        self.data = [a + float(b) for a, b in zip(self.data, args)]

    def __getitem__(self, idx):
        return self.data[idx]

def get_num_workers():
    return 0

def load_data(train_path, test_path, device):
    train_data = pd.read_csv(train_path)
    test_data = pd.read_csv(test_path)
    # train_data.info()
    # test_data.info() 
    # print(train_data[:3])
    # print(train_data[:3].to_string(max_colwidth=None))
    #price存起来
    train_label = train_data.iloc[:,2]
    #
    train_data = train_data.drop(train_data.columns[2], axis=1) 
    # train_data = train_data.drop(train_data.columns[0], axis=1)
    num_train = train_data.shape[0]
    # test_data = test_data.drop(test_data.columns[0], axis=1)
#    print(train_data.iloc[:4,2])    
    data = pd.concat([train_data, test_data],ignore_index=True)
    data = preprocess_data(data)
    # print(train_data.shape)
    # print(test_data.shape)
    train_data = data.iloc[:num_train,:]
    test_data = data.iloc[num_train:,:]
    # print(train_data.shape)
    # print(test_data.shape)
    
    train_data = torch.tensor(train_data.to_numpy(), dtype=torch.float32).to(device)
    train_label = torch.tensor(train_label.to_numpy(),dtype=torch.float32).to(device)
    test_data = torch.tensor(test_data.to_numpy(), dtype=torch.float32).to(device)
    
    train_label = train_label.view(-1,1)

    train_dataset = TensorDataset(train_data,train_label)
    blank_label = torch.zeros(test_data.shape[0],1)
    test_dataset = TensorDataset(test_data,blank_label)

    return train_dataset, test_dataset

def extract_top(features,data,sep,top_n=30):
    for feature in features:
        exploded = (
            data[['Id', feature]]
            .assign(**{feature: data[feature].str.split(sep)})  # 按sep分割
            .explode(feature)
        )
        exploded[feature] = exploded[feature].str.strip()  # 去除首尾空格
        value_counts = exploded[feature].value_counts()
        top_values = value_counts.head(top_n).index.tolist()
        exploded[feature] = exploded[feature].apply(
            lambda x: x if x in top_values else '0'
        )
        dummies = pd.get_dummies(exploded[feature], prefix=feature)    
        dummies['Id'] = exploded['Id']
        dummies = dummies.groupby('Id',as_index=False).max()
        dummies = dummies.drop('Id',axis=1)
        data = data.drop(feature,axis=1)
        data = pd.concat([data,dummies],axis=1)
        
    return data

def precess_date(data, features):
    for feature in features:
        dates = pd.to_datetime(data[feature], errors='coerce')
        data[f"{feature}_year"] = dates.dt.year.fillna(0).astype(int)
        data[f"{feature}_month"] = dates.dt.month.fillna(0).astype(int)
        data[f"{feature}_day"] = dates.dt.day.fillna(0).astype(int)
        data = data.drop(feature, axis=1)
    return data

def preprocess_data(data):
    # 处理日期特征
    date_features = ['Last Sold On','Listed On']
    #data = data.drop(date_features, axis=1)
    precess_date(data, date_features)

    # 处理数值特征
    numeric_features = data.select_dtypes(exclude=['object']).columns
    numeric_features = numeric_features.drop('Id')
    if len(numeric_features) > 0:
        data[numeric_features] = data[numeric_features].apply(lambda x: (x-x.mean())/x.std())
        data[numeric_features] = data[numeric_features].fillna(0)
    # 处理分类特征
    # data = data.drop('Summary', axis=1)
    feature_listblank = ['Address']
    data = extract_top(feature_listblank,data,' ')
    feature_list = ['Summary','Heating', 'Cooling', 'Parking', 'Bedrooms', 'Flooring', 'Heating features','Cooling features','Appliances included','Laundry features','Parking features']
    data = extract_top(feature_list,data,',')
    categorical_features = data.select_dtypes(include=['object']).columns
    if len(categorical_features) > 0:        
            # data[categorical_features] = pd.Categorical(data[categorical_features]).codes
            # data = data.drop(categorical_features, axis=1)
            data = extract_top(categorical_features,data,'',top_n=20)
    data = data.fillna(0)
    bool_features = data.select_dtypes(include=['bool']).columns
    if len(bool_features) > 0:
        data[bool_features] = data[bool_features].astype(int)
    data = data.drop('Id', axis=1)
    data = data.select_dtypes(include=['float64', 'int64'])
    print(data.shape)
    # print(data.dtypes)
    # non_numeric_cols = data.select_dtypes(exclude=['float64', 'int64','bool']).columns
    # print(non_numeric_cols)
    
    return data

def kaiming_init(net):
    for m in net.modules():
        if isinstance(m,nn.Linear):
            nn.init.kaiming_normal_(m.weight, nonlinearity='relu')

def reset_parameters(net):
    for m in net.modules():
        if isinstance(m, nn.Linear):
            m.reset_parameters()
    
def log_rmse(y_hat, labels):
    loss = nn.MSELoss()
    clipped_preds = y_hat.clamp( min=1e-1 ,max=float('inf'))
    labels = labels.clamp(min=1e-1, max=float('inf'))
    rmse = torch.sqrt(loss(torch.log(clipped_preds),torch.log(labels)))
    return rmse

def combine_loss(y_hat, y_label):
    loss1 = torch.exp(log_rmse(y_hat, y_label))
    # loss1 = log_rmse(y_hat, y_label)
    mse_loss = nn.MSELoss()
    loss2 = mse_loss(y_hat,y_label)
    return loss1 + loss2 
def train_model(net,loss,num_epcoh,train_iter, valid_iter, trainer):
    metric = Accumulator(3)
    evaluator = Evaluator(net, log_rmse)
    train_data=np.zeros(num_epcoh)
    valid_data=np.zeros(num_epcoh)
    if isinstance(net, nn.Module):
        net.train()
    for epoch in range(num_epcoh):
        n = 0
        print(f'epoch{epoch+1}')
        for X,y in train_iter:
            trainer.zero_grad()
            n += 1
            y_hat = net(X)
            l =  loss(y_hat,y)
            log_l = log_rmse(y_hat, y)
            valid_loss = evaluator.evaluate_loss(valid_iter)
            l = torch.mean(l)
            metric.add(log_l, valid_loss, 1)
            train_data[epoch] += log_l
            valid_data[epoch] += valid_loss
            l.backward()
            trainer.step()
        train_data[epoch] /= n
        valid_data[epoch] /= n
    return metric, train_data, valid_data

class KfoldSubsetIter:
    def __init__(self, k, dataset, batch_size=256, shuffle=True):
        self.k = k
        self.dataset = dataset # 传入数据集
        self.data_num = len(dataset)
        self.fold_num = self.data_num // k # 每折的样本数
        self.batch_size = batch_size
        self.indices = (torch.randperm(self.data_num) if shuffle else torch.arange(self.data_num,dtype=torch.long)).tolist() # 随机打乱索引

    def __iter__(self):
        for i in range(self.k):
            start = i * self.fold_num
            end = min(self.data_num, start+self.fold_num) # 防止越界
            indices_train = self.indices[:start]+self.indices[end:] # 训练集索引
            indices_valid = self.indices[start:end] # 验证集索引
            train_subset = torch.utils.data.Subset(self.dataset, indices_train)
            valid_subset = torch.utils.data.Subset(self.dataset, indices_valid)
            train_subset = DataLoader(train_subset, batch_size=self.batch_size, shuffle=True, num_workers=get_num_workers())
            valid_subset = DataLoader(valid_subset, batch_size=self.batch_size, shuffle=False, num_workers=get_num_workers())

            yield train_subset, valid_subset


class Ploter:
    def __init__(self,train_loss, valid_loss):
        self.train_loss = train_loss
        self.valid_loss = valid_loss
    
    def cpt_graph(self):
        plt.plot(self.train_loss, label='train_loss')
        plt.plot(self.valid_loss, label='valid_loss')
        plt.xlabel('epoch')
        plt.ylabel('loss')
        self._add_last_point_annotation()
        plt.legend()
    
    def plot(self):
        plt.plot(self.train_loss, label='train_loss')
        plt.plot(self.valid_loss, label='valid_loss')
        plt.xlabel('epoch')
        plt.ylabel('loss')
        self._add_last_point_annotation()
        plt.legend()
        plt.show() 
    
    def _add_last_point_annotation(self):
        # 获取最后一个点的坐标
        last_epoch = len(self.train_loss) - 1
        last_train = self.train_loss[-1]
        last_valid = self.valid_loss[-1]
        
        # 添加训练损失标注
        plt.annotate(f'train: {last_train:.4f}', 
                    xy=(last_epoch, last_train),
                    xytext=(10, 10), textcoords='offset points',
                    bbox=dict(boxstyle='round,pad=0.5', fc='yellow', alpha=0.5),
                    arrowprops=dict(arrowstyle='->'))
        
        # 添加验证损失标注
        plt.annotate(f'valid: {last_valid:.4f}',
                    xy=(last_epoch, last_valid),
                    xytext=(10, -20), textcoords='offset points',
                    bbox=dict(boxstyle='round,pad=0.5', fc='cyan', alpha=0.5),
                    arrowprops=dict(arrowstyle='->'))

    def save(self, filename="loss_curve.png"):
        self.cpt_graph()
    
        # 如果文件已存在，生成新文件名
        if os.path.exists(filename):
            base, ext = os.path.splitext(filename)
            counter = 1
            while os.path.exists(f"{base}_{counter}{ext}"):
                counter += 1
            filename = f"{base}_{counter}{ext}"
    
        plt.savefig(filename)
        plt.close()
        print(f"图像已保存为: {filename}")

def k_fold_train(net, loss, num_epoch, dataset, trainer, k=5, batch_size=256):
    k_fold_iter = KfoldSubsetIter(k, dataset, batch_size)
    num_fold = 0
    metric = Accumulator(2)
    train_loss_data = np.zeros(num_epoch)
    valid_loss_data = np.zeros(num_epoch)
    for train_iter, valid_iter in k_fold_iter: # k折迭代
        start = time.time()
#        print(f'weight{net[0].weight[:1,:4]}') # type: ignore
        net.apply(reset_parameters)
        net.apply(kaiming_init)
        if isinstance(net, nn.Module):
            net.train()
        print(f'Training Fold {num_fold+1}...')
#        print(f'weight{net[0].weight[:1,:4]}') # type: ignore
        num_fold += 1
        fold_metric, train_data, valid_data = train_model(net, loss, num_epoch, train_iter, valid_iter, trainer)
        train_loss = fold_metric[0] / fold_metric[2]
        valid_loss = fold_metric[1] / fold_metric[2]
        train_loss_data += train_data
        valid_loss_data += valid_data
        evaluator = Evaluator(net, log_rmse)
        valid_loss = evaluator.evaluate_loss(valid_iter)
        metric.add(train_loss, valid_loss)
        end = time.time()
        print(f'fold{num_fold},'f'Train Loss: {train_loss:.4f},'  f'Validation Loss: {valid_loss:.4f},'f'Time: {end-start:.2f}s')
    print(f'Average Train Loss: {metric[0] / k:.4f}')
    print(f'Average Validation Loss: {metric[1] / k:.4f}')
    train_loss_data = train_loss_data.astype(np.float32) / k
    valid_loss_data = valid_loss_data.astype(np.float32) / k # 取平均
    ploter = Ploter(train_loss_data, valid_loss_data)
    # ploter.cpt_graph()
    ploter.plot()
    ploter.save("img/loss_curve.png")
    
class Evaluator:
    def __init__(self, net, loss):
        self.net = net
        self.loss = loss

    def evaluate_loss(self, data_iter):
        if isinstance(self.net, nn.Module):
            self.net.eval()
        metric = Accumulator(2)
        with torch.no_grad():
            for X, y in data_iter:
                y_hat = self.net(X)
                l = self.loss(y_hat, y).mean()
                metric.add(l , 1)
        if isinstance(self.net, nn.Module):
            self.net.train()
        return metric[0] / metric[1]
    
    def evaluate_loss_item(self, data_iter):
        if isinstance(self.net, nn.Module):
            self.net.eval()
        metric = Accumulator(2)
        with torch.no_grad():
            for X, y in data_iter:
                y_hat = self.net(X)
                l = self.loss(y_hat, y).item()
                metric.add(l , len(y))
        if isinstance(self.net, nn.Module):
            self.net.train()
        return metric[0]

def train_and_pred(net, loss, num_epoch, train_dataset, test_dataset, trainer, batch_size=256):
    train_iter = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_iter = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)
    if isinstance(net, nn.Module):
        net.train()
    print('Training...')
    print(f'Epoch ')
    for epoch in range(num_epoch):
        print(f'{epoch}')
        for X,y in train_iter:
            trainer.zero_grad()
            y_hat = net(X)
            l =  loss(y_hat,y)
            l = torch.mean(l)            
            l.backward()
            trainer.step()
    if isinstance(net, nn.Module):
        net.eval()
    preds = []
    print('Predicting...')
    with torch.no_grad():
        for X, _ in test_iter:
            y_hat = net(X)
            preds.append(y_hat.cpu().numpy())
    submission = pd.read_csv('sample_submission.csv')
    submission.iloc[:, 1] = np.concatenate(preds, axis=0)
    submission.to_csv('submission.csv', index=False)

if  __name__ =='__main__':
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    # device = 'cpu'
    print(f"Using device: {device}")
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    train_path = './train.csv'
    test_path = './test.csv'
    batch_size = 256
    train_dataset, test_dataset = load_data(train_path, test_path, device)
    print("load complete")
#    print("train_iter length:", len(train_iter))
    num_input, num_output= train_dataset.tensors[0].shape[1], 1
#    print("num_input:", num_input)
    n_hidden1, n_hidden2, n_hidden3, n_hidden4, n_hidden5= int(num_input*1.5), int(num_input*1), num_input//2 , num_input//4, num_input//8
    p1, p2, p3= 0.2, 0.25, 0.3
    lr, lambd = 0.01, 0.0001
    # loss = log_rmse
    loss = nn.MSELoss()
    #loss = combine_loss
    num_epoch = 10
    net = nn.Sequential(
        nn.Linear(num_input,n_hidden1),
        nn.LeakyReLU(),
        # nn.ReLU(),
        nn.Dropout(p1),
        nn.Linear(n_hidden1,n_hidden2),
        nn.LeakyReLU(),
        nn.Dropout(p2),
        nn.Linear(n_hidden2,n_hidden3),
        nn.LeakyReLU(),
        nn.Dropout(p2),
        nn.Linear(n_hidden3,n_hidden4),
        nn.ReLU(),
        nn.Dropout(p3),
        nn.Linear(n_hidden4,num_output),
        # nn.Dropout(p3),
        # nn.Linear(n_hidden5,num_output),
    ).to(device)
    net.apply(kaiming_init)
    trainer = torch.optim.Adam(net.parameters(), lr=lr, weight_decay=lambd)
    k_fold_train(net, loss, num_epoch, train_dataset, trainer, k=5, batch_size=batch_size)
#    train_and_pred(net, loss, num_epoch, train_dataset, test_dataset, trainer)