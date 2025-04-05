#include "employeecontroller.hpp"

EmployeeController::EmployeeController(const Employee &emp, const EmployeeView &view):model(emp),view(view){}

void EmployeeController::updateView()const{
    view.displaEmployee(model.getName(), model.getAge());
}

void EmployeeController::setEmployeeName(const std::string& name){model.setName(name);}

void EmployeeController::setEmployeeAge(int age){model.setAge(age);}
