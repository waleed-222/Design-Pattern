#include "employeeview.hpp"
#include <iostream>

void EmployeeView::displaEmployee(const std::string &name, int age) const {
  std::cout << "Employee:" << name << ", Age:" << age<<std::endl;
}