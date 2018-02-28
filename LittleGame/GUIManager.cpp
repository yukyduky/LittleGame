#include "GUIManager.h"
#include "RectangleComponent.h"
#include "ArenaObject.h"
#include "Spell.h"

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

	float temptester123 = this->cameraPos.y / 630.0f;

//----------------------------\
//     HEALTH GUI ELEMENT     /
//___________________________/

	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		this->colorHP.r, this->colorHP.g, this->colorHP.b, this->colorHP.a,
		-0.6f, 0.0f, -0.55f,
		0.06, 0.0f, 0.06f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectHP = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		0.0f, 0.0f, 0.0f, 0.0f,
		-0.6f, -0.001f, -0.55f,
		0.075, 0.0f, 0.075f
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
		0.6f, 0.0f, -0.55f,
		0.06, 0.0f, 0.06f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->rectEnergy = this->rect;

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.6f, -0.001f, -0.55f,
		0.075, 0.0f, 0.075f
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
		0.0f, 0.0f, 0.0f, 0.0f,
		-0.3f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

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
		0.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

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
		0.0f, 0.0f, 0.0f, 0.0f,
		0.1f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

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
		0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

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