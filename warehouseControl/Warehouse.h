#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <string>
#include "Product.h"
#include "Employee.h"
#include "Customer.h"
#include "Invoice.h"

using namespace std;

class Warehouse {
public:
    Warehouse(const string& name);

    void addProduct(const Product& product);
    void addEmployee(const Employee& employee);
    void addCustomer(const Customer& customer);
    void addInvoice(const Invoice& invoice);

    const vector<Product>& getProducts() const;
    const vector<Employee>& getEmployees() const;
    const vector<Customer>& getCustomers() const;
    const vector<Invoice>& getInvoices() const;

    void saveToFile() const;
    void loadFromFile();

private:
    string name;
    vector<Product> products;
    vector<Employee> employees;
    vector<Customer> customers;
    vector<Invoice> invoices;
};

#endif 
