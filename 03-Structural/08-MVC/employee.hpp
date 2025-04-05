#include <string>

#ifndef Employee_HPP
#define Employee_HPP

class Employee {
private:
  std::string name;
  int age;

public:
  Employee(const std::string &name, int size);
  std::string getName() const;
  int getAge() const;
  void setName(const std::string &newName);
  void setAge(int newAge);
};

#endif