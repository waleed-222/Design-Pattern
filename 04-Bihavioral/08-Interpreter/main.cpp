#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Expression {
public:
  virtual int interpret() const = 0;
  virtual ~Expression() = default;
};

class NumberExpression : public Expression {
private:
  int value;

public:
  explicit NumberExpression(int val) : value(val) {}
  int interpret() const override { return value; }
};

class AddExpression : public Expression {
private:
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> right;

public:
  AddExpression(std::unique_ptr<Expression> left,
                std::unique_ptr<Expression> right)
      : left(std::move(left)), right(std::move(right)) {}
  int interpret() const override {
    return left->interpret() + right->interpret();
  }
};

class SubtractExpression : public Expression {
private:
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> right;

public:
  SubtractExpression(std::unique_ptr<Expression> left,
                     std::unique_ptr<Expression> right)
      : left(std::move(left)), right(std::move(right)) {}
  int interpret() const override {
    return left->interpret() - right->interpret();
  }
};

std::unique_ptr<Expression> parseExpression(const std::string &input) {
  std::istringstream stream(input);
  std::vector<std::unique_ptr<Expression>> expressions;
  std::string token;
  while (stream >> token) {
    if (token == "+") {
      if (expressions.size() < 2)
        throw std::runtime_error("Invalid expression");
      auto right = std::move(expressions.back());
      expressions.pop_back();
      auto left = std::move(expressions.back());
      expressions.pop_back();
      expressions.push_back(
          std::make_unique<AddExpression>(std::move(left), std::move(right)));
    } else if (token == "-") {
      if (expressions.size() < 2)
        throw std::runtime_error("Invalid expression");
      auto right = std::move(expressions.back());
      expressions.pop_back();
      auto left = std::move(expressions.back());
      expressions.pop_back();
      expressions.push_back(std::make_unique<SubtractExpression>(
          std::move(left), std::move(right)));
    } else {
      expressions.push_back(
          std::make_unique<NumberExpression>(std::stoi(token)));
    }
  }
  if (expressions.size() != 1)
    throw std::runtime_error("Invalid expression format");
  return std::move(expressions.back());
}

int main() {
  std::string input = "5 3 + 2 -"; // Equivalent to (5 + 3 - 2)

  try {
    auto expression = parseExpression(input);
    std::cout << "Result: " << expression->interpret() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}