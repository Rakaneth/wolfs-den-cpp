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

template <typename T>
inline bool contains(std::vector<T>& list, T thing) {
  for (auto& item : list)
    if (item == thing)
      return true;

  return false;
}

template<typename T> 
inline void listRemove(std::vector<T>& list, T val) {
  auto it = std::remove(list.begin(), list.end(), val);
  if (it != list.end())
    list.erase(it);
}

template <typename T>
inline T& listRandom(std::vector<T>& list, TCODRandom& rng) {
  int roll = rng.getInt(0, list.size());
  return list[roll];
}