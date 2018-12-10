#include "main.hpp"

ScreenManager::ScreenManager() : _curScreen(nullptr) {}
ScreenManager::~ScreenManager() {
	delete _curScreen;
}
void ScreenManager::registerScreen(Screen* screen) {
	_screenMap[screen->getName()] = screen;
}

void ScreenManager::setScreen(std::string screenID) {
	if (_curScreen != nullptr)
		_curScreen->exit();

	_curScreen = _screenMap[screenID];
	_curScreen->enter();
}

Screen& ScreenManager::getCurScreen() { return *_curScreen; }