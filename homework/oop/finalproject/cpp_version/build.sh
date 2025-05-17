#!/bin/bash

# 开启日志输出
set -x  # 显示执行的每个命令
set -e  # 如果任何命令失败则立即退出

echo "开始构建项目..."
echo "清理 build 目录..."
cd build
rm -rf ./*

echo "运行 cmake..."
cmake ..

echo "开始编译..."
make VERBOSE=1

# 检查编译结果
if [ $? -eq 0 ]; then
    echo "构建成功完成！"
else
    echo "构建失败！"
    exit 1
fi