#include <iostream>
#include <memory>

class Handler {
protected:
  std::shared_ptr<Handler> nextHandler;

public:
  virtual ~Handler() = default;
  void setNext(std::shared_ptr<Handler> next) { nextHandler = next; }
  virtual void handleRequest(const std::string &issue) {
    if (nextHandler) {
      nextHandler->handleRequest(issue);
    } else {
      std::cout << "No department can handle this issue\n";
    }
  }
};

class BillingSupport : public Handler {
public:
  void handleRequest(const std::string &issue) override {
    if (issue == "billing") {
      std::cout << "Billing team handling the issue\n";
    } else {
      Handler::handleRequest(issue);
    }
  }
};

class TechnicalService : public Handler {
public:
  void handleRequest(const std::string &issue) override {
    if (issue == "technical") {
      std::cout << "Technical Service handling the issue\n";
    } else {
      Handler::handleRequest(issue);
    }
  }
};

class CustomerService : public Handler {
public:
  void handleRequest(const std::string &issue) override {
    if (issue == "general") {
      std::cout << "Customer Service handling the issue\n";
    } else {
      Handler::handleRequest(issue);
    }
  }
};

int main() {
  auto billing = std::make_shared<BillingSupport>();
  auto technical = std::make_shared<TechnicalService>();
  auto customerService = std::make_shared<CustomerService>();

  customerService->setNext(technical);
  technical->setNext(billing);

  customerService->handleRequest("technical");
  customerService->handleRequest("billing");
  customerService->handleRequest("general");

  return 0;
}