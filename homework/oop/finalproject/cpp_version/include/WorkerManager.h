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

    bool findAccount(const string& account) {
        for (const auto& worker : dataList) {
            if (worker->getAccount() == account) {
                return true;
            }
        }
        return false;
    }
    bool cmpPassword(const string& account, const string& password) {
        for (const auto& worker : dataList) {
            if (worker->getAccount() == account && worker->getPassword() == password) {
                return true;
            }
        }
        return false;
    }
};
