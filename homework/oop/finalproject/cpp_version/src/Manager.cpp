#include "../include/Manager.h"
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
void Manager<T>::addData(const shared_ptr<T> data) {
    dataList.push_back(data);
    dataMap[data->getId()] = data;
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
    FILE* file = fopen(filename.c_str(), "w");
    if (file == nullptr) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    for (const auto& data : dataList) {
        // Assuming T has a method to serialize itself
        data->serialize(file);
    }
    cout << "Data saved." << endl;
    fclose(file);
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