#include "main.hpp"

void TempStat::tick() {
	if (_duration > 0)
		_duration--;

	if (_duration == 0)
		std::cout << _name << " has worn off." << std::endl;
}

void Stat::addRawBonus(TempStat bonus) {
	_rawBonuses.push_back(bonus);
}

void Stat::addFinalBonus(TempStat bonus) {
	_finalBonuses.push_back(bonus);
}

void Stat::tick() {
	for (auto& raw : _rawBonuses)
		raw.tick();

	for (auto& fn : _finalBonuses)
		fn.tick();

	_rawBonuses.erase(std::remove_if(_rawBonuses.begin(), _rawBonuses.end(),
		[](TempStat b) { return b.hasExpired(); }), _rawBonuses.end());

	_finalBonuses.erase(std::remove_if(_finalBonuses.begin(), _finalBonuses.end(),
		[](TempStat b) { return b.hasExpired(); }), _finalBonuses.end());
}

bool Stat::hasBonus(std::string name) {
	for (auto& raw : _rawBonuses)
		if (raw.getName() == name)
			return true;

	for (auto& fin : _finalBonuses)
		if (fin.getName() == name)
			return true;

	return false;
}

int Stat::getValue() const {
	int total = _baseVal;
	int rawFlats = 0;
	double rawPcts = 0.0;
	int finalFlats = 0;
	double finalPcts = 0.0;

	for (auto& raw : _rawBonuses) {
		rawFlats += raw.getBaseVal();
		rawPcts += raw.getPct();
	}

	for (auto& fin : _finalBonuses) {
		finalFlats += fin.getBaseVal();
		finalPcts += fin.getPct();
	}

	total *= (1 + rawPcts);
	total += rawFlats;
	total *= (1 + finalPcts);
	total += finalFlats;

	return (int)total;
}

void Stat::setBaseVal(int val) { _baseVal = (int)fmin(val, 50); }