#include "employee.hpp"
#include <string>

Employee::Employee(const std::string &name, int age) : name(name), age(age) {}

std::string Employee::getName() const { return name; }
int Employee::getAge() const { return age; }
void Employee::setName(const std::string &newName) { name = newName; }
void Employee::setAge(int newAge) { age = newAge; }