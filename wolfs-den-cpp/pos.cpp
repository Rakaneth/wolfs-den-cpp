#include "main.hpp"

int distance(const Pos& a, const Pos& b) {
	return fmax(abs(a.x - b.x), abs(a.y - b.y));
}

int toIndex(const Pos& pt, int width) {
	return pt.x + pt.y * width;
}

Pos fromIndex(int idx, int width) {
	return Pos{ idx % width, idx / width };
}

bool operator==(const Pos& a, const Pos& b) {
	return a.x == b.x && a.y == b.y;
}