#include "StatsHeader.h"

#include "Spell.h"

StatsHeader::StatsHeader()
{
	//Sets every glyph to 0 aka NONE
	this->stats.glyphs[0] = 0.0f;
	this->stats.glyphs[1] = 0.0f;
	this->stats.glyphs[2] = 0.0f;
	this->stats.glyphs[3] = 0.0f;
	this->stats.glyphs[4] = 0.0f;

	for (auto i : this->stats.enemyUpg)
	{
		i = 0;
	}
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
