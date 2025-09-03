from re import X
import torch
from torch import  nn
from d2l import torch as d2l
import matplotlib.pyplot as plt
import time
import numpy as np
import torchvision
from torch.utils import data
from torchvision import transforms


def get_dataloader_workers():
    return 4

def init_weights_Kaiming(m):
    if type(m) == nn.Linear:
        nn.init.kaiming_normal_(m.weight, mode='fan_in', nonlinearity='relu')
        nn.init.zeros_(m.bias)

def load_data_fashion_minst(batch_size, resize=None):
    trans = [
        transforms.ToTensor(),
        #transforms.Lambda(lambda x : x.view(-1))
    ]
    if resize:
        if isinstance(resize, (tuple, int)):
            trans.insert(0, transforms.Resize(resize))  # type: ignore
        else:
            raise ValueError(
                "resize must be an integer or a tuple of integers")
    trans = transforms.Compose(trans)
    #    print(trans)
    mnist_train = torchvision.datasets.FashionMNIST(root="data",
                                                    train=True,
                                                    transform=trans,
                                                    download=True)
    mnist_test = torchvision.datasets.FashionMNIST(root="data",
                                                   train=False,
                                                   transform=trans,
                                                   download=True)
    return (data.DataLoader(mnist_train,
                            batch_size,
                            shuffle=True,
                            num_workers=get_dataloader_workers()),
            data.DataLoader(mnist_test,
                            batch_size,
                            shuffle=False,
                            num_workers=get_dataloader_workers()))

def init_weights(m):
    if type(m) == nn.Linear:
        nn.init.normal_(m.weight, std=0.01)
        nn.init.zeros_(m.bias)

def init_zeros(m):
    if type(m) == nn.Linear:
        nn.init.zeros_(m.weight)
        nn.init.zeros_(m.bias)

def train_epoch(net, train_iter, loss, trainer):
    for X, y in train_iter:
        X, y = X.to(next(net.parameters()).device), y.to(
            next(net.parameters()).device)
        y_hat = net(X)
        l = loss(y_hat, y).mean()
        trainer.zero_grad()
        l.backward()
        trainer.step()
    return


class Accumulator:

    def __init__(self, n):
        self.data = [0.0] * n

    def add(self, *args):
        self.data = [a + float(b) for a, b in zip(self.data, args)]

    def __getitem__(self, idx):
        return self.data[idx]


def evaluate_accuracy(net, test_iter):
    if isinstance(net, torch.nn.Module):
        net.eval()
    metric = Accumulator(
        2)  # Sum of correct predictions and total number of predictions
    with torch.no_grad():
        for X, y in test_iter:
            X, y = X.to(next(net.parameters()).device), y.to(
                next(net.parameters()).device)
            metric.add(d2l.accuracy(net(X), y), y.numel())
    return metric[0] / metric[1]

def evaluate_one_epoch_loss(net, test_iter, loss):
    if isinstance(net, nn.Module):
        net.eval()
    metric = Accumulator(2)  # Sum of loss and total number of predictions
    with torch.no_grad():
        for X, y in test_iter:
            X, y = X.to(next(net.parameters()).device), y.to(
                next(net.parameters()).device)
            metric.add(loss(net(X), y).sum(), y.numel())
            break
    return metric[0] / metric[1]

def evaluate_loss(net, test_iter, loss):
    if isinstance(net, nn.Module):
        net.eval()
    metric = Accumulator(2)  # Sum of loss and total number of predictions
    with torch.no_grad():
        for X, y in test_iter:
            X, y = X.to(next(net.parameters()).device), y.to(
                next(net.parameters()).device)
            metric.add(loss(net(X), y).sum(), y.numel())
    return metric[0] / metric[1]


def train_net(net, train_iter, num_epochs, loss, trainer,test_iter):
    print(f"Training {net.__class__.__name__}...")
    timer=0
    start_time = time.time()
    epoch_losses = []
    epoch_accs = []
    test_losses = []
    if isinstance(net, nn.Module):
        net.train()
    for epoch in range(num_epochs):
        metric = Accumulator(3)  # Sum of loss, accuracy and total number of predictions
        for X, y in train_iter:

                X, y = X.to(next(net.parameters()).device), y.to(next(net.parameters()).device)
                y_hat = net(X)
                l = loss(y_hat, y).mean()
                trainer.zero_grad()
                l.backward()
                trainer.step()

                # 记录损失和准确率
                metric.add(l.item() * y.size(0), d2l.accuracy(y_hat, y), y.size(0))
                epoch_loss = metric[0] / metric[2]
        epoch_loss = metric[0] / metric[2]
        epoch_acc = metric[1] / metric[2]
        epoch_losses.append(epoch_loss)
        epoch_accs.append(epoch_acc)
        test_losses.append(evaluate_one_epoch_loss(net,test_iter,loss))
    end_time = time.time()
    timer += end_time - start_time
    
    return timer, epoch_losses, test_losses


def plot_evaluation(test_acc, test_loss, timer, model_names):

    metrics = [test_acc, test_loss]
    metrics_names = ['Accuracy', 'Loss']
    num_models = len(model_names)
    num_metrics = len(metrics)

    bar_width = 0.25
    x = np.arange(0, num_models)
    offsets = [-bar_width, 0, bar_width]
    colors = ['b', 'g', 'r']
    #
    plt.figure(figsize=(10, 6))
    for i in range(num_metrics):
        bars=plt.bar(x + offsets[i],
                metrics[i],
                width=bar_width,
                color=colors[i],
                label=metrics_names[i])
        for bar in bars:
            height = bar.get_height()
            plt.text(bar.get_x() + bar.get_width() / 2.,
                     height + 0.01,  # 稍微高于柱子顶部
                     f"{height:.2f}",  # 显示2位小数
                     ha='center',      # 水平居中
                     va='bottom',      # 垂直底部对齐
                     fontsize=9) 
    plt.xticks(x, model_names)
    plt.xlabel('Models')
    plt.ylabel('Value')
    plt.title('Model Evaluation')
    plt.legend()
    plt.tight_layout()
 

def plot_training_time(timer, model_names):
    bar_width = 0.15  # Adjust bar width to make bars narrower
    plt.figure(figsize=(10, 6))
    plt.bar(model_names, timer, width=bar_width, color='b')
    plt.xlabel('Models')
    plt.ylabel('Training Time (seconds)')

    plt.title('Training Time per Model')
    plt.xticks(rotation=45)
    plt.tight_layout()

def plot_epoch(epoch_losses, test_loss, model_names):
    plt.figure(figsize=(10, 6))
    plt.plot(epoch_losses, label=f'{model_names} train')
    plt.plot(test_loss, label=f'{model_names} test')
#    plt.ylim(0, 1)
    plt.xlabel('Epochs')
    plt.ylabel('Value')
    plt.title('Loss')
    plt.legend()
    plt.tight_layout()

if __name__ == '__main__':
#    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    device = torch.device('cpu')
    batch_size, lr, num_epochs, num_inputs, num_hidden, num_outputs = 256, 0.1, 30, 784, 256, 10
    num_hidden2 = 256
    p=0.5
    lambd = 0.0005
    net = nn.Sequential(nn.Flatten(), nn.Linear(num_inputs, num_hidden),
                        nn.ReLU(), nn.Linear(num_hidden, num_outputs))
    net = net.to(device)
    net_adam = nn.Sequential(
        nn.Flatten(),
        nn.Linear(num_inputs, num_hidden),
        nn.ReLU(),
        nn.Linear(num_hidden, num_outputs),
    )

    net_adam = net_adam.to(device)

    net_softmax = nn.Sequential(nn.Flatten(),
                                nn.Linear(num_inputs, num_outputs))

    net_softmax = net_softmax.to(device)

    net_4 = nn.Sequential(
        nn.Flatten(),
        nn.Linear(num_inputs, 512),
        nn.ReLU(),
        nn.Linear(512, num_hidden),
        nn.ReLU(),
        nn.Linear(num_hidden, 128),
        nn.ReLU(),
        nn.Linear(128, num_outputs),
    )

    net_4 = net_4.to(device)

    net_weight_decay = nn.Sequential(
        nn.Flatten(),
        nn.Linear(num_inputs, num_hidden),
        nn.ReLU(),
        nn.Linear(num_hidden, num_hidden2),
        nn.ReLU(),
        nn.Linear(num_hidden2, num_outputs),
    )
    net_weight_decay = net_weight_decay.to(device)

    net_dropout = nn.Sequential(
        nn.Flatten(),
        nn.Linear(num_inputs, num_hidden),
        nn.ReLU(),
        nn.Dropout(0.2),
        nn.Linear(num_hidden, num_hidden2),
        nn.ReLU(),
        nn.Dropout(p),
        nn.Linear(num_hidden2, num_outputs),
    )    


    loss = nn.CrossEntropyLoss(reduction='none')
    trainer1 = torch.optim.SGD(net.parameters(), lr=0.1)
    trainer2 = torch.optim.Adam(net_adam.parameters(), lr=lr)
    trainer3 = torch.optim.SGD(net_softmax.parameters(), lr=0.1)
    trainer4 = torch.optim.SGD(net_4.parameters(), lr=lr)
    trainer_weight_decay = torch.optim.SGD(
        net_weight_decay.parameters(), lr=0.1, weight_decay=lambd)
    trainer_dropout = torch.optim.SGD(
        net_dropout.parameters(), lr=lr)

    net.apply(init_weights)
    net_adam.apply(init_weights)
    net_softmax.apply(init_weights)
    net_4.apply(init_weights)
    #net_4.apply(init_weights_Kaiming)

    print("net device:", next(net.parameters()).device)
    print("net_adam device:", next(net_adam.parameters()).device)
    print("net_softmax device:", next(net_softmax.parameters()).device)
    print("net_4 device:", next(net_4.parameters()).device)
    print("net_weight_decay device:", next(net_weight_decay.parameters()).device)
    print("net_dropout device:", next(net_dropout.parameters()).device)
    # Load the data
    train_iter, test_iter = load_data_fashion_minst(batch_size)
    
    timer = [0.0, 0.0, 0.0, 0.0]  # Initialize timers for each model

    print('Training...\n')


    timer[0], epoch_losses_softmax, test_losses_softmax = train_net(net_softmax, train_iter, num_epochs, loss, trainer3,test_iter)
    timer[1], epoch_losses, test_losses = train_net(net, train_iter, num_epochs, loss, trainer1,test_iter)
#    timer[3], epoch_losses_4, epoch_accs_4 = train_net(net_4, train_iter, num_epochs, loss, trainer4)
    timer[2], epoch_losses_weight_decay, test_losses_weight_decay = train_net(net_weight_decay, train_iter, num_epochs, loss, trainer_weight_decay,test_iter)
    timer[3], epoch_losses_dropout, test_losses_dropout = train_net(net_dropout, train_iter, num_epochs, loss, trainer_dropout,test_iter)
    print('Training complete\n')
    print('Training time:', timer)

    test_acc = [
        evaluate_accuracy(net_softmax, test_iter),
        evaluate_accuracy(net, test_iter),
        evaluate_accuracy(net_weight_decay, test_iter),
        evaluate_accuracy(net_dropout, test_iter),
    ]

    test_loss = [
    evaluate_loss(net_softmax, test_iter, loss),  # 直接计算最终测试损失
    evaluate_loss(net, test_iter, loss),
    evaluate_loss(net_weight_decay, test_iter, loss),
    evaluate_loss(net_dropout, test_iter, loss),
    ]

    # print('Test accuracy:', test_acc)
    # print('Test loss:', test_loss)
    model_names = [
        'Softmax ', 'MLP', 'Weight Decay', 'Dropout'
    ]

    plot_epoch(epoch_losses, test_losses, model_names[0])
    plot_epoch(epoch_losses_softmax, test_losses_softmax, model_names[1])
    plot_epoch(epoch_losses_weight_decay, test_losses_weight_decay, model_names[2])
    plot_epoch(epoch_losses_dropout, test_losses_dropout, model_names[3])

    plot_evaluation(test_acc, test_loss, timer, model_names)
    plot_training_time(timer, model_names)
    plt.show()
#end
