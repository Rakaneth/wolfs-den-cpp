#pragma once

class Command {
public:
  virtual int execute(Creature& actor) = 0; // returns cost of action
};

class MoveCommand : public Command {
public:
  MoveCommand(int x, int y) : _x(x), _y(y) {}
  MoveCommand(Pos p) : MoveCommand(p.x, p.y) {}
  virtual int execute(Creature& actor) override;

protected:
  int _x, _y;
};

class MoveByCommand : public MoveCommand {
public:
  MoveByCommand(int dx, int dy) : MoveCommand(dx, dy) {}
  int execute(Creature& actor) override;
};

class WaitCommand : public Command {
public:
  int execute(Creature& actor) override { return 100; }
};