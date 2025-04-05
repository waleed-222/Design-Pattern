#include <iostream>

class PaymentProcessor {
public:
  virtual void validate() = 0;
  virtual void process(double amount) = 0;
  virtual ~PaymentProcessor() = default;

  void sendReceipt() { std::cout << "Sending receipt via email\n"; }
  void complete() { std::cout << "Payment completed\n"; }

  void processPayment(double amount) {
    validate();
    process(amount);
    sendReceipt();
    complete();
  }
};

class CreditCardPayment : public PaymentProcessor {
public:
  void validate() override {
    std::cout << "Validating credit Card details...\n";
  }
  void process(double amount) override {
    std::cout << "Processing Credit Card payment of $" << amount << std::endl;
  }
};

class PayPalPayment : public PaymentProcessor {
public:
  void validate() override {
    std::cout << "Validating PayPal account details...\n";
  }
  void process(double amount) override {
    std::cout << "Processing PayPal payment of $" << amount << std::endl;
  }
};

int main() {
  PaymentProcessor *payment1 = new CreditCardPayment();
  payment1->processPayment(100);
  std::cout << "--------------------------------------\n";

  PaymentProcessor *payment2 = new PayPalPayment();
  payment2->processPayment(200);

  delete payment1;
  delete payment2;

  return 0;
}