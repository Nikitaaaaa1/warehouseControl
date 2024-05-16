#include "Product.h"

using namespace std;

int Product::nextId = 1; 

Product::Product(int id, const string& name, double price)
    : id(id), name(name), price(price) {}

int Product::getId() const { return id; }
const string& Product::getName() const { return name; }
double Product::getPrice() const { return price; }

void Product::saveToFile(ofstream& file) const {
    file << id << " " << name << " " << price << "\n";
}

Product Product::loadFromFile(ifstream& file) {
    int id;
    string name;
    double price;
    file >> id >> name >> price;
    if (id >= nextId && id > 0) {
        nextId = id + 1;
    }
    return Product(id, name, price);
}
