#include "Cell.h"
#include <iostream>
#include "Input.h"
using namespace std;

Cell::Cell()
{
	// Initializing variables
	_Alive = true;
	_DeathRow = false;
	_R = 0.0f;
	_G = 0.0f;
	_B = 0.0f;
	_CellX = 0.0f;
	_CellY = 0.0f;
	_Survive = true;
	_Type = 1;
	_Timer = 0;
	_Wall = false;
}

void Cell::Draw(aie::Renderer2D* renderer)
{
}

void Cell::Update(float DeltaTime, aie::Input* input)
{
	_Timer += DeltaTime * 10;

	MouseOver(input);

	if (_Survive)
		_Alive = true;
	else
		_Alive = false;

	// Set colour for each type of cell
	if (_Wall)
	{
		_R = 1.0f;
		_G = 1.0f;
		_B = 1.0f;
	}
	else if (_Alive && _Type == 1)
	{
		_R = 0.2f;
		_G = 0.85f;
		_B = 0.2f;
	}
	else if (_Alive && _Type == 2)
	{
		_R = 0.85f;
		_G = 0.2f;
		_B = 0.2f;
	}
	else if (_Alive && _Type == 3)
	{
		_R = 0.2f;
		_G = 0.2f;
		_B = 0.85f;
	}
	
	// If the cell is dead make it black
	if (!_Alive && !_Wall)
	{
		_R = 0.0f;
		_G = 0.0f;
		_B = 0.0f;
	}
}

void Cell::MouseOver(aie::Input* input)
{
	// Save Cell
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		if (_Timer > 2)
		{
			if (input->getMouseX() >= _CellX - (_SizeX / 2) && input->getMouseX() <= _CellX + (_SizeX / 2) &&
				input->getMouseY() >= _CellY - (_SizeY / 2) && input->getMouseY() <= _CellY + (_SizeY / 2))
			{
				if (_Survive)
				{
					_Type += 1;
					if (_Type == 4)
						_Type = 1;
				}
				_Survive = true;
			}

			_Timer = 0;
		}
	}

	// Kill Cell
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		if (_Timer > 2)
		{
			if (input->getMouseX() >= _CellX - (_SizeX / 2) && input->getMouseX() <= _CellX + (_SizeX / 2) &&
				input->getMouseY() >= _CellY - (_SizeY / 2) && input->getMouseY() <= _CellY + (_SizeY / 2))
			{
				_Survive = false;
			}

			_Timer = 0;
		}
	}
}