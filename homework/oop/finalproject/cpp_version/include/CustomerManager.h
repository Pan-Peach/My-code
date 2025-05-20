#pragma once
#include <iostream>
#include "Manager.h"
#include "User.h"

class CustomerManager : public Manager<Customer> {
private:

public:
    CustomerManager() = default;
    ~CustomerManager() override = default;

    bool findAccount(const string& account) {
        for (const auto& customer : dataList) {
            if (customer->getAccount() == account) {
                return true;
            }
        }
        return false;
    }
    bool cmpPassword(const string& account, const string& password) {
        for (const auto& customer : dataList) {
            if (customer->getAccount() == account && customer->getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    friend class ContainedPackageManager;
};