#include <iostream>
#include <memory>

class PaymentStrategy {
public:
  virtual void pay(double amount) = 0;
  virtual ~PaymentStrategy() = default;
};

class CreditCardPayment : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Processing Credit card payment of $" << amount << std::endl;
  }
};

class PayPalPayment : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Processing PayPal payment of $" << amount << std::endl;
  }
};

class BitCoinPayment : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Processing BitCoin payment of $" << amount << std::endl;
  }
};

class PaymentProcessor {
private:
  std::shared_ptr<PaymentStrategy> strategy;

public:
  void setStrategy(std::shared_ptr<PaymentStrategy> newStrategy) {
    strategy = newStrategy;
  }
  void processorPayment(double amount) {
    if (strategy) {
      strategy->pay(amount);
    } else {
      std::cout << "No payment strategy set!\n";
    }
  }
};

int main() {
  PaymentProcessor processor;

  // Pay with Credit Card
  processor.setStrategy(std::make_shared<CreditCardPayment>());
  processor.processorPayment(100.0);

  // Pay with PayPal
  processor.setStrategy(std::make_shared<PayPalPayment>());
  processor.processorPayment(50.0);

  // pay with BitCoin
  processor.setStrategy(std::make_shared<BitCoinPayment>());
  processor.processorPayment(30.0);

  return 0;
}