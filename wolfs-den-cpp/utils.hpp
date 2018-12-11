#pragma once

template <typename T>
inline T clamp(T val, T low, T high) {
	if (val < low)
		return low;
	else if (val > high)
		return high;
	else
		return val;
}

template <typename T>
inline bool between(T val, T low, T high) {
	return clamp(val, low, high) == val;
}
