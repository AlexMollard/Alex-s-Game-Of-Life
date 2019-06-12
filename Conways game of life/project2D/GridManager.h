#pragma once
#include <Renderer2D.h>
#include "Cell.h"
#include "Input.h"


class GridManager
{
public:
	GridManager(int cellAmount, float windowSizeX, float windowSizeY);

	void Update(aie::Input* input, float deltaTime , float windowWidth, float windowHeight);
	void Draw(aie::Renderer2D* renderer);

	void Resize(float windowWidth, float windowHeight);
	void CheckNeighbours();

private:
	float _WindowSizeX;
	float _WindowSizeY;
	float _Timer;
	int _CellTotal;
	int _CellSizeX;
	int _CellSizeY;

	Cell** _Cells;

};

