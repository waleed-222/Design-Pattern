#include <iostream>

class Coffee {
public:
  virtual ~Coffee() = default;
  virtual double getCost() const = 0;
  virtual std::string getDescription() const = 0;
};

class SimpleCoffee : public Coffee {
  double getCost() const override { return 5.0; }
  std::string getDescription() const override{ return "Simple Coffee"; }
};

class CoffeeDecorator : public Coffee {
public:
  CoffeeDecorator(const Coffee &coffee) : wrapperCoffee(coffee) {}

protected:
  const Coffee &wrapperCoffee;
};

class Sugar : public CoffeeDecorator {
public:
  Sugar(const Coffee &coffee) : CoffeeDecorator(coffee) {}
  double getCost() const override { return wrapperCoffee.getCost() + 0.5; }
  std::string getDescription() const override {
    return wrapperCoffee.getDescription() + " ,Sugar";
  }
};

class Milk : public CoffeeDecorator {
public:
  Milk(const Coffee &coffee) : CoffeeDecorator(coffee) {}
  double getCost() const override { return wrapperCoffee.getCost() + 1.5; }
  std::string getDescription() const override {
    return wrapperCoffee.getDescription() + " ,Milk";
  }
};

int main() {
  SimpleCoffee basecoffee;
  Milk milk(basecoffee);
  Sugar sugar(milk);
  std::cout << sugar.getDescription() << " -$" << sugar.getCost() << std::endl;
  return 0;
}