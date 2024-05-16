#ifndef INVOICE_H
#define INVOICE_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Invoice {
public:
    Invoice(int id, int customerId, int employeeId, const vector<int>& productIds, double totalAmount, const string& customerName, const string& employeeName);
    static int nextId;

    int getId() const;
    int getCustomerId() const;
    int getEmployeeId() const;
    const vector<int>& getProductIds() const;
    double getTotalAmount() const;
    const string& getCustomerName() const;
    const string& getEmployeeName() const;

    void saveToFile(ofstream& file) const;
    static Invoice loadFromFile(ifstream& file);

private:
    int id;
    int customerId;
    int employeeId;
    vector<int> productIds;
    double totalAmount;
    string customerName;
    string employeeName;
};

#endif 
