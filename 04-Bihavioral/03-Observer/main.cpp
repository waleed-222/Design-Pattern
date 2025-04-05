#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Observer {
public:
  virtual void update(float temperature) = 0;
  virtual ~Observer() = default;
};

class WeatherStation {
private:
  std::vector<std::shared_ptr<Observer>> observers;
  float temperature;

public:
  void addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
  }
  void removeObserver(const std::shared_ptr<Observer>& observer) {
    observers.erase(std::remove_if(observers.begin(), observers.end(),
                                   [&](const std::shared_ptr<Observer>& obs) {
                                       return obs == observer;
                                   }),
                    observers.end());
}

  void setTemperature(float temp) {
    temperature = temp;
    notifyObservers();
  }
  void notifyObservers() {
    for (auto observer : observers) {
      observer->update(temperature);
    }
  }
};

class ScreenDisplay : public Observer {
public:
  void update(float temperature) override {
    std::cout << "Screen Display: Temperature updated to " << temperature
              << "°C\n";
  }
};

class FileLogger : public Observer {
public:
  void update(float temperature) override {
    std::cout << "File Logger: Logging tempeature " << temperature << "°C\n";
  }
};

int main() {
  auto station = std::make_shared<WeatherStation>();

  auto screen = std::make_shared<ScreenDisplay>();
  auto logger = std::make_shared<FileLogger>();

  station->addObserver(screen);
  station->addObserver(logger);

  station->setTemperature(25.0);
  station->setTemperature(30.5);

  station->removeObserver(screen);
  station->setTemperature(28.0);

  return 0;
}
