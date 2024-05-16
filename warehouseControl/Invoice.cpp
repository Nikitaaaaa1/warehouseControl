#include "Invoice.h"

using namespace std;

int Invoice::nextId = 1;

Invoice::Invoice(int id, int customerId, int employeeId, const vector<int>& productIds, double totalAmount, const string& customerName, const string& employeeName)
    : id(id), customerId(customerId), employeeId(employeeId), productIds(productIds), totalAmount(totalAmount), customerName(customerName), employeeName(employeeName) {}

int Invoice::getId() const { return id; }
int Invoice::getCustomerId() const { return customerId; }
int Invoice::getEmployeeId() const { return employeeId; }
const vector<int>& Invoice::getProductIds() const { return productIds; }
double Invoice::getTotalAmount() const { return totalAmount; }
const string& Invoice::getCustomerName() const { return customerName; }
const string& Invoice::getEmployeeName() const { return employeeName; }

void Invoice::saveToFile(ofstream& file) const {
    file << id << " " << customerId << " " << employeeId << " "
        << totalAmount << " " << customerName << " " << employeeName << "\n";
    for (const auto& productId : productIds) {
        file << productId << " ";
    }
    file << "\n";
}

Invoice Invoice::loadFromFile(ifstream& file) {
    int id, customerId, employeeId;
    double totalAmount;
    string customerName, employeeName;
    vector<int> productIds;
    file >> id >> customerId >> employeeId >> totalAmount >> customerName >> employeeName;
    int productId;
    while (file >> productId) {
        productIds.push_back(productId);
        if (file.peek() == '\n' || file.peek() == EOF) {
            break;
        }
    }
    if (id >= nextId && id > 0) {
        nextId = id + 1;
    }
    return Invoice(id, customerId, employeeId, productIds, totalAmount, customerName, employeeName);
}
