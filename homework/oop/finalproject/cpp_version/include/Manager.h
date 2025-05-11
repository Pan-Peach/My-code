#pragma once
#include <list>
#include <unordered_map>
#include <memory>
using namespace std;
template<typename T>
class Manager {
private:
    static Manager* instance;    // 静态成员变量，存储唯一实例
    Manager() = default;         // 构造函数私有化，防止外部创建实例

public:
    virtual ~Manager() = default;
    static Manager* getInstance() {
        if (instance == nullptr) {
            instance = new Manager();  // 第一次调用时创建实例
        }
        return instance;              // 返回唯一实例
    }
    virtual void saveData() = 0;
    virtual void loadData() = 0;
};
