#include "../include/WorkerManager.h"

void WorkerManager::loadData() {
    Manager<Worker>::loadData();  // 调用基类实现
}

void WorkerManager::saveData() {
    Manager<Worker>::saveData();
}

void WorkerManager::addData(const shared_ptr<Worker> data) {
    Manager<Worker>::addData(data);
}

void WorkerManager::removeData(int id) {
    Manager<Worker>::removeData(id);
}

shared_ptr<Worker> WorkerManager::getData(int id) {
    return Manager<Worker>::getData(id);
}

void WorkerManager::setFilename(const string& filename) {
    Manager<Worker>::setFilename(filename);
}

