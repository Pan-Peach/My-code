#pragma once
#include "Manager.h"
#include "User.h"

class WorkerManager : public Manager<Worker> {
public:
    WorkerManager() = default;
    ~WorkerManager() override = default;



    void saveData() override;
    void loadData() override;
    void addData(const shared_ptr<Worker> data) override;
    void removeData(int id) override;
    void setFilename(const string& filename) override;
    shared_ptr<Worker> getData(int id) override;

};
