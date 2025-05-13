#include "../include/ExpressManager.h"
#include <iostream>

int main(){
    WorkerManager WorkerManager;
    string  WorkerFile = "../data/test_worker.txt";
    WorkerManager.setFilename(WorkerFile);
    WorkerManager.loadData();

    return 0;
}