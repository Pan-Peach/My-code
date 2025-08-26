import pandas as pd
import numpy as np
import os
from pathlib import Path
from torch.utils.data import Dataset, DataLoader 
import torchvision.transforms as transforms
from PIL import Image
import torch
import torch.nn as nn
from torchvision import models
class DogBreedDataset(Dataset):
    # 类变量，所有实例共享
    breed_to_idx = {}
    idx_to_breed = {}
    initialized = False
    
    @classmethod
    def initialize_mapping(cls, breeds):
        """初始化品种映射"""
        if not cls.initialized:
            cls.breed_to_idx = {breed: idx for idx, breed in enumerate(sorted(breeds))}
            cls.idx_to_breed = {idx: breed for breed, idx in cls.breed_to_idx.items()}
            cls.initialized = True

    def __init__(self, dataframe, transform=None):
        self.dataframe = dataframe
        self.transform = transform
        if not self.initialized:
            self.initialize_mapping(dataframe['breed'].unique())

    def __len__(self):
        return len(self.dataframe)

    def __getitem__(self, idx):
        img_path = self.dataframe.iloc[idx]['dog_image']
        image = Image.open(img_path).convert('RGB')
        
        if self.transform:
            image = self.transform(image)
        
        label = self.dataframe.iloc[idx]['breed']
        label = self.breed_to_idx[label]  # 使用类变量进行映射
        return image, label
    
    @classmethod
    def decode_predictions(cls, predictions):
        """将预测的索引转换回品种名称"""
        return [cls.idx_to_breed[idx.item()] for idx in predictions]

def get_num_workers():
    return 4

def  load_data(file_path, batch_size=64):
    df = pd.read_csv(os.path.join(file_path, 'labels.csv'))
    df['dog_image'] = df['id'].apply(lambda x: os.path.join(file_path, 'train', f"{x}.jpg"))
    df['exists'] = df['dog_image'].apply(lambda x: Path(x).exists())

    test_df = pd.read_csv(os.path.join(file_path, 'test.csv'))
    test_df['dog_image'] = test_df['id'].apply(lambda x: os.path.join(file_path, 'test', f"{x}.jpg"))
    test_df['exists'] = test_df['dog_image'].apply(lambda x: Path(x).exists())


    # 划分
    total_size = len(df)
    train_size = int(total_size * 0.9)
    val_size = total_size - train_size
    train_df = df.iloc[:train_size]
    val_df = df.iloc[train_size:]


    # 定义数据增强（用于训练集）
    train_transform = transforms.Compose([
        transforms.RandomResizedCrop(224, scale=(0.8, 1.0)),
        transforms.RandomHorizontalFlip(),
        transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406],
                           std=[0.229, 0.224, 0.225])
    ])
    
    # 定义测试/验证集转换（无数据增强）
    test_transform = transforms.Compose([
        transforms.Resize((224, 224)),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406],
                           std=[0.229, 0.224, 0.225])
    ])

    # 创建数据集
    train_dataset = DogBreedDataset(train_df, transform=train_transform)
    val_dataset = DogBreedDataset(val_df, transform=test_transform)
    test_dataset = DogBreedDataset(test_df, transform=test_transform)

    # 创建数据加载器model
    train_iter = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=get_num_workers())
    val_iter = DataLoader(val_dataset, batch_size=batch_size, shuffle=False, num_workers=get_num_workers())
    test_iter = DataLoader(test_dataset, batch_size=batch_size, shuffle=False, num_workers=get_num_workers())
    return train_iter, val_iter, test_iter

class ResidualBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride=1):
        super(ResidualBlock, self).__init__()
        self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.conv2 = nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1)
        self.bn2 = nn.BatchNorm2d(out_channels)

        self.shortcut = nn.Sequential()
        if stride != 1 or in_channels != out_channels:
            self.shortcut = nn.Sequential(
                nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(out_channels)
            )

    def forward(self, x):
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)

        out = self.conv2(out)
        out = self.bn2(out)

        out += self.shortcut(x)
        out = self.relu(out)
        # print(out.shape)
        return out

class ResNet(nn.Module):
    def __init__(self, block, num_blocks, num_classes=120):
        super(ResNet, self).__init__()
        self.in_channels = 64

        self.conv1 = nn.Conv2d(3, 64, kernel_size=7, stride=2, padding=3)
        self.bn1 = nn.BatchNorm2d(64)
        self.relu = nn.ReLU(inplace=True)
        self.maxpool = nn.MaxPool2d(kernel_size=3, stride=2, padding=1)

        res_layers = []
        
        channels = self.in_channels
        for i, num_block in enumerate(num_blocks):
            stride = 1 if i == 0 else 2
            res_layers.append(self._make_layer(block, channels, num_block, stride))
            channels *= 2 

        
        self.res_layers = nn.Sequential(*res_layers)
        # self.layer1 = self._make_layer(block, 64, num_blocks[0], stride=1)
        # self.layer2 = self._make_layer(block, 128, num_blocks[1], stride=2)
        # self.layer3 = self._make_layer(block, 256, num_blocks[2], stride=2)
        # self.layer4 = self._make_layer(block, 512, num_blocks[3], stride=2)
        # self.layers = nn.Sequential(*layers)
        self.avgpool = nn.AdaptiveAvgPool2d((1, 1))
        self.fc = nn.Linear(self.in_channels, num_classes)

        for m in self.modules():
            if isinstance(m, nn.Conv2d):
                nn.init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
            elif isinstance(m, nn.BatchNorm2d):
                nn.init.constant_(m.weight, 1)
                nn.init.constant_(m.bias, 0)

    def _make_layer(self, block, out_channels, blocks, stride):
        layers = []
        layers.append(block(self.in_channels, out_channels, stride))
        self.in_channels = out_channels
        for _ in range(1, blocks):
            layers.append(block(out_channels, out_channels))
        return nn.Sequential(*layers)

    def forward(self, x):
        x = self.conv1(x)
        x = self.bn1(x)
        x = self.relu(x)
        x = self.maxpool(x)
        # print(x.shape)

        x = self.res_layers(x)

        x = self.avgpool(x)
        x = torch.flatten(x, 1)
        x = self.fc(x)
        return x

def plot_training_history(history):
    import matplotlib.pyplot as plt

    plt.figure(figsize=(12, 4))
    plt.subplot(1, 3, 1)
    plt.plot(history["train_loss"], label="Train Loss")
    plt.plot(history["val_loss"], label="Val Loss")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.legend()
    plt.subplot(1, 3, 2)
    plt.plot(history["val_accuracy"], label="Val Accuracy")
    plt.xlabel("Epoch")
    plt.ylabel("Accuracy")
    plt.legend()
    plt.show()

def train_one_epoch(model, data_loader, optimizer, criterion, device):
    model.train()
    running_loss = 0.0
    for images, labels in data_loader:
        images, labels = images.to(device), labels.to(device)

        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item()
    return running_loss / len(data_loader)

def validate(model, data_loader, criterion, device):
    model.eval()
    running_loss = 0.0
    correct = 0
    total = 0

    with torch.no_grad():
        for images, labels in data_loader:
            images, labels = images.to(device), labels.to(device)

            outputs = model(images)
            loss = criterion(outputs, labels)

            running_loss += loss.item()
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

    accuracy = correct / total
    return running_loss / len(data_loader), accuracy

def train_model(model, train_loader, val_loader, optimizer, criterion, num_epochs, device, 
                patience=5, scheduler=None, save_path='checkpoints'):
    os.makedirs(save_path, exist_ok=True)
    history = {
        "train_loss": [],
        "val_loss": [],
        "val_accuracy": []
    }
    
    best_val_acc = 0
    patience_counter = 0
    best_model_path = None
    
    for epoch in range(num_epochs):
        train_loss = train_one_epoch(model, train_loader, optimizer, criterion, device)
        val_loss, val_accuracy = validate(model, val_loader, criterion, device)
        
        history["train_loss"].append(train_loss)
        history["val_loss"].append(val_loss)
        history["val_accuracy"].append(val_accuracy)
        
        print(f'Epoch [{epoch+1}/{num_epochs}], '
              f'Train Loss: {train_loss:.4f}, '
              f'Val Loss: {val_loss:.4f}, '
              f'Val Accuracy: {val_accuracy:.4f}')
        
        # 保存最佳模型
        if val_accuracy > best_val_acc:
            best_val_acc = val_accuracy
            patience_counter = 0
            if best_model_path:
                os.remove(best_model_path)
            best_model_path = os.path.join(save_path, f'best_model_{val_accuracy:.4f}.pth')
            torch.save({
                'epoch': epoch,
                'model_state_dict': model.state_dict(),
                'optimizer_state_dict': optimizer.state_dict(),
                'val_accuracy': val_accuracy,
                'history': history
            }, best_model_path)
        else:
            patience_counter += 1
        
        # 早停
        if patience_counter >= patience:
            print(f'Early stopping after {epoch + 1} epochs')
            break

        # 学习率调度
        if scheduler:
            scheduler.step()
    
    # 保存训练历史到CSV
    import pandas as pd
    history_df = pd.DataFrame(history)
    history_df.to_csv(os.path.join(save_path, 'training_history.csv'), index=False)
    
    plot_training_history(history)
    return history, best_model_path

if __name__ == "__main__":
    torch.cuda.empty_cache()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    file_path = '../../../data/dog-breed-identification'
    train_iter, val_iter, test_iter = load_data(file_path, batch_size=64)
    print("Data Loaded")
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = ResNet(ResidualBlock, [2,3,4,6], num_classes=120)
    model.to(device)
    offical_model = models.resnet18().to(device)
    offical_model.fc = nn.Linear(512, 120).to(device)
    # x = torch.randn(1, 3, 224, 224)
    # y = model(x)
    # print(y.shape)  # 应该输出 torch.Size([1, 120])
    optimizer = torch.optim.SGD(offical_model.parameters(), lr=0.01, momentum=0.9, weight_decay=1e-4)
    scheduler = torch.optim.lr_scheduler.StepLR(optimizer, step_size=30, gamma=0.1)
    criterion = nn.CrossEntropyLoss()
    num_epochs = 100

    # x = torch.randn(1, 3, 224, 224).to(device)
    # y = model(x)
    # print(y.shape)  # 应该输出 torch.Size([1, 120])
    # for layers in model.res_layers:
    #     x = layers(x)
    #     print(x.shape)
    print("Start training on device:", device)
    train_model(offical_model, train_iter, val_iter, optimizer, criterion, num_epochs, device, patience=10)
