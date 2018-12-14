#include "main.hpp"

template <typename T>
void Manager<T>::remove(std::shared_ptr<T> item) {
  auto it = std::remove(_list.begin(), _list.end(), item);
  _list.erase(it, _list.end());
}

bool UpkeepManager::process() {
	for (auto& item : _list)
    if (item->upkeep)
      item->tick();
	
	return true;
}