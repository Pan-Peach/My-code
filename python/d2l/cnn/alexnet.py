import torch
from torch import nn
from torchvision import transforms
import torchvision
from torch.utils.data import DataLoader
import os
import numpy as np
import matplotlib.pyplot as plt

def get_numworkers():
    return 4

def load_data(path,batch_size=128,device='cpu'):
    trans = transforms.Compose([
        transforms.ToTensor(),
        # transforms.Resize((224, 224)),
        transforms.Normalize((0.5,), (0.5,)),    
    ])
    train_dataset = torchvision.datasets.FashionMNIST(path, train=True,transform=trans,download=True)
    test_dataset = torchvision.datasets.FashionMNIST(path, train=False, transform=trans,download=True)
    return (DataLoader(train_dataset, batch_size, shuffle=True,num_workers=get_numworkers()),
            DataLoader(test_dataset, batch_size, shuffle=False,num_workers=get_numworkers()))

def train(net, train_iter, test_iter, num_epochs, lr, device):
    net.to(device)
    optimizer = torch.optim.Adam(net.parameters(), lr=lr, weight_decay=1e-4)
    loss = nn.CrossEntropyLoss()
    record = np.zeros((num_epochs, 3))
    if isinstance(net, nn.Module):
        net.train()
    
    first_conv = next(net.parameters())

    for epoch in range(num_epochs):
        print(f'epoch {epoch + 1}')
        # print(first_conv.data.flatten()[:5])
        cnt = 0
        train_acc = 0
        rec_loss = 0
        for X, y in train_iter:
            cnt += 1 
            # print(cnt)           
            X, y = X.to(device), y.to(device)

            optimizer.zero_grad()
            y_hat = net(X)
            hat = y_hat.argmax(dim=1)
            sum = (hat == y).sum().item()
            train_acc += sum / len(y)
            l = loss(y_hat, y)
            rec_loss += l.mean().item()
            l.backward()
            optimizer.step()
        record[epoch, 0] = evaluate(net, test_iter)
        record[epoch, 1] = rec_loss / cnt
        record[epoch, 2] = train_acc / cnt

        print(f'epoch {epoch + 1}, loss {l.item():.4f}, train acc {record[epoch, 2]:.4f}, test acc {record[epoch, 0]:.4f}')
    plot_outcome(record)

def evaluate(net,test_iter):
    if  isinstance(net,nn.Module):
        net.eval()
    with torch.no_grad():
        correct = 0
        cnt = 0
        for X,y in test_iter:
            cnt += 1
            X, y = X.to(device), y.to(device)
            y_hat = net(X)
            correct += (y_hat.argmax(dim=1) == y).sum().item()/len(y)
        print(f'accuracy {correct / cnt:.4f}')
        return correct / cnt

def plot_outcome(record):
    plt.plot(np.arange(1, record.shape[0] + 1), record[:, 0], label='test acc')
    plt.plot(np.arange(1, record.shape[0] + 1), record[:, 1], label='loss')
    plt.plot(np.arange(1, record.shape[0] + 1), record[:, 2], label='train acc')
    plt.xlabel('epoch')
    plt.ylabel('accuracy/loss')
    plt.legend()
    plt.show()

class FashionCNN(nn.Module):
    def __init__(self):
        super().__init__()
        self.features = nn.Sequential(
            nn.Conv2d(1, 32, kernel_size=3, padding=1),  # 28→28
            nn.ReLU(inplace=True),
            nn.MaxPool2d(2),  # 28→14
            
            nn.Conv2d(32, 64, kernel_size=3, padding=1),  # 14→14
            nn.ReLU(inplace=True),
            nn.MaxPool2d(2)   # 14→7
        )
        self.classifier = nn.Sequential(
            nn.Linear(64*7*7, 128),
            nn.ReLU(inplace=True),
            nn.Dropout(0.5),
            nn.Linear(128, 10)
        )

    def forward(self, x):
        x = self.features(x)
        x = x.view(x.size(0), -1)
        return self.classifier(x)

if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print(f'Using {device} device')
    batch_size = 128
    num_epochs = 15
    lr = 0.001
    path = "./data"
    train_iter, test_iter = load_data(path,batch_size=batch_size,device=device)
    AlexNet = nn.Sequential(
        nn.Conv2d(1, 96, kernel_size=11, stride=4, padding=1), nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=3, stride=2),
        nn.Conv2d(96, 256, kernel_size=5, padding=2), nn.ReLU(inplace=True),
        nn.MaxPool2d(kernel_size=3, stride=2),
        nn.Conv2d(256, 384, kernel_size=3, padding=1), nn.ReLU(inplace=True),
        nn.Conv2d(384, 384, kernel_size=3, padding=1), nn.ReLU(inplace=True),
        nn.Conv2d(384, 256, kernel_size=3, padding=1), nn.ReLU(inplace=True),
        nn.AdaptiveAvgPool2d((6, 6)),  # 自适应池化确保输出尺寸
        nn.Flatten(),
        nn.Linear(256*6*6, 4096), nn.ReLU(inplace=True),
        nn.Dropout(0.5),
        nn.Linear(4096, 4096), nn.ReLU(inplace=True),
        nn.Dropout(0.5),
        nn.Linear(4096, 10)
    ).to(device)
    mlp = nn.Sequential(
        nn.Flatten(),
        nn.Linear(224*224, 10)
    ).to(device)
    MiniAlexNet = nn.Sequential(
    # 输入: 1x28x28
    nn.Conv2d(1, 32, kernel_size=3, stride=1, padding=1), nn.ReLU(),  # 32x28x28
    nn.MaxPool2d(kernel_size=2, stride=2),  # 32x14x14
    
    nn.Conv2d(32, 64, kernel_size=3, padding=1), nn.ReLU(),  # 64x14x14
    nn.MaxPool2d(kernel_size=2, stride=2),  # 64x7x7
    
    nn.Conv2d(64, 128, kernel_size=3, padding=1), nn.ReLU(),  # 128x7x7
    nn.Conv2d(128, 256, kernel_size=3, padding=1), nn.ReLU(),  # 256x7x7
    nn.AdaptiveAvgPool2d((3, 3)),  # 256x3x3
    
    nn.Flatten(),
    nn.Linear(256*3*3, 512), nn.ReLU(),
    nn.Dropout(0.5),
    nn.Linear(512, 10)
    ).to(device)
    FashionCNN = FashionCNN().to(device)
    # X = torch.randn(1, 1, 224, 224).to(device)
    # for layer in AlexNet:
    #     X = layer(X)
    #     print(layer.__class__.__name__, 'output shape: \t', X.shape)
    # for X, y in train_iter:
    #     torch.set_printoptions(threshold=np.inf)
    #     print(X)
    #     break
    # train(AlexNet, train_iter, test_iter, num_epochs, lr, device)
    train(MiniAlexNet, train_iter, test_iter, num_epochs, lr, device)
    
