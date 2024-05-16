#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <fstream>

using namespace std;

class Employee {
public:
    Employee(int id, const string& name, const string& position);
    static int nextId;

    int getId() const;
    const string& getName() const;
    const string& getPosition() const;

    void saveToFile(ofstream& file) const;
    static Employee loadFromFile(ifstream& file);

private:
    int id;
    string name;
    string position;
};

#endif 
