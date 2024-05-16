#include "Warehouse.h"
#include <fstream>
#include <stdexcept>

using namespace std;

Warehouse::Warehouse(const string& name) : name(name) {}

void Warehouse::addProduct(const Product& product) {
    products.push_back(product);
    saveToFile();
}

void Warehouse::addEmployee(const Employee& employee) {
    employees.push_back(employee);
    saveToFile();
}

void Warehouse::addCustomer(const Customer& customer) {
    customers.push_back(customer);
    saveToFile();
}

void Warehouse::addInvoice(const Invoice& invoice) {
    invoices.push_back(invoice);
    saveToFile();
}

const vector<Product>& Warehouse::getProducts() const {
    return products;
}

const vector<Employee>& Warehouse::getEmployees() const {
    return employees;
}

const vector<Customer>& Warehouse::getCustomers() const {
    return customers;
}

const vector<Invoice>& Warehouse::getInvoices() const {
    return invoices;
}

void Warehouse::saveToFile() const {
    ofstream productFile("products.txt");
    if (!productFile.is_open()) {
        throw runtime_error("Failed to open products file for writing");
    }
    for (const auto& product : products) {
        product.saveToFile(productFile);
    }

    ofstream employeeFile("employees.txt");
    if (!employeeFile.is_open()) {
        throw runtime_error("Failed to open employees file for writing");
    }
    for (const auto& employee : employees) {
        employee.saveToFile(employeeFile);
    }

    ofstream customerFile("customers.txt");
    if (!customerFile.is_open()) {
        throw runtime_error("Failed to open customers file for writing");
    }
    for (const auto& customer : customers) {
        customer.saveToFile(customerFile);
    }

    ofstream invoiceFile("invoices.txt");
    if (!invoiceFile.is_open()) {
        throw runtime_error("Failed to open invoices file for writing");
    }
    for (const auto& invoice : invoices) {
        invoice.saveToFile(invoiceFile);
    }
}

void Warehouse::loadFromFile() {
    products.clear();
    employees.clear();
    customers.clear();
    invoices.clear();

    ifstream productFile("products.txt");
    if (productFile.is_open()) {
        while (productFile.peek() != EOF) {
            Product product = Product::loadFromFile(productFile);
            if (product.getId() > 0) {
                products.push_back(product);
            }
        }
    }

    ifstream employeeFile("employees.txt");
    if (employeeFile.is_open()) {
        while (employeeFile.peek() != EOF) {
            Employee employee = Employee::loadFromFile(employeeFile);
            if (employee.getId() > 0) {
                employees.push_back(employee);
            }
        }
    }

    ifstream customerFile("customers.txt");
    if (customerFile.is_open()) {
        while (customerFile.peek() != EOF) {
            Customer customer = Customer::loadFromFile(customerFile);
            if (customer.getId() > 0) {
                customers.push_back(customer);
            }
        }
    }

    ifstream invoiceFile("invoices.txt");
    if (invoiceFile.is_open()) {
        while (invoiceFile.peek() != EOF) {
            Invoice invoice = Invoice::loadFromFile(invoiceFile);
            if (invoice.getId() > 0) {
                invoices.push_back(invoice);
            }
        }
    }
}
