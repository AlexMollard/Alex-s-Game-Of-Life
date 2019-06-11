#pragma once
#include "GridManager.h"
#include "Application.h"
#include "Renderer2D.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	_2dRenderer;
	aie::Texture*		_Texture;
	aie::Texture*		_ShipTexture;
	aie::Font*			_Font;
	GridManager*		_GridManager;

	float _Timer;
};