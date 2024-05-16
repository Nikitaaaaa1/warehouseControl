#include "Employee.h"

using namespace std;

int Employee::nextId = 1; 

Employee::Employee(int id, const string& name, const string& position)
    : id(id), name(name), position(position) {}

int Employee::getId() const { return id; }
const string& Employee::getName() const { return name; }
const string& Employee::getPosition() const { return position; }

void Employee::saveToFile(ofstream& file) const {
    file << id << " " << name << " " << position << "\n";
}

Employee Employee::loadFromFile(ifstream& file) {
    int id;
    string name, position;
    file >> id >> name >> position;
    if (id >= nextId && id > 0) {
        nextId = id + 1;
    }
    return Employee(id, name, position);
}
