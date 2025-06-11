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




string ContainedPackage::serialize(){
string line = to_string(weight) + " " + to_string(volume) + " " + name + " " + tel + " " + ContainerName+pickupCode + " " + to_string(inAddress) + " " + to_string(outAddress) + " " + "unknown" + " " + code + " " + company + " " + to_string(timestamp) + " " + to_string(id);
    return line;
}
void ContainedPackage::deserialize(string line){
    size_t pos = 0;
    size_t spacepos = line.find(' ');
    weight = stof(line.substr(pos, spacepos - pos));
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    volume = stof(line.substr(pos, spacepos - pos));
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    name = line.substr(pos, spacepos - pos);
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    tel = line.substr(pos, spacepos - pos);
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    ContainerName = line.substr(pos, spacepos - pos);   
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    pickupCode = line.substr(pos, spacepos - pos);
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    inAddress = stoi(line.substr(pos, spacepos - pos));
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    outAddress = stoi(line.substr(pos, spacepos - pos));
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    code = line.substr(pos, spacepos - pos);
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    company = line.substr(pos, spacepos - pos);
    pos = spacepos + 1;
    spacepos = line.find(' ', pos);
    long long time = stoll(line.substr(pos, spacepos - pos));
    timestamp = static_cast<time_t>(time);
    pos = spacepos + 1;
    id = stoi(line.substr(pos));
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
    cout << "Pickup Code: " << pickupCode << endl;
    cout << "ID: " << id << endl;
    cout << "Timestamp: " << ctime(&timestamp); // Convert time_t to string
    cout << "Owner ID: " << OwnerId << endl;
    cout << "\n";
}