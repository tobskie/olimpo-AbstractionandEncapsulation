#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <cctype>
using namespace std;

class Employee {
private:
    int id;
    string name;

public:
    Employee(int id, string name) : id(id), name(name) {}
    virtual double calculateSalary() const = 0;
    virtual void display() const = 0;
    int getID() const { return id; }
    string getName() const { return name; }
    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee {
private:
    double salary;
public:
    FullTimeEmployee(int id, string name, double salary) : Employee(id, name), salary(salary) {}
    double calculateSalary() const override { return salary; }
    void display() const override {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n";
    }
};

class PartTimeEmployee : public Employee {
private:
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(int id, string name, double hourlyWage, int hoursWorked)
        : Employee(id, name), hourlyWage(hourlyWage), hoursWorked(hoursWorked) {}
    double calculateSalary() const override { return hourlyWage * hoursWorked; }
    void display() const override {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
    }
};

class ContractualEmployee : public Employee {
private:
    double paymentPerProject;
    int projectsCompleted;
public:
    ContractualEmployee(int id, string name, double paymentPerProject, int projectsCompleted)
        : Employee(id, name), paymentPerProject(paymentPerProject), projectsCompleted(projectsCompleted) {}
    double calculateSalary() const override { return paymentPerProject * projectsCompleted; }
    void display() const override {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")\n";
        cout << "Contract Payment Per Project: $" << paymentPerProject << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
    }
};

vector<unique_ptr<Employee>> employees;

bool isUniqueID(int id) {
    for (const auto &emp : employees) {
        if (emp->getID() == id) return false;
    }
    return true;
}

int getValidID() {
    int id;
    while (true) {
        cout << "Enter ID: ";
        cin >> id;
        if (cin.fail() || id <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID! Please enter a positive number.\n";
            continue;
        }
        if (!isUniqueID(id)) {
            cout << "Duplicate ID! Try another.\n";
            continue;
        }
        return id;
    }
}

string getValidStringInput(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        getline(cin, input);
        bool isValid = true;
        for (char c : input) {
            if (isdigit(c)) {
                isValid = false;
                break;
            }
        }
        if (!isValid || input.empty()) {
            cout << "Invalid input! Please enter a valid string.\n";
            continue;
        }
        return input;
    }
}

double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive number.\n";
            continue;
        }
        return value;
    }
}

void addFullTimeEmployee() {
    int id = getValidID();
    string name = getValidStringInput("Enter Name: ");
    double salary = getValidDoubleInput("Enter Fixed Monthly Salary: ");
    employees.push_back(make_unique<FullTimeEmployee>(id, name, salary));
    cout << "Employee added successfully!\n";
}

void addPartTimeEmployee() {
    int id = getValidID();
    string name = getValidStringInput("Enter Name: ");
    double hourlyWage = getValidDoubleInput("Enter Hourly Wage: ");
    int hoursWorked = static_cast<int>(getValidDoubleInput("Enter Hours Worked: "));
    employees.push_back(make_unique<PartTimeEmployee>(id, name, hourlyWage, hoursWorked));
    cout << "Employee added successfully!\n";
}

void addContractualEmployee() {
    int id = getValidID();
    string name = getValidStringInput("Enter Name: ");
    double paymentPerProject = getValidDoubleInput("Enter Contract Payment Per Project: ");
    int projectsCompleted = static_cast<int>(getValidDoubleInput("Enter Number of Projects Completed: "));
    employees.push_back(make_unique<ContractualEmployee>(id, name, paymentPerProject, projectsCompleted));
    cout << "Employee added successfully!\n";
}

void displayPayrollReport() {
    if (employees.empty()) {
        cout << "\nNo employees in the system yet.\n";
        return;
    }
    cout << "\n------ Employee Payroll Report ------\n";
    for (const auto &emp : employees) {
        emp->display();
        cout << "\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nMenu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Try again.\n";
            continue;
        }
        switch (choice) {
            case 1: addFullTimeEmployee(); break;
            case 2: addPartTimeEmployee(); break;
            case 3: addContractualEmployee(); break;
            case 4: displayPayrollReport(); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
