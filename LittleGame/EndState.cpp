#include "EndState.h"
#include "GameManager.h"

EndState EndState::sEndState;

EndState * EndState::getInstance()
{
	return &sEndState;
}

void EndState::init()
{

}
void EndState::cleanUp()
{

}
void EndState::pause()
{

}
void EndState::resume()
{

}
void EndState::handleEvents(GameManager* gm)
{
	gm->quit();
}
void EndState::update(GameManager* gm)
{
	gm->quit();
}
void EndState::render(GameManager* gm)
{
	gm->quit();
}