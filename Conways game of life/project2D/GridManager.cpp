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

	// Set Cell Neighbour Variables
	_AliveNeighbours = 0;

	// Set Timer for each generation
	_Timer = 0;

	// Create Cells
	_Cells = new Cell*[_CellTotal];
	for (int i = 0; i < cellAmount; i++)
		_Cells[i] = new Cell[_CellTotal];

	// Resize Cells for window size
	Resize(windowSizeX, windowSizeY);

	// Set cells
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			// Set the walls
			if (x == 0 || x == _CellTotal - 1 || y == 0 || y == _CellTotal - 1)
			{
				_Cells[x][y].SetWall(true);
				_Cells[x][y].SetAlive(false);
				_Cells[x][y].SetSurvive(false);
			}
			else
			{
				// Set alive and dead cells
				int testing = rand() % 30;
				// Set Cells
				if (testing < 10)
				{
					_Cells[x][y].SetSurvive(true);
					_Cells[x][y].SetType(1);
				}
				else if (testing < 20)
				{
					_Cells[x][y].SetSurvive(false);
					_Cells[x][y].SetType(2);
				}
				else
				{
					_Cells[x][y].SetSurvive(true);
					_Cells[x][y].SetType(3);
				}
			}
		}
	}

	// Create wall cell
	_Wall = _Cells[0][0];
}

void GridManager::Update(aie::Input* input, float deltaTime, float windowWidth, float windowHeight)
{
	// Timer tracker
	_Timer += deltaTime * 10;

	// Resize Cells if window size has changed
	if (_WindowSizeX != windowWidth || _WindowSizeY != windowHeight)
		Resize(windowWidth, windowHeight);

	// Check all cells neighbours
	if (input->isKeyDown(aie::INPUT_KEY_SPACE) && _Timer > 2)
	{
		CheckNeighbours();
		_Timer = 0;	
	}

	// Update all the cells
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			_Cells[x][y].Update(deltaTime, input);
		}
	}

}

void GridManager::Resize(float windowWidth, float windowHeight)
{
		// Window Size
		_WindowSizeX = windowWidth;
		_WindowSizeY = windowHeight;

		// Cell size
		_CellSizeX = _WindowSizeX / _CellTotal / 2;
		_CellSizeY = _WindowSizeY / _CellTotal / 2;

		// Set all cells positions
		for (int x = 0; x < _CellTotal; x++)
		{
			for (int y = 0; y < _CellTotal; y++)
			{
				// Set Cell Position
				_Cells[x][y].SetPos(x * _CellSizeX * 2 + _CellSizeX, y * _CellSizeY * 2 + _CellSizeY);
				_Cells[x][y].SetSize(_CellSizeX, _CellSizeY);
			}
		}
}

void GridManager::CheckNeighbours()
{
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			if (!_Cells[x][y].GetWall())
			{
				// How many neighbours does the cell have
				_AliveNeighbours = 0;
				_Type1Neighbours = 0;
				_Type2Neighbours = 0;
				_Type3Neighbours = 0;

				// Reset neighbours
				TR	= _Wall;
				TM	= _Wall;
				TL	= _Wall;
				MR	= _Wall;
				ML	= _Wall;
				BR	= _Wall;
				BM	= _Wall;
				BL	= _Wall;

				// Neighbour Cells
				if (!_Cells[x + 1][y + 1].GetWall())
					TR = _Cells[x + 1][y + 1];

				if (!_Cells[x][y + 1].GetWall())
					TM = _Cells[x][y + 1];

				if (!_Cells[x - 1][y + 1].GetWall())
					TL = _Cells[x - 1][y + 1];

				if (!_Cells[x + 1][y].GetWall())
					MR = _Cells[x + 1][y];

				if (!_Cells[x - 1][y].GetWall())
					ML = _Cells[x - 1][y];

				if (!_Cells[x + 1][y - 1].GetWall())
					BR = _Cells[x + 1][y - 1];

				if (!_Cells[x][y - 1].GetWall())
					BM = _Cells[x][y - 1];

				if (!_Cells[x - 1][y - 1].GetWall())
					BL = _Cells[x - 1][y - 1];

				// Get how many neighbours alive and type
				if (TR.GetAlive())
					GetCellType(TR);			
										
				if (TM.GetAlive())						
					GetCellType(TM);
										
				if (TL.GetAlive())						
					GetCellType(TL);
										
				if (MR.GetAlive())						
					GetCellType(MR);
										
				if (ML.GetAlive())						
					GetCellType(ML);
										
				if (BL.GetAlive())						
					GetCellType(BL);
										
				if (BM.GetAlive())						
					GetCellType(BM);
									
				if (BR.GetAlive())						
					GetCellType(BR);

				// Set Cells new status
				NextGeneration(x,y);
			}
		}
	}
}

void GridManager::NextGeneration(int x, int y)	// Rules Would be put in here
{
	//Set Cell Rules
	if (_AliveNeighbours == 3 && !_Cells[x][y].GetAlive())
		_Cells[x][y].SetSurvive(true);
	else if (_AliveNeighbours <= 1 && _Cells[x][y].GetAlive())
		_Cells[x][y].SetSurvive(false);
	else if (_AliveNeighbours >= 4 && _Cells[x][y].GetAlive())
		_Cells[x][y].SetSurvive(false);
	else if (_AliveNeighbours == 2 && _Cells[x][y].GetAlive())
		_Cells[x][y].SetSurvive(true);
	else if (_AliveNeighbours == 3 && _Cells[x][y].GetAlive())
		_Cells[x][y].SetSurvive(true);
}

void GridManager::GetCellType(Cell cell)
{
	_AliveNeighbours += 1;

	// Get Neighbour types
	_NeighbourType = cell.GetType();
	if (_NeighbourType == 1)
		_Type1Neighbours += 1;
	else if (_NeighbourType == 2)
		_Type2Neighbours += 1;
	else if (_NeighbourType == 3)
		_Type3Neighbours += 1;
}

void GridManager::Draw(aie::Renderer2D* renderer)
{
	// Draw cells
	for (int x = 0; x < _CellTotal; x++)
	{
		for (int y = 0; y < _CellTotal; y++)
		{
			renderer->setRenderColour(_Cells[x][y].GetR(), _Cells[x][y].GetG(), _Cells[x][y].GetB());
			renderer->drawBox(_Cells[x][y].GetX(), _Cells[x][y].GetY(), _CellSizeX, _CellSizeY);
		}
	}
}