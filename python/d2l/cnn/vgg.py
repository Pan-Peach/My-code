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

def vgg_block(num_convs, in_channels, out_channels):
    """
    创建VGG块
    Args:
        num_convs: 卷积层数量
        in_channels: 输入通道数
        out_channels: 输出通道数
    """
    layers = []
    for _ in range(num_convs):
        layers.append(nn.Conv2d(in_channels, out_channels, 
                              kernel_size=3, padding=1))
        layers.append(nn.ReLU(inplace=True))
        in_channels = out_channels
    layers.append(nn.MaxPool2d(kernel_size=2, stride=2))
    return nn.Sequential(*layers)

def vgg(conv_arch):
    conv_blks = []
    in_channels = 1  # 输入通道数，灰度图像为1

    for (num_convs, out_channels) in conv_arch:
        conv_blks.append(vgg_block(num_convs, in_channels, out_channels))
        in_channels = out_channels
    
    return nn.Sequential(
        *conv_blks,
        nn.Flatten(),
        nn.Linear(out_channels*3*3, 4096), nn.ReLU(inplace=True), nn.Dropout(0.5),
        nn.Linear(4096, 4096), nn.ReLU(inplace=True), nn.Dropout(0.5),
        nn.Linear(4096, 10)
    )



def train_vgg(net, train_iter, test_iter, num_epochs, lr, device):
    """
    训练VGG模型
    Args:
        net: VGG模型
        train_iter: 训练数据迭代器
        test_iter: 测试数据迭代器
        num_epochs: 训练轮数
        lr: 学习率
        device: 设备
    """
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(net.parameters(), lr=lr)

    net.to(device)
    
    for epoch in range(num_epochs):
        net.train()
        for X, y in train_iter:
            X, y = X.to(device), y.to(device)
            optimizer.zero_grad()
            output = net(X)
            loss = criterion(output, y)
            loss.backward()
            optimizer.step()
        
        print(f'Epoch {epoch + 1}, Loss: {loss.item()}')

    # 评估模型
    net.eval()
    with torch.no_grad():
        total, correct = 0, 0
        for X, y in test_iter:
            X, y = X.to(device), y.to(device)
            output = net(X)
            total += y.size(0)
            correct += (output.argmax(dim=1) == y).sum().item()
        print(f'Test Accuracy: {correct / total:.4f}')
        record = np.zeros((num_epochs, 3))
        record[epoch, 0] = epoch + 1
        record[epoch, 1] = loss.item()
        record[epoch, 2] = correct / total

if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    # 创建模型
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    net = vgg([(1, 64), (1, 128), (2, 256)]).to(device)

    # 测试数据维度变化
    X = torch.randn(1, 1, 28, 28).to(device)
    for layer in net:
        X = layer(X)
        print(layer.__class__.__name__, 'output shape: \t', X.shape)
    # 加载数据
    batch_size = 128
    path = "./data"
    train_iter, test_iter = load_data(path=path, batch_size=batch_size)
    # 训练模型
    num_epochs = 15
    lr = 0.001
    train_vgg(net, train_iter, test_iter, num_epochs, lr, device)
