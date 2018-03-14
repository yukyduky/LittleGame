#include "StatsHeader.h"

StatsHeader::StatsHeader()
{
	//Sets every glyph to 0 aka NONE
	this->stats.glyphs[0] = 0;
	this->stats.glyphs[1] = 0;
	this->stats.glyphs[2] = 0;
	this->stats.glyphs[3] = 0;
	this->stats.glyphs[4] = 0;

	//Sets every enemyUpg to 0 aka NONE
	this->stats.enemyUpg[0] = 0;
	this->stats.enemyUpg[1] = 0;
	this->stats.enemyUpg[2] = 0;
	this->stats.enemyUpg[3] = 0;

	this->playerCompletedGame = false;
}

void StatsHeader::addLevel()
{
	this->stats.level++;
}

void StatsHeader::addKill()
{
	this->stats.kills++;
}

void StatsHeader::addDamageTaken(float dmg)
{
	this->stats.damageTaken += dmg;
}

void StatsHeader::addUpgrade(int type)
{
	this->stats.enemyUpg.at(type)++;
}

void StatsHeader::addGlyph(int spellName, int glyph)
{
	this->stats.glyphs.at(spellName) = glyph;
}

Statistics StatsHeader::getStats()
{
	return stats;
}

void StatsHeader::resetStats()
{
	this->stats.damageTaken = 0.0f;
	this->stats.kills = 0;
	this->stats.level = 0;
	this->stats.difficulty = 1.0f;

	//Sets every glyph to 0 aka NONE
	this->stats.glyphs[0] = 0;
	this->stats.glyphs[1] = 0;
	this->stats.glyphs[2] = 0;
	this->stats.glyphs[3] = 0;
	this->stats.glyphs[4] = 0;

	//Sets every enemyUpg to 0 aka NONE
	this->stats.enemyUpg[0] = 0;
	this->stats.enemyUpg[1] = 0;
	this->stats.enemyUpg[2] = 0;
	this->stats.enemyUpg[3] = 0;

	this->playerCompletedGame = false;
}
