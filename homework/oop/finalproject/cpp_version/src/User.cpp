#include "../include/User.h"
#include <iostream>

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