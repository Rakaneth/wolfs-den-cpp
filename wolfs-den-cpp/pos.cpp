#include "main.hpp"

int distance(const Pos& a, const Pos& b) {
  return std::max(abs(a.x - b.x), abs(a.y - b.y));
}

int toIndex(const Pos& pt, int width) { return pt.x + pt.y * width; }

Pos fromIndex(int idx, int width) { return Pos{idx % width, idx / width}; }

bool operator==(const Pos& a, const Pos& b) { return a.x == b.x && a.y == b.y; }

std::ostream& operator<<(std::ostream& out, const Pos& pos) {
  return out << pos.x << ',' << pos.y;
}
