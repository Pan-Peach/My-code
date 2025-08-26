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