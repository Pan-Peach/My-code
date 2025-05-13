#include "../include/User.h"
#include <iostream>

void Worker::serialize(FILE* file) {
    fprintf(file, "%s %d %s\n",
    account.c_str(), id, password.c_str()
    );
}
void Worker::deserialize(FILE* file) {
    
}

void Worker::display() {
    cout << "Account: " << account << endl;
    cout << "ID: " << id << endl;
    cout << "Password: " << password << endl;
}