#include "Customer.h"

using namespace std;

int Customer::nextId = 1; 

Customer::Customer(int id, const string& name, const string& address)
    : id(id), name(name), address(address) {}

int Customer::getId() const { return id; }
const string& Customer::getName() const { return name; }
const string& Customer::getAddress() const { return address; }

void Customer::saveToFile(ofstream& file) const {
    file << id << " " << name << " " << address << "\n";
}

Customer Customer::loadFromFile(ifstream& file) {
    int id;
    string name, address;
    file >> id >> name >> address;
    if (id >= nextId && id > 0) {
        nextId = id + 1;
    }
    return Customer(id, name, address);
}
