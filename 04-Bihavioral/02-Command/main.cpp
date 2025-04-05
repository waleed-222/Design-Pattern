#include <iostream>
#include <vector>

class Command {
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual ~Command() = default;
};

class Light {
public:
  void turnOn() { std::cout << "Light Turn On\n"; }
  void turnOff() { std::cout << "Light Turn Off\n"; }
};

class LightOnCommand : public Command {
public:
  LightOnCommand(Light &l) : light(l) {}
  void execute() override { light.turnOn(); }
  void undo() override { light.turnOff(); }

private:
  Light light;
};

class LightOffCommand : public Command {
public:
  LightOffCommand(Light &l) : light(l) {}
  void execute() override { light.turnOff(); }
  void undo() override { light.turnOn(); }

private:
  Light light;
};

class Switch {
public:
  void executeCommand(Command *cmd) {
    cmd->execute();
    history.push_back(cmd);
  }
  void undoLastCommand() {
    if (!history.empty()) {
      history.back()->undo();
      history.pop_back();
    }
  }

private:
  std::vector<Command *> history;
};

int main() {
  Light light;
  LightOnCommand turnOn(light);
  LightOffCommand turnOff(light);

  Switch lightswitch;

  lightswitch.executeCommand(&turnOn);
  lightswitch.executeCommand(&turnOff);
  std::cout << "Undoing last command\n";
  lightswitch.undoLastCommand();

  return 0;
}