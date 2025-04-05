#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class Iterator {
public:
  virtual bool hasNext() = 0;
  virtual int next() = 0;
  virtual ~Iterator() = default;
};

class NumberIterator : public Iterator {
private:
  std::vector<int> collection;
  size_t index;

public:
  explicit NumberIterator(std::vector<int> numbers)
      : collection(std::move(numbers)), index(0) {}
  bool hasNext() override { return index < collection.size(); }
  int next() override {
    if (hasNext()) {
      return collection[index++];
    }
    throw std::out_of_range("No more elements");
  }
};

class IterableCollction {
public:
  virtual std::unique_ptr<Iterator> createIterator() = 0;
  virtual ~IterableCollction() = default;
};

class NumberCollection : public IterableCollction {
private:
  std::vector<int> numbers;

public:
  void addNumber(int num) { numbers.push_back(num); }
  std::unique_ptr<Iterator> createIterator() override {
    return std::make_unique<NumberIterator>(numbers);
  }
};

int main() {
  NumberCollection numbers;
  numbers.addNumber(10);
  numbers.addNumber(20);
  numbers.addNumber(30);
  numbers.addNumber(40);

  auto iterator = numbers.createIterator();

  std::cout << "Iterating over collection:\n";
  while (iterator->hasNext()) {
    std::cout << iterator->next() << " ";
  }
  std::cout << std::endl;

  return 0;
}