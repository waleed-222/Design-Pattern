#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Car {
public:
  Car(const std::string &brand, const std::string &model,
      const std::string &engineType)
      : brand(brand), model(model), engineType(engineType) {}

  void displayCarDetails(const std::string &color,
                         const std::string &registerationNumber) {
    std::cout << "Car Details:\n"
              << "Brand:" << brand << std::endl
              << "Model:" << model << std::endl
              << "EngineType:" << engineType << std::endl
              << "Color:" << color << std::endl
              << "Registeration Number:" << registerationNumber << std::endl;
  }

private:
  std::string brand;
  std::string engineType;
  std::string model;
};

class CarFactory {
public:
  std::shared_ptr<Car> getCar(const std::string &brand,
                              const std::string &model,
                              const std::string &engineType) {
    std::string key = getKey(brand, model, engineType);
    if (carpool.find(key) == carpool.end()) {
      std::cout << "Creating a new Car object for: " << key << std::endl;
      carpool[key] = std::make_shared<Car>(brand, model, engineType);
    } else {
      std::cout << "Reusing existing Car object for:" << key << std::endl;
    }
    return carpool[key];
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Car>> carpool;
  std::string getKey(const std::string &brand, const std::string &model,
                     const std::string &engineType) {
    return brand + "_" + model + "_" + engineType;
  }
};

int main() {
  CarFactory carFactory;

  // First request - should create a new car
  auto car1 = carFactory.getCar("Toyota", "Camry", "V6");
  car1->displayCarDetails("Red", "ABC123");
  std::cout << std::endl;
  // Second request - same type, should reuse
  auto car2 = carFactory.getCar("Toyota", "Camry", "V6");
  car2->displayCarDetails("Blue", "XYZ789");
  std::cout << std::endl;
  // Third request - different type, should create a new car
  auto car3 = carFactory.getCar("Honda", "Civic", "I4");
  car3->displayCarDetails("Black", "LMN456");

  return 0;
}