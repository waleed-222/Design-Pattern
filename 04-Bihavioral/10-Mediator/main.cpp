#include <iostream>
#include <memory>
#include <string>
#include <vector>

class User;

class ChatMediator {
public:
  virtual void sendMessage(const std::string &message, User *sender) = 0;
  virtual void addUser(std::shared_ptr<User> user) = 0;
  virtual ~ChatMediator() = default;
};

class ChatRoom : public ChatMediator {
private:
  std::vector<std::shared_ptr<User>> users;

public:
  void addUser(std::shared_ptr<User> user) override { users.push_back(user); }
  void sendMessage(const std::string &message, User *sender) override;
};

class User {
protected:
  std::string name;
  ChatMediator *chatRoom;

public:
  User(const std::string &name, ChatMediator *mediator)
      : name(name), chatRoom(mediator) {}
  virtual void send(const std::string &message) {
    std::cout << name << " sends:" << message << std::endl;
    chatRoom->sendMessage(message, this);
  }

  virtual void receive(const std::string &message,
                       const std::string &senderName) {
    std::cout << name << " receive from " << senderName << ":" << message
              << std::endl;
  }

  std::string getName() const { return name; }
};

void ChatRoom::sendMessage(const std::string &message, User *sender) {
  for (auto &user : users) {
    if (user.get() != sender) {
      user->receive(message, sender->getName());
    }
  }
}

int main() {
  ChatRoom chatRoom;

  auto user1 = std::make_shared<User>("Alice", &chatRoom);
  auto user2 = std::make_shared<User>("Bob", &chatRoom);
  auto user3 = std::make_shared<User>("Charlie", &chatRoom);

  chatRoom.addUser(user1);
  chatRoom.addUser(user2);
  chatRoom.addUser(user3);

  user1->send("Hello, everyone!");
  user2->send("Hi Alice!");
  user3->send("Hey folks!");

  return 0;
}