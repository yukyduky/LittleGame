#pragma once
#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include <vector>
#include <list>
#include <d3d11.h>
#include <DirectXMath.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <Dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")

//SafeRealse function from the D2D tutorial that might be usefull in other parts of the program
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = nullptr;
	}
}

class Component;

using namespace DirectX;


class MenuObject
{
public:
	MenuObject(ID2D1HwndRenderTarget* RT);
	MenuObject(ID2D1HwndRenderTarget* RT ,size_t ID, XMFLOAT4 pos, D2D1::ColorF color);
	~MenuObject();

	// Needs to be filled
	void cleanUp();
	void addComponent(Component* component);
	const size_t getID() const { return this->ID; }

	virtual void render();
	

private:
	ID2D1SolidColorBrush * pColorBrush;

protected:
	D2D1_RECT_F rectangle;
	ID2D1HwndRenderTarget * pRT;
	XMFLOAT2 menuSize = {150.0f, 350.0f};

	std::list<Component*> components;

	const size_t ID;
	XMFLOAT3 pos;
};



#endif // !MENUOBJECT_H
