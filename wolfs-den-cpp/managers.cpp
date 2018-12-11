#include "main.hpp"

template <typename T>
void Manager<T>::remove(std::shared_ptr<T> item) {
	_list.erase(std::remove(_list.begin(), _list.end(), item));
}

bool UpkeepManager::process() {
	for (auto& item : _list)
		item->tick();
	
	return true;
}