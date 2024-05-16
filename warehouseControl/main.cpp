#include <iostream>
#include <sstream>
#include <limits>
#include "Warehouse.h"
#include "SignalHandler.h"


using namespace std;

void showMenu() {
    cout << "Commands:\n";
    cout << "  1. Add product\n";
    cout << "  2. Add employee\n";
    cout << "  3. Add customer\n";
    cout << "  4. Add invoice\n";
    cout << "  5. List products\n";
    cout << "  6. List employees\n";
    cout << "  7. List customers\n";
    cout << "  8. List invoices\n";
    cout << "  9. Load data\n";
    cout << "  10. Exit\n";
}

void addProduct(Warehouse& warehouse) {
    int id = Product::nextId++;
    string name;
    double price;

    cout << "Enter product name: ";
    getline(cin, name);

    cout << "Enter product price: ";
    cin >> price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    warehouse.addProduct(Product(id, name, price));
    cout << "Product added with ID " << id << ".\n";
}

void addEmployee(Warehouse& warehouse) {
    int id = Employee::nextId++;
    string name, position;

    cout << "Enter employee name: ";
    getline(cin, name);

    cout << "Enter employee position: ";
    getline(cin, position);

    warehouse.addEmployee(Employee(id, name, position));
    cout << "Employee added with ID " << id << ".\n";
}

void addCustomer(Warehouse& warehouse) {
    int id = Customer::nextId++;
    string name, address;

    cout << "Enter customer name: ";
    getline(cin, name);

    cout << "Enter customer address: ";
    getline(cin, address);

    warehouse.addCustomer(Customer(id, name, address));
    cout << "Customer added with ID " << id << ".\n";
}

void addInvoice(Warehouse& warehouse) {
    int id = Invoice::nextId++;
    int customerId, employeeId;
    double totalAmount;
    string customerName, employeeName;
    vector<int> productIds;

    cout << "Available customers:\n";
    for (const auto& customer : warehouse.getCustomers()) {
        cout << "ID: " << customer.getId() << ", Name: " << customer.getName() << "\n";
    }
    cout << "Enter customer ID: ";
    cin >> customerId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Available employees:\n";
    for (const auto& employee : warehouse.getEmployees()) {
        cout << "ID: " << employee.getId() << ", Name: " << employee.getName() << "\n";
    }
    cout << "Enter employee ID: ";
    cin >> employeeId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter total amount: ";
    cin >> totalAmount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Available products:\n";
    for (const auto& product : warehouse.getProducts()) {
        cout << "ID: " << product.getId() << ", Name: " << product.getName() << ", Price: $" << product.getPrice() << "\n";
    }
    int productId;
    cout << "Enter product IDs (enter -1 to finish): ";
    while (true) {
        cin >> productId;
        if (productId == -1) break;
        productIds.push_back(productId);
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (const auto& customer : warehouse.getCustomers()) {
        if (customer.getId() == customerId) {
            customerName = customer.getName();
            break;
        }
    }

    for (const auto& employee : warehouse.getEmployees()) {
        if (employee.getId() == employeeId) {
            employeeName = employee.getName();
            break;
        }
    }

    warehouse.addInvoice(Invoice(id, customerId, employeeId, productIds, totalAmount, customerName, employeeName));
    cout << "Invoice added with ID " << id << ".\n";
}

void listProducts(const Warehouse& warehouse) {
    cout << "Products:\n";
    for (const auto& product : warehouse.getProducts()) {
        cout << "ID: " << product.getId() << ", Name: " << product.getName() << ", Price: $" << product.getPrice() << "\n";
    }
}

void listEmployees(const Warehouse& warehouse) {
    cout << "Employees:\n";
    for (const auto& employee : warehouse.getEmployees()) {
        cout << "ID: " << employee.getId() << ", Name: " << employee.getName() << ", Position: " << employee.getPosition() << "\n";
    }
}

void listCustomers(const Warehouse& warehouse) {
    cout << "Customers:\n";
    for (const auto& customer : warehouse.getCustomers()) {
        cout << "ID: " << customer.getId() << ", Name: " << customer.getName() << ", Address: " << customer.getAddress() << "\n";
    }
}

void listInvoices(const Warehouse& warehouse) {
    cout << "Invoices:\n";
    for (const auto& invoice : warehouse.getInvoices()) {
        cout << "ID: " << invoice.getId() << ", Customer: " << invoice.getCustomerName() << ", Employee: " << invoice.getEmployeeName() << ", Total Amount: $" << invoice.getTotalAmount() << "\n";
        cout << "Products: ";
        for (const int productId : invoice.getProductIds()) {
            for (const auto& product : warehouse.getProducts()) {
                if (product.getId() == productId) {
                    cout << product.getName() << " ";
                    break;
                }
            }
        }
        cout << "\n";
    }
}

void loadData(Warehouse& warehouse) {
    try {
        warehouse.loadFromFile();
        cout << "Data loaded.\n";
    }
    catch (const exception& e) {
        cout << "Error loading data: " << e.what() << "\n";
    }
}

void processCommand(Warehouse& warehouse, int command) {
    switch (command) {
    case 1:
        addProduct(warehouse);
        break;
    case 2:
        addEmployee(warehouse);
        break;
    case 3:
        addCustomer(warehouse);
        break;
    case 4:
        addInvoice(warehouse);
        break;
    case 5:
        listProducts(warehouse);
        break;
    case 6:
        listEmployees(warehouse);
        break;
    case 7:
        listCustomers(warehouse);
        break;
    case 8:
        listInvoices(warehouse);
        break;
    case 9:
        loadData(warehouse);
        break;
    case 10:
        exit(0);
    default:
        cout << "Unknown command.\n";
    }
}

int main() {
    Warehouse warehouse("Main Warehouse");

    SignalHandler::setupSignalHandler([&warehouse](int signum) {
        cout << "\nInterrupt signal (" << signum << ") received. Exiting program...\n";
        warehouse.saveToFile();
        exit(signum);
        });

    warehouse.loadFromFile();

    int command;

    while (true) {
        showMenu();
        cout << "> ";
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        processCommand(warehouse, command);
    }

    return 0;
}
