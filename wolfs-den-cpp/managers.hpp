#pragma once

template <class T>
class Manager
{
public:
	void add(std::shared_ptr<T> item) { _list.push_back(item); }
	void remove(std::shared_ptr<T> item);
	void clear() { _list.clear(); }
	virtual bool process() = 0;
protected:
	std::vector<std::shared_ptr<T>> _list;
};

class UpkeepManager : public Manager<IUpkeep>
{
public:
	bool process();
};


