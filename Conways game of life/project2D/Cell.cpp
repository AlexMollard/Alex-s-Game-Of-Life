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
	_Type = '1';
}

Cell::~Cell()
{
}

void Cell::Draw(aie::Renderer2D* renderer)
{
}

void Cell::Update(float deltaTime)
{
	if (_Alive && _Type == '1')			// Rock
	{
		_R = 0.2f;
		_G = 0.85f;
		_B = 0.2f;
	}
	else if (_Alive && _Type == '2')	// Paper
	{
		_R = 0.85f;
		_G = 0.2f;
		_B = 0.2f;
	}
	else if (_Alive && _Type == '3')	// Paper
	{
		_R = 0.2f;
		_G = 0.2f;
		_B = 0.85f;
	}

	else if (!_Alive)
	{
		_R = 0.0f;
		_G = 0.0f;
		_B = 0.0f;
	}
}
