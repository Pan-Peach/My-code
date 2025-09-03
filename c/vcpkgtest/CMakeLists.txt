
cmake_minimum_required(VERSION 3.15)

project(vcpkgtest)

set(CMAKE_C_STANDARD 11)

set(
    SOURCES
    "main.c"
)

find_package(check CONFIG REQUIRED)

add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:Check::check>,Check::check,Check::checkShared>)

# 添加以下内容以生成测试文件
enable_testing()

set(
    TEST_SOURCES
    "test_main.c"
)

add_executable(test_main ${TEST_SOURCES})

target_link_libraries(test_main PRIVATE $<IF:$<TARGET_EXISTS:Check::check>,Check::check,Check::checkShared>)

add_test(NAME test_main COMMAND test_main)