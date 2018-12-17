#include "main.hpp"

int MoveCommand::execute(Creature& actor) {
  //TODO: interactions
  if (actor.getMap().canWalk(_x, _y)) {
    actor.move(_x, _y);
    actor.getMap().dirty = true;
    return std::max(1, 100 - actor.getSpd().getValue());
  } else
    return 0;
}

int MoveByCommand::execute(Creature& actor) { 
  Pos p = actor.pos();
  int x = clamp(p.x + _x, 0, actor.getMap().getWidth() - 1);
  int y = clamp(p.y + _y, 0, actor.getMap().getHeight() - 1);
  MoveCommand temp(x, y);
  return temp.execute(actor);
}
