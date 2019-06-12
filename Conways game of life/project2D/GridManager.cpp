#include "GridManager.h"
#include <iostream>
using namespace std;

GridManager::GridManager(int cellAmount, float windowSizeX, float windowSizeY)
{
	// Set how many cells there are
	_CellTotal = cellAmount;

	// Set window size varibles
	_WindowSizeX = windowSizeX;
	_WindowSizeY = windowSizeY;

	// Set Cell Size
	_CellSizeX = 10;
	_CellSizeY = 10;

	// Set Timer for each generation
	_Timer = 0;

	// Create Cells
	_Cells = new Cell*[_CellTotal];
	for (int i = 0; i < cellAmount; i++)
		_Cells[i] = new Cell[_CellTotal];

	Resize(windowSizeX, windowSizeY);

	// Randomize cells
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			int _RandomAlive = rand() % 50;
			if (_RandomAlive < 30)
				_Cells[x][y].SetAlive(true);
			else
				_Cells[x][y].SetAlive(false);
		}
	}

	// Glider example
	//_Cells[1][_CellTotal-2].SetAlive(true);
	//_Cells[2][_CellTotal-3].SetAlive(true);
	//_Cells[3][_CellTotal-3].SetAlive(true);
	//_Cells[3][_CellTotal-2].SetAlive(true);
	//_Cells[3][_CellTotal-1].SetAlive(true);
}

void GridManager::Update(aie::Input* input, float deltaTime, float windowWidth, float windowHeight)
{
	_Timer += deltaTime * 10;

	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			_Cells[x][y].Update(deltaTime);
		}
	}

	// Resize Cells
	if (_WindowSizeX != windowWidth || _WindowSizeY != windowHeight)
		Resize(windowWidth, windowHeight);

	if (_Timer > 0.5)
	{
		CheckNeighbours();
		_Timer = 0;
	}
}

void GridManager::Resize(float windowWidth, float windowHeight)
{
		_WindowSizeX = windowWidth;
		_WindowSizeY = windowHeight;

		// Cell size
		_CellSizeX = _WindowSizeX / _CellTotal / 2;
		_CellSizeY = _WindowSizeY / _CellTotal / 2;

		for (int x = 0; x < _CellTotal; x++)
		{
			for (int y = 0; y < _CellTotal; y++)
			{
				// Cell Postition
				_Cells[x][y].SetPos(x * _CellSizeX * 2, y * _CellSizeY * 2);
			}
		}
}

void GridManager::CheckNeighbours()
{
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			int _AliveNeighbours = 0;


			if (x + 1 < _CellTotal && y + 1 < _CellTotal)
			{														 // - | - | X
				if (_Cells[x + 1][y + 1].GetAlive())				 // - | - | -
					_AliveNeighbours += 1;							 // - | - | -
			}

			if (y + 1 < _CellTotal)
			{													   // - | X | -
				if (_Cells[x][y + 1].GetAlive())				   // - | - | -
					_AliveNeighbours += 1;						   // - | - | -
			}

			if (x - 1 >= 0 && y + 1 < _CellTotal)
			{														// X | - | -
				if (_Cells[x - 1][y + 1].GetAlive())				// - | - | -
					_AliveNeighbours += 1;							// - | - | -
			}

			if (x - 1 >= 0)
			{													   // - | - | -
				if (_Cells[x - 1][y].GetAlive())				   // X | - | -
					_AliveNeighbours += 1;						   // - | - | -
			}

			if (x + 1 < _CellTotal)
			{													   // - | - | -
				if (_Cells[x + 1][y].GetAlive())				   // - | - | X
					_AliveNeighbours += 1;						   // - | - | - 
			}

			if (x - 1 >= 0 && y - 1 >= 0)
			{													   // - | - | -
				if (_Cells[x - 1][y - 1].GetAlive())			   // - | - | -
					_AliveNeighbours += 1;						   // X | - | -
			}

			if (y - 1 >= 0)
			{													   // - | - | -
				if (_Cells[x][y - 1].GetAlive())				   // - | - | -
					_AliveNeighbours += 1;						   // - | X | -
			}


			if (x + 1 < _CellTotal && y - 1 >= 0)
			{													  // - | - | -
				if (_Cells[x + 1][y - 1].GetAlive())			  // - | - | -
					_AliveNeighbours += 1;						  // - | - | X
			}

			// RULES
			if ((_Cells[x][y].GetAlive() == true && _AliveNeighbours <= 1) || 
				(_Cells[x][y].GetAlive() == true && _AliveNeighbours >= 4))
			{
				_Cells[x][y].SetDeath(true);	// Kill Cell
			}
			else if (
				(_Cells[x][y].GetAlive() == false && _AliveNeighbours == 3) || 
				(_Cells[x][y].GetAlive() == true && _AliveNeighbours == 2) || 
				(_Cells[x][y].GetAlive() == true && _AliveNeighbours == 3))
			{
				_Cells[x][y].SetDeath(false);	// Save Cell
			}
		}
	}

	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			if (_Cells[x][y].GetDeath())
				_Cells[x][y].SetAlive(false);
			else if(!_Cells[x][y].GetDeath())
				_Cells[x][y].SetAlive(true);
		}
	}

}


void GridManager::Draw(aie::Renderer2D* renderer)
{
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			renderer->setRenderColour(_Cells[x][y].GetR(), _Cells[x][y].GetG(), _Cells[x][y].GetB());
			renderer->drawBox(_Cells[x][y].GetX() + _WindowSizeX / _CellTotal, _Cells[x][y].GetY() + _WindowSizeY / _CellTotal, _CellSizeX, _CellSizeY);
		}
	}
}