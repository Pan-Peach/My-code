#include "../include/Package.h"
#include <iostream>
#include <string>

string IncomingPackage::serialize(){

}
void IncomingPackage::deserialize(string line){

}
void IncomingPackage::display()const {
}


string OutgoingPackage::serialize(){

}
void OutgoingPackage::deserialize(string line){

}
void OutgoingPackage::display() const {

}


ContainedPackage::ContainedPackage(float w, float v, const string& cName, Container* c)
    : Package(w, v, "", "", 0, 0), ContainerName(cName), container(c) {
    // Constructor implementation
}

string ContainedPackage::serialize(){

}
void ContainedPackage::deserialize(string line){

}
void ContainedPackage::display() const {
    cout << "Contained Package:" << endl;
    cout << "Container Name: " << ContainerName << endl;
    cout << "Weight: " << weight << endl;
    cout << "Volume: " << volume << endl;
    cout << "Code: " << code << endl;
    cout << "Company: " << company << endl;
    cout << "Out Address: " << outAddress << endl;
    cout << "In Address: " << inAddress << endl;
}