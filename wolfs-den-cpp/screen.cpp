#include "main.hpp"

Screen::Screen(std::string name): _name(name) {}
Screen::~Screen() {}
std::string Screen::getName() const { return _name; }
void Screen::enter() { std::cout << "Entered " << _name << " screen."; }
void Screen::exit() { std::cout << "Exited " << _name << " screen."; }
void Screen::border(TCODConsole& cons, std::string caption) {
	static int topleft = 0xC9;
	static int topright = 0xBB;
	static int botleft = 0xC8;
	static int botright = 0xBc;
	static int horz = 0xCD;
	static int vert = 0xBA;
	int xmax = cons.getWidth() - 1;
	int ymax = cons.getHeight() - 1;

	for (int x = 1; x <= xmax; x++) {
		cons.putChar(x, 0, horz);
		cons.putChar(x, ymax, horz);
	}

	for (int y = 1; y <= ymax; y++) {
		cons.putChar(0, y, vert);
		cons.putChar(xmax, y, vert);
	}

	cons.putChar(0, 0, topleft);
	cons.putChar(0, ymax, botleft);
	cons.putChar(xmax, 0, topright);
	cons.putChar(xmax, ymax, botright);

	if (caption != "")
		cons.printf(1, 0, caption.c_str());
}