#include "../include/ExpressManager.h"
#include <iostream>

int main(){
    WorkerManager WorkerManager;
    string  WorkerFile = "../data/test_worker.txt";
    WorkerManager.setFilename(WorkerFile);
    WorkerManager.loadData();
    WorkerManager.viewAll();
    Worker test("test", "password");
    test.setId(WorkerManager.getNextId());
    WorkerManager.addData(make_shared<Worker>(test));
    WorkerManager.saveData();
    return 0;
}