#include "person.hpp"
#include <iostream>
#include <memory>

class Person::PersonImpl {
public:
  std::string name;
  int age;

  PersonImpl(const std::string &name, int age) : name(name), age(age) {}
  void introduce() const {
    std::cout << "Hi, I'm " << name << " and I'm " << age << " years old."
              << std::endl;
  }
};

Person::Person(const std::string &name, int age)
    : pImpl(std::make_unique<PersonImpl>(name, age)) {}
Person::~Person() = default;

void Person::introduce() const { pImpl->introduce(); }