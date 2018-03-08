#pragma once
#ifndef STATSHEADER_H
#define STATSHEADER_H

#include "IStatsHeader.h"

class StatsHeader : public IStatsHeader
{
public:
	StatsHeader();

	virtual void addLevel();
	virtual void addKill();
	virtual void addDamageTaken(float dmg);
	virtual void addUpgrade(int type);
	virtual void addGlyph(int spellName, int glyph);

	virtual Statistics getStats();
	virtual void resetStats();
private:
	Statistics stats;

};

#endif //!STATSHEADER_H