#include "main.hpp"

Screen::Screen(std::string name): _name(name) {}
Screen::~Screen() {}
std::string Screen::getName() const { return _name; }
void Screen::enter() { std::cout << "Entered " << _name << " screen."; }
void Screen::exit() { std::cout << "Exited " << _name << " screen."; }