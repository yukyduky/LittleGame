#include "StatsHeader.h"

#include "Spell.h"

StatsHeader::StatsHeader()
{
	for (auto i : this->stats.glyphs)
	{
		i = (int)GLYPHTYPE::NONE;
	}

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
