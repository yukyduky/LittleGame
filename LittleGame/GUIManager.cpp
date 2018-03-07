#include "GUIManager.h"
#include "RectangleComponent.h"
#include "ArenaObject.h"
#include "Spell.h"
#include "ArenaGlobals.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                   GUI MANAGER           /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

void GUIManager::createGUIElement(
	float r, float g, float b, float a,
	float xAdjust, float yAdjust, float zAdjust,
	float xScaling, float yScaling, float zScaling)
{
	vColor color;
	XMVECTOR vec;
	XMFLOAT3 pos;

	XMMATRIX worldM;
	XMMATRIX rotationM;
	XMMATRIX scaleM;
	XMMATRIX translationM;

	// NOTE: NO preparation needed; numbers already divided by '255.0f'
	color = { r, g, b, a };

	// Place the object in front of the camera
	pos = (this->cameraPos + this->cameraFacingDir);
	// Specific Adjustments
	pos = { pos.x + xAdjust, pos.y + yAdjust, pos.z + zAdjust };

	//Create the 'GameObject' and calculate the world matrix
	this->object = new ArenaObject(this->tempID, pos);
	vec = XMLoadFloat3(&pos);

	rotationM = XMMatrixIdentity();
	scaleM = XMMatrixScaling(xScaling, yScaling, zScaling);
	translationM = XMMatrixTranslationFromVector(vec);
	worldM = scaleM * rotationM * translationM;

	//Create the RectangleComponent
	rect = new RectangleComponent(*this->object, color.r, color.g, color.b, color.a);
	//Give the RectangleComponent to the ArenaObject and set it's world matrix
	this->object->addComponent(rect);
	this->object->SETworldMatrix(worldM);
	this->object->SETrotationMatrix(rotationM);
	this->object->SETscaleMatrix(scaleM);

	// Incrementing the ID number for next object
	this->tempID++;
}

void GUIManager::updateGUIElement(RectangleComponent* element, float remainingCooldownFloat)
{
	element->updateVertexZ(0, remainingCooldownFloat);
	element->updateVertexZ(1, remainingCooldownFloat);
}

int GUIManager::getID() {
	return this->tempID++;
}

//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

GUIManager::GUIManager() {

}

GUIManager::~GUIManager() {

}

int GUIManager::initGUI(
	int ID,
	DirectX::XMFLOAT3 cameraPos,
	DirectX::XMFLOAT3 cameraFacingDir,
	std::list<GameObject*>& GUIObjects,
	std::list<GraphicsComponent*>& graphics)
{
	this->tempID = ID;
	this->cameraPos = cameraPos;
	this->cameraFacingDir = cameraFacingDir;

	for (int i = 0; i < 4; i++) {
		this->rectBack[i] = nullptr;
	}

	float temptester123 = this->cameraPos.y / 630.0f;

	// Setting 'EnemyCount' GUI elements pos depending on arena size
	// NOTE: This is due to varying camera positions.

	if (ARENADATA::GETarenaHeight() == 1600 && ARENADATA::GETarenaWidth() == 1600)
	{
		this->enemyElementPosX = -1.05f;
		this->enemyElementPosY = 0.0f;
		this->enemyElementPosZ = 1.1f;
	}

//----------------------------\
//     HEALTH GUI ELEMENT     /
//___________________________/

	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorHP.r, this->colorHP.g, this->colorHP.b, this->colorHP.a,
		-0.58f, 0.0f, -0.55f,
		0.06f, 0.0f, 0.06f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectHP = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorBack.r, this->colorBack.g, this->colorBack.b, this->colorBack.a,
		-0.58f, -0.001f, -0.55f,
		0.075f, 0.0f, 0.075f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

///-------------------------------------------


	


//----------------------------\
//     ENERGY GUI ELEMENT     /
//___________________________/
	
	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorEnergy.r, this->colorEnergy.g, this->colorEnergy.b, this->colorEnergy.a,
		0.58f, 0.0f, -0.55f,
		0.06f, 0.0f, 0.06f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectEnergy = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorBack.r, this->colorBack.g, this->colorBack.b, this->colorBack.a,
		0.58f, -0.001f, -0.55f,
		0.075f, 0.0f, 0.075f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

///-------------------------------------------





//----------------------------\
//     ABILITY BUTTON #1      /
//___________________________/
	
	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorAbility1.r, this->colorAbility1.g, this->colorAbility1.b, this->colorAbility1.a,
		-0.3f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectAbility1 = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorBackSelected.r, this->colorBackSelected.g, this->colorBackSelected.b, this->colorBackSelected.a,
		-0.3f, -0.001f, -0.55f,
		0.04f, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectBack[0] = this->rect;

///-------------------------------------------





//----------------------------\
//     ABILITY BUTTON #2      /
//___________________________/
	
	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorAbility2.r, this->colorAbility2.g, this->colorAbility2.b, this->colorAbility2.a,
		-0.1f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectAbility2 = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorBack.r, this->colorBack.g, this->colorBack.b, this->colorBack.a,
		-0.1f, -0.001f, -0.55f,
		0.04f, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectBack[1] = this->rect;

///-------------------------------------------





//----------------------------\
//     ABILITY BUTTON #3      /
//___________________________/
	
	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorAbility3.r, this->colorAbility3.g, this->colorAbility3.b, this->colorAbility3.a,
		0.1f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectAbility3 = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorBack.r, this->colorBack.g, this->colorBack.b, this->colorBack.a,
		0.1f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectBack[2] = this->rect;

///-------------------------------------------





//----------------------------\
//     ABILITY BUTTON #4      /
//___________________________/

	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorAbility4.r, this->colorAbility4.g, this->colorAbility4.b, this->colorAbility4.a,
		0.3f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectAbility4 = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorBack.r, this->colorBack.g, this->colorBack.b, this->colorBack.a,
		0.3f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectBack[3] = this->rect;

///-------------------------------------------






	return this->tempID;
}

void GUIManager::updateGUI(ActorObject* player)
{
	vColor colorHolder;

	// Update size of UI elements to represent remaining 'HP', 'ENERGY', or 'COOLDOWN'
	this->updateGUIElement(this->rectHP, player->GEThpRemainingFloat());
	this->updateGUIElement(this->rectEnergy, player->GETenergyRemainingFloat());
	this->updateGUIElement(this->rectAbility1, player->GETspellsVector().at(1)->GETremainingCoolDownFloat());
	this->updateGUIElement(this->rectAbility2, player->GETspellsVector().at(2)->GETremainingCoolDownFloat());
	this->updateGUIElement(this->rectAbility3, player->GETspellsVector().at(3)->GETremainingCoolDownFloat());
	this->updateGUIElement(this->rectAbility4, player->GETspellsVector().at(4)->GETremainingCoolDownFloat());

	// Update the color of ability cooldown based on whether they are ON or OFF cooldown
	if (player->GETspellsVector().at(1)->getTSC() == 0)
		this->rectAbility1->updateColor(this->colorAbility1);
		
	else {
		colorHolder = this->colorAbility1;
		this->rectAbility1->updateColor(vColor(colorHolder.r, colorHolder.g, colorHolder.b, 0.0f));
	}

	if (player->GETspellsVector().at(2)->getTSC() == 0)
		this->rectAbility2->updateColor(this->colorAbility2);
	else {
		colorHolder = this->colorAbility2;
		this->rectAbility2->updateColor(vColor(colorHolder.r, colorHolder.g, colorHolder.b, 0.0f));
	}

	if (player->GETspellsVector().at(3)->getTSC() == 0)
		this->rectAbility3->updateColor(this->colorAbility3);
	else {
		colorHolder = this->colorAbility3;
		this->rectAbility3->updateColor(vColor(colorHolder.r, colorHolder.g, colorHolder.b, 0.0f));
	}

	if (player->GETspellsVector().at(4)->getTSC() == 0)
		this->rectAbility4->updateColor(this->colorAbility4);
	else {
		colorHolder = this->colorAbility4;
		this->rectAbility4->updateColor(vColor(colorHolder.r, colorHolder.g, colorHolder.b, 0.0f));
	}

	if (player->GETcurrentSpellInt() != this->lastSpell)
	{
		this->rectBack[(lastSpell - 1)]->updateColor(this->colorBack);
		this->rectBack[(player->GETcurrentSpellInt() - 1)]->updateColor(this->colorBackSelected);

		this->lastSpell = player->GETcurrentSpellInt();
	}
}

void GUIManager::pushEnemyElement(std::list<GameObject*>& GUIObjects, std::list<GraphicsComponent*>& graphics, int ID)
{
	this->tempID = ID;

	this->createGUIElement(
		0.0f, 1.0f, 0.0f, 1.0f,
		this->enemyElementPosX, this->enemyElementPosY, this->enemyElementPosZ,
		0.002f, 0.0f, 0.04f
	);

	this->enemyElementPosX += this->separationDistance;

	if (this->enemyElementPosX > 1.05f)
		this->enemyElementPosX = -1.05f;

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	// Pushing to specific 'enemy-only' lists
	this->enemyElementObjects.push_back(this->object);
	this->enemyElementRects.push_back(this->rect);
}

void GUIManager::popEnemyElement(std::list<GameObject*>& GUIObjects, std::list<GraphicsComponent*>& graphics)
{
	GameObject* tempObjectHolder = this->enemyElementObjects.front();
	GraphicsComponent* tempGraphicsHolder = this->enemyElementRects.front();

	this->enemyElementObjects.pop_front();
	this->enemyElementRects.pop_front();

	GUIObjects.remove(tempObjectHolder);
	graphics.remove(tempGraphicsHolder);

	tempObjectHolder->cleanUp();
	delete tempObjectHolder;
}

void GUIManager::cleanUp()
{
	this->enemyElementObjects.clear();
	this->enemyElementRects.clear();

	this->enemyElementPosX = 0.0f;
	this->enemyElementPosY = 0.0f;
	this->enemyElementPosZ = 0.0f;
}
//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                   GUI MANAGER           \
////////////////////////////////////////////////////////////