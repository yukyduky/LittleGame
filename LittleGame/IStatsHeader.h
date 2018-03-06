#pragma once
#ifndef ISTATSHEADER_H
#define ISTATSHEADER_H

#include <array>

// Level, kills, damage taken to player, 2 arrays that are set to 0 in constructor
struct Statistics
{
	int level;
	float difficulty;
	int kills;
	float damageTaken;
	std::array<int, (size_t)5/*Need enum for types of enemy upgrades*/> enemyUpg;
	std::array<int /*GLYPHTYPE*/, 5 /*NAME*/> glyphs;

	Statistics() :
		level(0),
		difficulty(0),
		kills(0),
		damageTaken(0.0f)
	{};
};

// Statics can be accessed by calling the struct with the stats in the getStats() function
class IStatsHeader
{
public:
	// Adds 1 to the level
	virtual void addLevel() = 0;
	// Increases the difficulty by the input value
	virtual void increaseDifficulty(float additiveValue) = 0;
	// Adds 1 to the killcount
	virtual void addKill() = 0;
	// Input is damage that will be added to the damage taken
	virtual void addDamageTaken(float dmg) = 0;
	// Input is (int)ENEMYUPGRADE
	virtual void addUpgrade(int type) = 0;
	// Input is (int)NAME and (int)GLYPHTYPE
	virtual void addGlyph(int spellName, int glyph) = 0;

	// Returns struct
	virtual Statistics getStats() = 0;
	// Sets all stats to 0, used in reset game
	virtual void resetStats() = 0;
private:

};

#endif //!ISTATSHEADER_H