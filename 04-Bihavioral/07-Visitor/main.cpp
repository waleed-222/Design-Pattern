#include <iostream>
#include <vector>

class Engineer;
class Manager;

class EmployeeVistor {
public:
  virtual void visit(Engineer *engineer) = 0;
  virtual void visit(Manager *manager) = 0;
  virtual ~EmployeeVistor() = default;
};

class Employee {
public:
  virtual void accept(EmployeeVistor *vistor) = 0;
  virtual ~Employee() = default;
};

class Engineer : public Employee {
public:
  void accept(EmployeeVistor *vistor) override { vistor->visit(this); }
};

class Manager : public Employee {
public:
  void accept(EmployeeVistor *vistor) override { vistor->visit(this); }
};

class SalaryCalculator : public EmployeeVistor {
public:
  void visit(Engineer *engineer) override {
    std::cout << "Calculating salary for Engineer...\n";
  }
  void visit(Manager *manager) override {
    std::cout << "Calculating salary for Manager...\n";
  }
};

class PerformanceEvaluator : public EmployeeVistor {
public:
  void visit(Engineer *engineer) override {
    std::cout << "Evaluating Engineer performance...\n";
  }
  void visit(Manager *manager) override {
    std::cout << "Evaluating Manager performance...\n";
  }
};

int main() {
  std::vector<Employee *> employees = {new Engineer(), new Manager()};

  SalaryCalculator salaryCalculator;
  PerformanceEvaluator performanceCalculator;

  std::cout << "Processing Salaries:\n";
  for (Employee *emp : employees) {
    emp->accept(&salaryCalculator);
  }
  std::cout << "\nProcessing Performance Evaluations:\n";
  for (Employee *emp : employees) {
    emp->accept(&performanceCalculator);
  }

  for (Employee *emp : employees) {
    delete emp;
  }
  return 0;
}