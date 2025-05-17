#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <climits>  
#include <algorithm>
#include "User.h"
#include "Item.h"
using namespace std;

template <typename T>
void Manager<T>::addData(const shared_ptr<T> data) {
    int id = data->getId();
    if(dataList.empty()){
        dataList.push_back(data);
        dataMap[data->getId()] = data;
        cout<<"Data with ID " << data->getId() << " added." << endl;
        return;
    }
    int lId=dataList.front()->getId();
    int rId=dataList.back()->getId();
    dataMap[data->getId()] = data;
    if(id<lId){
        dataList.push_front(data);
    }
    else if(id>rId){
        dataList.push_back(data);
    }
    else{
        auto it = find_if(dataList.begin(), dataList.end(), [id](const shared_ptr<T>& d) { return d->getId() > id; });
        dataList.insert(it, data);
    }
    cout<<"Data with ID " << data->getId() << " added." << endl;
}

template <typename T>
void Manager<T>::removeData(int id) {
    auto it = dataMap.find(id);
    if (it != dataMap.end()) {
        dataList.remove(it->second);
        dataMap.erase(it);
    }
    else{
        cout<<"Data with ID " << id << " not found." << endl;
    }
}


template <typename T>
void Manager<T>::saveData() {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    
    for (const auto& data : dataList) {
        fout << data->serialize() << endl;
    }

    cout << "Data saved." << endl;
    fout.close();
}

template <typename T>
void Manager<T>::loadData(){
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }
    
    string line;
    while (getline(fin, line)) {
        if(line.empty()) continue; // Skip empty lines
        shared_ptr<T> data = make_shared<T>();
        data->deserialize(line);
        addData(data);
    }

    cout << "Data loaded." << endl;
    fin.close();
}

template <typename T>
void Manager<T>::viewAll() {
    for (const auto& data : dataList) {
        // Assuming T has a method to display itself
        data->display();
    }
}

template <typename T>
void Manager<T>::setFilename(const string& filename) {
    this->filename = filename;
}

template <typename T>
shared_ptr<T> Manager<T>::getData(int id) {
    auto it = dataMap.find(id);
    if (it != dataMap.end()) {
        return it->second;
    }
    else {
        cout << "Data with ID " << id << " not found." << endl;
        return nullptr;
    }
}

template <typename T>
int Manager<T>::getNextId() {
    while(dataMap.find(nextId) != dataMap.end()) {
        nextId++;
        if(nextId == INT_MAX){
            throw overflow_error("ID overflow");
            return -1;
        }
    }
    return nextId;
}