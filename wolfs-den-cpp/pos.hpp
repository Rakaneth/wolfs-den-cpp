#pragma once

struct Pos {
  Pos() = default;
  Pos(int x, int y) : x(x), y(y) {}
  int x, y;
};

int distance(const Pos& a, const Pos& b);
int toIndex(const Pos& pt, int width);
Pos fromIndex(int idx, int width);
bool operator==(const Pos& a, const Pos& b);
std::ostream& operator<<(std::ostream& out, const Pos& pos);

typedef std::vector<Pos> PosList;
