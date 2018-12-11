#include "main.hpp"

ScreenManager::ScreenManager() : _curScreen(nullptr) {}

void ScreenManager::registerScreen(std::shared_ptr<Screen> screen) {
	_screenMap.insert(std::make_pair(screen->getName(), screen));
}

void ScreenManager::setScreen(std::string screenID) {
	if (_curScreen != nullptr)
		_curScreen->exit();

	_curScreen = _screenMap[screenID];
	_curScreen->enter();
}

Screen& ScreenManager::getCurScreen() { return *_curScreen; }