#pragma once
class BaseStat {
public:
	BaseStat(std::string name, int flat = 0, double pct = 0.0)
		: _name(name), _baseVal(flat), _pct(pct) {}
	int getBaseVal() const { return _baseVal; }
	double getPct() const { return _pct; }
	std::string getName() const { return _name; }
protected:
	std::string _name;
	int _baseVal;
	double _pct;
};

class TempStat : public BaseStat, public IUpkeep {
public:
	static const int INFINITE;
	TempStat(std::string name, int flat = 0, double pct = 0.0, int duration = INFINITE)
		: BaseStat(name, flat, pct), _duration(duration) {}
	bool hasExpired() { return _duration == 0; }
	void tick();
private:
	int _duration;
};

class Stat : public BaseStat, public IUpkeep {
public:
	Stat(std::string name, int baseVal) : BaseStat(name, baseVal) {}
	void addRawBonus(TempStat bonus);
	void addFinalBonus(TempStat bonus);
	void tick();
	bool hasBonus(std::string name);
	int getValue() const;
	void setBaseVal(int val);
private:
	std::vector<TempStat> _rawBonuses;
	std::vector<TempStat> _finalBonuses;
};