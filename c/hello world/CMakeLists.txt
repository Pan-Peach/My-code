cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(HelloWorldProject)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# 添加源文件
set(SOURCES
    test.c
    hello_world.c
)

# 添加可执行文件
add_executable(HelloWorldExecutable ${SOURCES})