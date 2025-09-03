import matplotlib.pyplot as plt

 
def plot_model(history):
    """
    绘制训练和验证的损失值和准确率
    :param history: 训练过程中记录的历史数据
    """
    # 绘制训练 & 验证的损失值
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(history.history['loss'], label='训练损失')
    plt.plot(history.history['val_loss'], label='验证损失')
    plt.title('训练和验证的损失值')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()

    # 绘制训练 & 验证的准确率
    plt.subplot(1, 2, 2)
    plt.plot(history.history['accuracy'], label='训练准确率')
    plt.plot(history.history['val_accuracy'], label='验证准确率')
    plt.title('训练和验证的准确率')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()

    plt.show()
