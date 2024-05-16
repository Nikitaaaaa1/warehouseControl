#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>

using namespace std;

class Product {
public:
    Product(int id, const string& name, double price);
    static int nextId;

    int getId() const;
    const string& getName() const;
    double getPrice() const;

    void saveToFile(ofstream& file) const;
    static Product loadFromFile(ifstream& file);

private:
    int id;
    string name;
    double price;
};

#endif
