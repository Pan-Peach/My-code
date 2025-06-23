#pragma once
#include "User.h"
#include "Manager.h"    

class AdminManager : public Manager<Admin> {

public:
   AdminManager() = default;
   ~AdminManager() override = default;
   
   bool findAccount(const string& account) {
       for (const auto& admin : dataList) {
           if (admin->getAccount() == account) {
               return true;
           }
       }
       return false;
   }

   shared_ptr<Admin> cmpPassword(const string& account, const string& password) {
       for (const auto& admin : dataList) {
           if (admin->getAccount() == account && admin->getPassword() == password) {
               return admin;
           }
       }
       return nullptr;
   }
};