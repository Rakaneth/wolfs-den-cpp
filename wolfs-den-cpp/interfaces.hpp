#pragma once

class ILocatable {
public:
	virtual Pos pos() = 0;
};

class IUpkeep {
public:
	virtual void tick() = 0;
};
