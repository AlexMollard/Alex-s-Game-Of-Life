#include "GridManager.h"
#include <iostream>
using namespace std;

GridManager::GridManager(int cellAmount, float windowSizeX, float windowSizeY)
{
	_CellTotal = cellAmount;
	_WindowSizeX = windowSizeX;
	_WindowSizeY = windowSizeY;
	_CellSize = 1000 / _CellTotal;
	_Timer = 0;
	_Cells = new Cell*[_CellTotal];

	for (int i = 0; i < cellAmount; i++)
		_Cells[i] = new Cell[_CellTotal];

	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			_Cells[x][y].SetPos(x * _CellSize * 1.5, y * _CellSize * 1.5);

			int _RandomAlive = rand() % 10;
			if (_RandomAlive == 1)
				_Cells[x][y].SetAlive(true);
			else
				_Cells[x][y].SetAlive(false);
		}
	}

	// Glider
	//_Cells[1][40].SetAlive(true);
	//_Cells[2][39].SetAlive(true);
	//_Cells[3][39].SetAlive(true);
	//_Cells[3][40].SetAlive(true);
	//_Cells[3][41].SetAlive(true);
}

GridManager::~GridManager()
{
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


	if (_WindowSizeX != windowWidth || _WindowSizeY != windowHeight)
	{
		_WindowSizeX = windowWidth;
		_WindowSizeY = windowHeight;

		for (int x = 0; x < _CellTotal; x++)
		{
			for (int y = 0; y < _CellTotal; y++)
			{
				_Cells[x][y].SetPos(x * _CellSize * 1.5, y * _CellSize * 1.5);
			}
		}
	}

	if (_Timer > 1)
	{
		CheckNeighbours();
		_Timer = 0;
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

			// RULES		//NEEDS FIXING
			if ((_Cells[x][y].GetAlive() == true && _AliveNeighbours <= 1) || 
				(_Cells[x][y].GetAlive() == true && _AliveNeighbours >= 4))
			{
				_Cells[x][y].SetAlive(false);	// Kill Cell
			}
			else if (
				(_Cells[x][y].GetAlive() == false && _AliveNeighbours == 3) || 
				(_Cells[x][y].GetAlive() == true && _AliveNeighbours == 2) || 
				(_Cells[x][y].GetAlive() == true && _AliveNeighbours == 3))
			{
				_Cells[x][y].SetAlive(true);	// Save Cell
			}
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
			renderer->drawBox(_Cells[x][y].GetX() + _WindowSizeX / _CellTotal, _Cells[x][y].GetY() + _WindowSizeY / _CellTotal, _CellSize, _CellSize);
		}
	}
}