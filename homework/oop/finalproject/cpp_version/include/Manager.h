#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include <string>
using namespace std;

class Admin; // 前向声明

template<typename T>
class Manager {
protected:
    // static Manager* instance;    // 静态成员变量，存储唯一实例
    // Manager() = default;         // 构造函数私有化，防止外部创建实例
    list<shared_ptr<T>> dataList;          // 存储数据的列表
    unordered_map<int, shared_ptr<T>> dataMap; // 存储数据的哈希表
    string filename; // 文件名

    void viewAll();
    

public:
    Manager() = default; // 默认构造函数
    virtual ~Manager() = default;
    // static Manager* getInstance() {
    //     if (instance == nullptr) {
    //         instance = new Manager();  // 第一次调用时创建实例
    //     }
    //     return instance;              // 返回唯一实例
    // }

    virtual void saveData();
    virtual void loadData();
    virtual void addData(const shared_ptr<T> data);
    virtual void removeData(int id);
    virtual shared_ptr<T> getData(int id);

    virtual void setFilename(const string& filename);
  

    friend class Admin;
};
