#pragma once
#ifndef ISTATSHEADER_H
#define ISTATSHEADER_H

#include <array>

struct Statistics
{
	int level;
	int kills;
	float damageTaken;
	std::array<int, (size_t)5/*Need enum for types of enemy upgrades*/> enemyUpg;
	std::array<int /*GLYPHTYPE*/, 5 /*NAME*/> glyphs;

	Statistics() :
		level(-1),
		kills(0),
		damageTaken(0.0f)
	{};
};

class IStatsHeader
{
public:
	virtual void addLevel() = 0;
	virtual void addKill() = 0;
	virtual void addDamageTaken(float dmg) = 0;
	virtual void addUpgrade(int type) = 0;
	virtual void addGlyph(int spellName, int glyph) = 0;

	virtual Statistics getStats() = 0;
	virtual void resetStats() = 0;
private:

};

#endif //!ISTATSHEADER_H