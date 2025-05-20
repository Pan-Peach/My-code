#include "../include/User.h"
#include <iostream>



string Admin::serialize() {
    string line = account + " " + password + " " + to_string(id);
    return line;
}

void Admin::deserialize(string line) {
    size_t pos = 0;
    size_t spacePos = line.find(' ');

    account = line.substr(pos, spacePos);

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    password = line.substr(pos, spacePos - pos);

    pos = spacePos + 1;
    id = stoi(line.substr(pos));

}

void Admin::display() const {
    cout << "Account: " << account << endl;
    cout << "ID: " << id << endl;
    cout << "Password: " << password << endl<<endl;
}


Customer::Customer(const string& name, const string& acc, const string& pwd, const int& id, const int& num_OutgoingPackage, const int& num_ContainedPackage, const string& tel) {
    this->name = name;
    this->account = acc;
    this->password = pwd;
    this->id = id;
    this->num_ContainedPackage = num_ContainedPackage;
    this->num_OutgoingPackage = num_OutgoingPackage;
    this->tel = tel;
    CptStarLevel();
    
}

string Customer::serialize() {
    string line = name + " " + account + " " + password + " " + to_string(id) + to_string(num_ContainedPackage) + " " + to_string(num_OutgoingPackage) + " " + tel;
    return line;
}


void Customer::deserialize(string line) {
    size_t pos = 0;
    size_t spacePos = line.find(' ');

    name = line.substr(pos, spacePos);

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    account = line.substr(pos, spacePos - pos);

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    password = line.substr(pos, spacePos - pos);

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    id = stoi(line.substr(pos, spacePos - pos));

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    num_ContainedPackage = stoi(line.substr(pos, spacePos - pos));

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    num_OutgoingPackage = stoi(line.substr(pos, spacePos - pos));

    tel = line.substr(spacePos + 1);

}

void Customer::display() const {
    cout << "Name: " << name << endl;
    cout << "Account: " << account << endl;
    cout << "ID: " << id << endl;
    cout << "Password: " << password << endl;
    cout << "Number of Contained Packages: " << num_ContainedPackage << endl;
    cout << "Number of Outgoing Packages: " << num_OutgoingPackage << endl;
    cout << "Telephone: " << tel << endl;
    cout << "Star Level: " << starLevel << endl<<endl;
}

void Customer::CptStarLevel() {
    int x = num_ContainedPackage + num_OutgoingPackage;
    if (x == 0) starLevel = 0;
    else{
        starLevel = 6 - 5/x;
    }
    return;
}

string Worker::serialize() {
    string line = account + " " + to_string(id) + " " + password;
    return line;
}
void Worker::deserialize(string line) {
    size_t pos = 0;
    size_t spacePos = line.find(' ');

    account = line.substr(pos, spacePos);

    pos = spacePos + 1;
    spacePos = line.find(' ', pos);
    id = stoi(line.substr(pos, spacePos - pos));

    pos = spacePos + 1;
    password = line.substr(pos);

    return;
}

void Worker::display() const {
    cout << "Account: " << account << endl;
    cout << "ID: " << id << endl;
    cout << "Password: " << password << endl<<endl;
}