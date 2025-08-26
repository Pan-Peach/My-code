import torch
from torch import nn
import os

import numpy as np

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

def load_data(path="./data",batch_size=128):
    trans = transforms.Compose([
        transforms.ToTensor(),
        # transforms.Resize((224, 224)),
        transforms.Normalize((0.5,), (0.5,)),    
    ])
    train_dataset = torchvision.datasets.FashionMNIST(path, train=True,transform=trans,download=True)
    test_dataset = torchvision.datasets.FashionMNIST(path, train=False, transform=trans,download=True)
    return (DataLoader(train_dataset, batch_size, shuffle=True,num_workers=get_numworkers()),
            DataLoader(test_dataset, batch_size, shuffle=False,num_workers=get_numworkers()))

def nin_block(in_channels, out_channels, kernel_size, strides, padding):
    return nn.Sequential(
        # 常规卷积层
        nn.Conv2d(in_channels, out_channels, kernel_size, strides, padding),
        nn.ReLU(),
        # 两个1×1卷积层
        nn.Conv2d(out_channels, out_channels, kernel_size=1), nn.ReLU(),
        nn.Conv2d(out_channels, out_channels, kernel_size=1), nn.ReLU())

def nin_net():
    return nn.Sequential(
        nin_block(1, 96, kernel_size=5, strides=1, padding=0),
        nn.MaxPool2d(kernel_size=3, stride=2),
        nn.Dropout(0.2),
        nin_block(96, 256, kernel_size=3, strides=1, padding=1),
        nn.MaxPool2d(kernel_size=3, stride=2),
        nn.Dropout(0.5),
        nin_block(256, 10, kernel_size=3, strides=1, padding=1),  # 输出通道数等于类别数
        nn.AdaptiveAvgPool2d((1, 1)),  # 全局平均池化
        nn.Flatten()  # 展平成二维输出
    )

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
        cnt = 0
        train_acc = 0
        rec_loss = 0
        for X, y in train_iter:
            cnt += 1 
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

        print(f'epoch {epoch + 1}, loss {l.item():.4f}')

        if isinstance(net, nn.Module):
            net.eval()
        with torch.no_grad():
            for X, y in test_iter:
                X, y = X.to(device), y.to(device)
                y_hat = net(X)
                hat = y_hat.argmax(dim=1)
                sum = (hat == y).sum().item()
                print(f'test acc {sum / len(y)}')
                break

if __name__ == "__main__":
    # 设置设备
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    
    # 创建模型
    net = nin_net().to(device)
    
    
    # 加载数据
    batch_size = 128
    path = "./data"
    train_iter, test_iter = load_data(path=path, batch_size=batch_size)
    
    X = torch.randn(batch_size, 1, 28, 28, device=device)
    for layer in net:
        X = layer(X)
        print(layer.__class__.__name__, 'output shape:\t', X.shape)
    # 训练模型的代码可以在这里添加
    num_epochs = 15
    lr = 0.001
    train(net, train_iter, test_iter, num_epochs, lr, device)
    # ...