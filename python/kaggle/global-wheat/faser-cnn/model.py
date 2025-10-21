import torch
import torchvision
from PIL import Image
import random
import pandas as pd
import torchvision.transforms.functional as F
import torchvision.transforms as T
from torchvision.models.detection import FasterRCNN
import os

class WheatDataset(torch.utils.data.Dataset):
    def __init__(self, dataframe, image_dir, transforms=None):
        """
        Args:
            dataframe: 读取的DataFrame，包含‘image_id’，‘bbox’等列。
            image_dir: 图片所在的根目录。
            transforms: 图像增强变换。
        """
        self.df = dataframe
        self.image_dir = image_dir
        self.transforms = transforms
        
        # 因为一张图可能有多个框，我们需要按图片名分组
        self.image_ids = dataframe['image_id'].unique()

        self.base_transform = T.ToTensor()
    
    def __getitem__(self, idx):
        # 1. 获取图片id和对应的所有标注
        image_id = self.image_ids[idx]
        image_path = f"{self.image_dir}/{image_id}.jpg"
        image = Image.open(image_path).convert("RGB")
        
        # 2. 获取该图片的所有标注行
        records = self.df[self.df['image_id'] == image_id]
        
        # 3. 解析bbox。CSV里的bbox可能是字符串，如“[x, y, width, height]”
        boxes = []
        for _, record in records.iterrows():
            # 假设bbox是字符串，需要解析
            bbox_str = record['bbox']
            # 去掉括号，分割成列表
            bbox_list = list(map(float, bbox_str.strip('[]').split(',')))
            x, y, w, h = bbox_list
            
            # Faster R-CNN需要[x_min, y_min, x_max, y_max]格式
            x_min, y_min, x_max, y_max = x, y, x + w, y + h
            boxes.append([x_min, y_min, x_max, y_max])
        
        # 转换为Tensor
        boxes = torch.as_tensor(boxes, dtype=torch.float32)
        
        # 4. 创建标签。我们只有“小麦头”一类，所以全是1（背景是0）
        labels = torch.ones((len(boxes),), dtype=torch.int64)
        
        # 5. 创建目标字典（Faster R-CNN规定的格式）
        target = {}
        target['boxes'] = boxes
        target['labels'] = labels
        target['image_id'] = torch.tensor([idx])
        
        # 6. 数据增强（如果有）
        if self.transforms is not None:
            # 注意：transforms需要同时处理image和boxes
            image, target = self.transforms(image, target)
        else:
            image = self.base_transform(image)
        
        return image, target

    def __len__(self):
        return len(self.image_ids)
    
class WheatDetectionTransforms:
    """
    训练阶段增强：
        - 随机水平翻转
        - 随机颜色抖动
        - 随机 expand + crop
    验证阶段只做 resize。
    """
    def __init__(self, resize_size=(800, 800), train=True):
        self.resize_size = resize_size
        self.train = train

    def __call__(self, image, target):
        # ---------- 训练阶段才做增强 ----------
        if self.train:
            # 1. 随机水平翻转
            if random.random() < 0.5:
                image = F.hflip(image)
                if 'boxes' in target and len(target['boxes']):
                    w, _ = image.size          # PIL size -> (W, H)
                    boxes = target['boxes'].clone()
                    boxes[:, [0, 2]] = w - boxes[:, [2, 0]]   # x_min/max 镜像
                    target['boxes'] = boxes

            # 2. 颜色抖动
            if random.random() < 0.5:
                image = F.adjust_brightness(image, brightness_factor=random.uniform(0.8, 1.2))
                image = F.adjust_contrast(image,   contrast_factor=random.uniform(0.8, 1.2))
                image = F.adjust_saturation(image, saturation_factor=random.uniform(0.8, 1.2))

            # 3. 随机 expand + crop
            if random.random() < 0.5:
                image, target = self._random_expand_crop(image, target)

        # ---------- 通用：PIL -> Tensor + Resize ----------
        original_size = image.size[::-1]          # (H, W)
        image = F.to_tensor(image)                # 0-1, C×H×W
        image = F.resize(image, self.resize_size)
        new_size = image.shape[-2:]

        # ---------- 同步 box ----------
        if 'boxes' in target and len(target['boxes']):
            scale_y = new_size[0] / original_size[0]
            scale_x = new_size[1] / original_size[1]
            boxes = target['boxes'].clone()
            boxes[:, [0, 2]] *= scale_x
            boxes[:, [1, 3]] *= scale_y
            target['boxes'] = boxes

        return image, target

    # ------------- 辅助：随机 expand + crop -------------
    def _random_expand_crop(self, image, target, min_crop_iou=0.5):
        """
        先随机 expand（周围填 0），再随机 crop 一块，保证与任一框 IoU 不小于 min_crop_iou
        """
        w, h = image.size
        boxes = target['boxes'].clone()
        labels = target.get('labels', None)

        # 1. expand 比例
        expand_ratio = random.uniform(1.0, 1.5)
        new_w, new_h = int(w * expand_ratio), int(h * expand_ratio)
        left = random.randint(0, new_w - w)
        top  = random.randint(0, new_h - h)

        expand_img = Image.new('RGB', (new_w, new_h), (0, 0, 0))
        expand_img.paste(image, (left, top))

        # 2. 框坐标平移
        boxes[:, [0, 2]] += left
        boxes[:, [1, 3]] += top

        # 3. 随机 crop 若干次，直到满足 IoU 条件
        max_attempts = 50
        for _ in range(max_attempts):
            crop_ratio = random.uniform(0.5, 1.0)
            crop_w, crop_h = int(new_w * crop_ratio), int(new_h * crop_ratio)
            crop_x = random.randint(0, new_w - crop_w)
            crop_y = random.randint(0, new_h - crop_h)

            crop_box = torch.tensor([[crop_x, crop_y, crop_x + crop_w, crop_y + crop_h]], dtype=torch.float32)
            ious = torchvision.ops.box_iou(crop_box, boxes).squeeze(0)   # 两者都是 (N,4)
            if ious.numel() == 0 or ious.max() >= min_crop_iou:
                break
        else:
            # 都没成功，直接原图返回
            return image, target

        # 4. 真正 crop
        crop_img = expand_img.crop((crop_x, crop_y, crop_x + crop_w, crop_y + crop_h))
        boxes -= torch.tensor([crop_x, crop_y, crop_x, crop_y], dtype=torch.float32)
        boxes[:, [0, 2]].clamp_(min=0, max=crop_w)
        boxes[:, [1, 3]].clamp_(min=0, max=crop_h)

        # 过滤掉被裁没的框
        keep = (boxes[:, 2] - boxes[:, 0]) * (boxes[:, 3] - boxes[:, 1]) > 1.0
        target['boxes'] = boxes[keep]
        if labels is not None:
            target['labels'] = labels[keep]

        # 5. 空框保护：防止 boxes/labels 长度不一致
        if target['boxes'].shape[0] == 0:
            target['boxes']  = torch.empty((0, 4), dtype=torch.float32)
            target['labels'] = torch.empty((0,),   dtype=torch.int64)
        else:
            target['labels'] = labels[keep]   # 已有 keep 索引，直接切片

        return crop_img, target
    
class WheatFasterRCNN(torch.nn.Module):
    def __init__(self, num_classes=2):
        super().__init__()

        self.backbone = torchvision.models.resnet50() 
        self.backbone = torch.nn.Sequential(*list(self.backbone.children())[:-2])
        self.backbone.out_channels = 2048

        self.anchor_generator = torchvision.models.detection.rpn.AnchorGenerator(
            sizes=((8,16,32),),
            aspect_ratios=((0.5, 1.0, 2.0),)
        )

        self.roi_pooler = torchvision.ops.MultiScaleRoIAlign(
            featmap_names=['0'],
            output_size=7,
            sampling_ratio=2
        )
        
        self.model = FasterRCNN(
            backbone=self.backbone,
            num_classes=num_classes,
            rpn_anchor_generator=self.anchor_generator,
            box_roi_pool=self.roi_pooler
        )

    def forward(self, images, targets=None):
        return self.model(images, targets)
    
def train_one_epoch(model, optimizer, data_loader, device, epoch, scaler=None):
    model.train()
    total_loss = 0.0
    for images, targets in data_loader:
        images = list(image.to(device) for image in images)
        targets = [{k: v.to(device) for k, v in t.items()} for t in targets]

        optimizer.zero_grad()
        
        if scaler is not None:
            with torch.amp.autocast(device_type=device.type):
                loss_dict = model(images, targets)
                losses = sum(loss for loss in loss_dict.values())
            scaler.scale(losses).backward()
            scaler.step(optimizer)
            scaler.update()
        else:
            loss_dict = model(images, targets)
            losses = sum(loss for loss in loss_dict.values())
            losses.backward()
            optimizer.step()

        total_loss += losses.item()

    avg_loss = total_loss / len(data_loader)
    print(f"Epoch {epoch}, Loss: {avg_loss:.4f}")
    return avg_loss

def train(model, dataset, device, num_epochs=10, batch_size=4, learning_rate=0.005):
    data_loader = torch.utils.data.DataLoader(dataset, batch_size=batch_size, shuffle=True, collate_fn=lambda x: tuple(zip(*x)))

    model.to(device)
    optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate, momentum=0.9, weight_decay=0.0005)

    scaler = torch.amp.GradScaler() if torch.cuda.is_available() else None  # 混合精度训练
    print("Start training...")
    for epoch in range(num_epochs):
        print(f"Epoch {epoch+1}/{num_epochs}")
        train_one_epoch(model, optimizer, data_loader, device, epoch, scaler=scaler)



if __name__ == "__main__":
    os.chdir(os.path.dirname(__file__))  # 切到脚本目录，避免相对路径问题
    input = '../../../../data/global-wheat/'
    working = './'
    model = WheatFasterRCNN(num_classes=2)
    df = pd.read_csv(os.path.join(input, 'train.csv'))
    dataset = WheatDataset(dataframe=df, image_dir=os.path.join(input, 'train'), transforms=WheatDetectionTransforms(train=True))
    device = torch.device('cuda') if torch.cuda.is_available() else torch.device('cpu')
    train(model, dataset, device, num_epochs=10, batch_size=4, learning_rate=0.005)
    