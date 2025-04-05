#ifndef EMPLOYEECONTROLLER_HPP
#define EMPLOYEECONTROLLER_HPP

#include "employee.hpp"
#include "employeeview.hpp"

class EmployeeController {
private:
  Employee model;
  EmployeeView view;

public:
  EmployeeController(const Employee &emp, const EmployeeView &view);
  void updateView() const;
  void setEmployeeName(const std::string &name);
  void setEmployeeAge(int age);
};
#endif // !EMPLOYEECONTROLLER_HPP
