#ifndef PERSON_HPP
#define PERSON_HPP

#include <memory>
#include <string>

class Person {
public:
  Person(const std::string &name, int age);
  ~Person();
  void introduce() const;

private:
  class PersonImpl;
  std::unique_ptr<PersonImpl> pImpl;
};

#endif