#include "Cell.h"
#include <iostream>
using namespace std;

Cell::Cell()
{
	_Alive = true;
	_R = 0.0f;
	_G = 0.0f;
	_B = 0.0f;
	_CellX = 0.0f;
	_CellY = 0.0f;
}

Cell::~Cell()
{
}

void Cell::Draw(aie::Renderer2D* renderer)
{
}

void Cell::Update(float deltaTime)
{
	//  3.5% red, 50.6% green and 29% blue
	if (_Alive)
	{
		_R = 0.035f;
		_G = 0.506f;
		_B = 0.29f;
	}
	else
	{
		_R = 0.40f;
		_G = 0.251f;
		_B = 0.192f;
	}
}
