#include <iostream>
#include <memory>

class Amplifier {
public:
    void on() { std::cout << "Amplifier: Turning on...\n"; }
    void off() { std::cout << "Amplifier: Turning off...\n"; }
};

class DVDPlayer {
public:
    void on() { std::cout << "DVD Player: Turning on...\n"; }
    void off() { std::cout << "DVD Player: Turning off...\n"; }
    void play(const std::string& movie) { std::cout << "DVD Player: Playing \"" << movie << "\"...\n"; }
    void stop() { std::cout << "DVD Player: Stopping playback...\n"; }
    void eject() { std::cout << "DVD Player: Ejecting disc...\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector: Turning on...\n"; }
    void off() { std::cout << "Projector: Turning off...\n"; }
    void setInput(const std::string& source) { std::cout << "Projector: Setting input to " << source << "\n"; }
};

class HomeTheater {
public:
    HomeTheater()
        : amplifier(std::make_shared<Amplifier>()),
          dvdPlayer(std::make_shared<DVDPlayer>()),
          projector(std::make_shared<Projector>()) {}

    void watchMovie(const std::string& movie) {
        std::cout << "\n--- Starting Movie Night: " << movie << " ---\n";
        amplifier->on();
        projector->on();
        projector->setInput("DVD Player");
        dvdPlayer->on();
        dvdPlayer->play(movie);
        std::cout << "Enjoy your movie!\n";
    }

    void endMovie() {
        std::cout << "\n--- Ending Movie Night ---\n";
        dvdPlayer->stop();
        dvdPlayer->eject();
        dvdPlayer->off();
        projector->off();
        amplifier->off();
        std::cout << "Goodbye!\n";
    }

private:
    std::shared_ptr<Amplifier> amplifier;
    std::shared_ptr<DVDPlayer> dvdPlayer;
    std::shared_ptr<Projector> projector;
};

int main() {
    HomeTheater homeTheater;
    homeTheater.watchMovie("Inception");
    homeTheater.endMovie();
    return 0;
}
