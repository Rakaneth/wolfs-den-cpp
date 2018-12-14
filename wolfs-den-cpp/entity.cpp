#include "main.hpp"

int Entity::_counter = 0;

Entity::Entity(const std::shared_ptr<World>& world, int layer)
  : _world(world), _id(++_counter), _x(0), _y(0), _layer(layer) {}

void Entity::move(int x, int y) {
  _x = x;
  _y = y;
  getMap().dirty = true;
}

void Entity::removeTag(std::string tag) {
  _tags.erase(std::remove(_tags.begin(), _tags.end(), tag));
}

bool Entity::hasTag(std::string tag) {
  for (auto& t : _tags)
    if (t == tag)
      return true;

  return false;
}

Pos Entity::pos() { return Pos{_x, _y}; }

GameMap& Entity::getMap() {
  auto tmp = _world.lock();
  return tmp->getMap(mapID);
}

const int Item::INFINITE = -1;

Item::Item(const std::shared_ptr<World>& world, ItemType type, int uses)
  : Entity(world, 1), _uses(uses), _type(type) {}
