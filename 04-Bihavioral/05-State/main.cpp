#include <algorithm>
#include <iostream>
#include <memory>

class TrafficLightContext;

class TrafficLightState {
public:
  virtual void handle(TrafficLightContext &context) = 0;
  virtual std::string getStateName() = 0;
  virtual ~TrafficLightState() = default;
};

class TrafficLightContext {
private:
  std::unique_ptr<TrafficLightState> state;

public:
  TrafficLightContext(std::unique_ptr<TrafficLightState> initialState)
      : state(std::move(initialState)) {}

  void setState(std::unique_ptr<TrafficLightState> newState) {
    state = std::move(newState);
  }

  void request() { state->handle(*this); }

  std::string getCurrentState() { return state->getStateName(); }
};

class RedState : public TrafficLightState {
public:
  void handle(TrafficLightContext &context) override;
  std::string getStateName() override { return "Red"; };
};

class GreenState : public TrafficLightState {
public:
  void handle(TrafficLightContext &context) override;
  std::string getStateName() override { return "Green"; };
};

class YellowState : public TrafficLightState {
public:
  void handle(TrafficLightContext &context) override;
  std::string getStateName() override { return "Yellow"; };
};

void RedState::handle(TrafficLightContext &context) {
  std::cout << "Red light -> changing to Green\n";
  context.setState(std::make_unique<GreenState>());
}

void GreenState::handle(TrafficLightContext &context) {
  std::cout << "Green light -> changing to Yellow\n";
  context.setState(std::make_unique<YellowState>());
}

void YellowState::handle(TrafficLightContext &context) {
  std::cout << "Yellow light -> changing to Red\n";
  context.setState(std::make_unique<RedState>());
}

int main() {
  TrafficLightContext trafficlight(std::make_unique<RedState>());

  for (int i = 0; i < 5; i++) {
    std::cout << "Current State:" << trafficlight.getCurrentState()
              << std::endl;
    trafficlight.request();
  }

  return 0;
}