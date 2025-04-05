#include <iostream>
#include <stdexcept>
#include <vector>

class Memento {
private:
  std::string state;

public:
  explicit Memento(std::string state) : state(std::move(state)) {}

  std::string getState() const { return state; }
};

class TextEditor {
private:
  std::string text;

public:
  void write(const std::string &newText) { text += newText; }
  void showText() const { std::cout << "Current Text: " << text << std::endl; }
  Memento save() const { return Memento(text); }
  void restore(const Memento &memento) { text = memento.getState(); }
};

class History {
private:
  std::vector<Memento> snapshots;

public:
  void save(const Memento &memento) { snapshots.push_back(memento); }
  Memento undo() {
    if (snapshots.empty()) {
      throw std::runtime_error("No previous state to restore!");
    }
    Memento lastState = snapshots.back();
    snapshots.pop_back();
    return lastState;
  }
};

int main() {
  TextEditor editor;
  History history;

  editor.write("Hello, ");
  history.save(editor.save()); // Save state
  editor.showText();

  editor.write("World!");
  history.save(editor.save()); // Save state
  editor.showText();

  std::cout << "\nUndoing last change...\n";
  editor.restore(history.undo());
  editor.showText();

  std::cout << "\nUndoing another change...\n";
  editor.restore(history.undo());
  editor.showText();

  return 0;
}