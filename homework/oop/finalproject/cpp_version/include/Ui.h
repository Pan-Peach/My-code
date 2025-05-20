#pragma once

#include <string>

using namespace std;

class Ui {
private:

    int mode;
    int currentUserId;
public:
    Ui() = default;
    void pause();
    void clearScreen();
    void displayMainMenu();
    void displayLoginMenu();
    void displayRegisterMenu();
    void displayAdminMenu();
    void displayCustomerMenu();
    void displayWorkerMenu();
    void displayPackageMenu();
    void displayContainedPackageMenu();
    void displaySearchPackageMenu();
    void displaySearchContainedPackageMenu();
    void displaySearchCustomerMenu();
    void displaySearchManagerMenu();
    void displaySearchUserMenu();
};