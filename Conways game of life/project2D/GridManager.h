#pragma once
#include <Renderer2D.h>
#include "Cell.h"
#include "Input.h"


class GridManager
{
public:
	GridManager(int cellAmount, float windowSizeX, float windowSizeY);
	~GridManager();

	void Update(aie::Input* input, float deltaTime , float windowWidth, float windowHeight);
	void Draw(aie::Renderer2D* renderer);

	void CheckNeighbours();

private:
	float _WindowSizeX;
	float _WindowSizeY;
	float _Timer;
	int _CellTotal;
	int _CellSize;

	Cell** _Cells;

};

