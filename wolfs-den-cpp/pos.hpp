#pragma once

struct Pos {
  Pos(int x, int y) : x(x), y(y) {}
  int x, y;
};

int distance(const Pos& a, const Pos& b);
int toIndex(const Pos& pt, int width);
Pos fromIndex(int idx, int width);
bool operator==(const Pos& a, const Pos& b);

typedef std::vector<Pos> PosList;
