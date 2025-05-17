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
    list<shared_ptr<T>> dataList;          // 存储数据的列表
    unordered_map<int, shared_ptr<T>> dataMap; // 存储数据的哈希表
    string filename; // 文件名
    int nextId = 0;

public:
    Manager() = default; // 默认构造函数
    virtual ~Manager() = default;

    virtual void saveData();
    virtual void loadData();
    virtual void addData(const shared_ptr<T> data);
    virtual void removeData(int id);
    virtual shared_ptr<T> getData(int id);
    virtual int getNextId() ;

    virtual void setFilename(const string& filename);
  
    void viewAll();

    friend class Admin;
};

#include "Manager.inl" 
