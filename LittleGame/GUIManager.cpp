#include "GUIManager.h"
#include "RectangleComponent.h"
#include "ArenaObject.h"

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

	//Prepare the color
	color = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };

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

//----------------------------\
//     HEALTH GUI ELEMENT     /
//___________________________/

	// FOREGROUND \\
//  ----------------
	this->createGUIElement(
		255.0f, 0.0f, 0.0f, 255.0f,
		-0.6f, 0.0f, -0.55f,
		0.06, 0.0f, 0.06f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->hpRect = this->rect;

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
		244.0f, 226.0f, 67.0f, 255.0f,
		0.6f, 0.0f, -0.55f,
		0.06, 0.0f, 0.06f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->energyRect = this->rect;

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
		255.0f, 25.5f, 127.5f, 255.0f,
		-0.3f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->ability1Rect = this->rect;

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
		80.0f, 80.0f, 80.0f, 255.0f,
		-0.1f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->ability2Rect = this->rect;

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
		255.0f, 255.0f, 0.0f, 51.0f,
		0.1f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	this->ability3Rect = this->rect;

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
		0.0f, 102.0f, 255.0f, 255.0f,
		0.3f, 0.0f, -0.55f,
		0.03f, 0.0f, 0.03f
	);

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

	// BACKGROUND \\
//  ----------------
	this->createGUIElement(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.3f, -0.001f, -0.55f,
		0.04, 0.0f, 0.04f
	);

	this->ability4Rect = this->rect;

	GUIObjects.push_back(this->object);
	graphics.push_back(this->rect);

///-------------------------------------------





	return this->tempID;
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