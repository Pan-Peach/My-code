import os
import pandas as pd, ast, pathlib, numpy as np
import pandas as pd, ast
from PIL import Image, ImageDraw
from ultralytics import YOLO
from pathlib import Path



def testdata():
    df = pd.read_csv(f'{path}/train.csv')
    row0=df.iloc[0]
    print(row0)
    img = Image.open(f'{path}/train/{row0.image_id}.jpg')
    bbox=ast.literal_eval(row0.bbox)
    draw = ImageDraw.Draw(img)
    draw.rectangle((bbox[0], bbox[1], bbox[0]+bbox[2], bbox[1]+bbox[3]), outline='red', width=5)
    img.save('test.png')

def data_to_yolo(path):
    df = pd.read_csv(f'{path}/train.csv')
    for i, row in df.iterrows():
        img = Image.open(f'{path}/train/{row.image_id}.jpg')
        w, h = img.size

def train(path):
    model = YOLO("yolov8n.pt")  # load a pretrained model (recommended for training)
    model.train(data=f"{path}/wheat.yaml", epochs=10, imgsz=640, batch=16, name="wheat-yolov8n")

def testpath(path):
    yaml_path = Path('../../../data/global-wheat/yolo/wheat.yaml').resolve()
    train_dir = yaml_path.parent / 'images/train'
    val_dir   = yaml_path.parent / 'images/val'

    print('yaml 绝对路径:', yaml_path)
    print('train 目录存在？', train_dir.exists(), train_dir)
    print('val   目录存在？', val_dir.exists(), val_dir)

def predict(img_path):
    model = YOLO(f"runs/detect/wheat-yolov8n3/weights/best.pt")  # load a pretrained model (recommended for training)
    results_df = pd.DataFrame(columns=['image_id', 'PredictionString'])
    #results = model.predict(source=f"{img_path}/test", conf=0.25, save=True, save_txt=True, project='predict', name='wheat-yolov8n')
    test_images = list(Path(f"{img_path}/test").glob('*.jpg'))
    
    for img_file in test_images:
        image_id = img_file.stem
        results = model.predict(source=str(img_file), conf=0.25)[0]
        if(len(results.boxes))>0:
            prediction = []
            for box in results.boxes:
                cls = int(box.cls[0])
                conf = box.conf[0]
                x1, y1, x2, y2 = box.xyxy[0]
                w = x2 - x1
                h = y2 - y1
                pred_str = f"{conf:.4f} {x1:.2f} {y1:.2f} {w:.2f} {h:.2f}"
                new_row = {'image_id': image_id, 'PredictionString': pred_str}
                results_df = pd.concat([results_df, pd.DataFrame([new_row])], ignore_index=True)
    
    return results_df

def draw_pre_boxes(img_path, results):
    
    output_dir = Path('predict_imgs')
    output_dir.mkdir(exist_ok=True)
    
    for image_id in results['image_id'].unique():
        img = Image.open(f'{img_path}/test/{image_id}.jpg')
        draw = ImageDraw.Draw(img)
        image_preds = results[results['image_id'] == image_id]

        for _, row in image_preds.iterrows():
            conf,x1,y1,w,h = map(float, row['PredictionString'].split())
            x2, y2 = x1 + w, y1 + h
            draw.rectangle((x1, y1, x2, y2), outline='red', width=5)
            draw.text((x1, y1), f"{conf:.2f}", fill='red')
        img.save(output_dir / f"{image_id}.png")
if __name__ == '__main__':
    path = '../../../data/global-wheat/yolo'
    img_path = '../../../data/global-wheat'
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    #testpath(path)
    #train(path)
    result_df = predict(img_path)
    result_df.to_csv(f'{path}/submission.csv', index=False)
    draw_pre_boxes(img_path, result_df)
