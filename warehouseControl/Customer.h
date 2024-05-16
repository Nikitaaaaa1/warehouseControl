#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <fstream>

using namespace std;

class Customer {
public:
    Customer(int id, const string& name, const string& address);
    static int nextId;

    int getId() const;
    const string& getName() const;
    const string& getAddress() const;

    void saveToFile(ofstream& file) const;
    static Customer loadFromFile(ifstream& file);

private:
    int id;
    string name;
    string address;
};

#endif 
