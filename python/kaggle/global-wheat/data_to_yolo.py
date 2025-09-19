import pandas as pd
import numpy as np
import os
from tqdm import tqdm
import shutil
import ast
from PIL import Image

seed = 42
path = '../../../data/global-wheat'

def gen_txt(row):
    bbox = ast.literal_eval(row.bbox)
    w = row.width
    h = row.height
    x_center = (bbox[0] + bbox[2] / 2) / w
    y_center = (bbox[1] + bbox[3] / 2) / h
    width = bbox[2] / w
    height = bbox[3] / h
    return f"0 {x_center} {y_center} {width} {height}\n"

def data_to_yolo(path):
    df = pd.read_csv(f'{path}/train.csv')
    np.random.seed(seed)
    img_ids = df['image_id'].unique()
    np.random.shuffle(img_ids)
    n = len(img_ids)
    n_train = int(n * 0.8)
    n_val = n-n_train
    train_ids = img_ids[:n_train]
    val_ids = img_ids[n_train:]
    df['split'] = df['image_id'].apply(lambda x: 'train' if x in train_ids else 'val')
    for i, row in tqdm(df.iterrows(), total=len(df)):
        name = row.image_id
        img = Image.open(f'{path}/train/{row.image_id}.jpg')
        w, h = img.size
        row.width = w
        row.height = h
        txt_content = gen_txt(row)
        if row.split == 'train':
            img_dir = f'{path}/yolo/images/train'
            txt_dir = f'{path}/yolo/labels/train'
        elif row.split == 'val':
            img_dir = f'{path}/yolo/images/val'
            txt_dir = f'{path}/yolo/labels/val'
        with open(f'{txt_dir}/{name}.txt', 'a') as f:
            f.write(txt_content)
        if not os.path.exists(f'{img_dir}/{name}.jpg'):
            shutil.copy(f'{path}/train/{name}.jpg', f'{img_dir}/{name}.jpg')

os.chdir(os.path.dirname(os.path.abspath(__file__)))
data_to_yolo(path)
