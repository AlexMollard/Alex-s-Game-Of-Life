#pragma once
#include <Renderer2D.h>
class Cell
{
public:
	Cell();
	~Cell();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	// Postition Functions
	void SetPos(float x, float y)	{ _CellX = x;  _CellY = y; };
	float GetX()					{ return _CellX; };
	float GetY()					{ return _CellY; };
	
	// Alive Functions
	bool GetAlive()					{ return _Alive; };
	void SetAlive(bool alive)		{ _Alive = alive; };

	// Death Functions
	bool GetDeath()					{ return _DeathRow; };
	void SetDeath(bool death)		{ _DeathRow = death; };

	// Type Functions
	char GetType()					{ return _Type; };
	void SetType(char type)			{ _Type = type; };

	// Colour Functions
	float GetR()					{ return _R; };
	float GetG()					{ return _G; };
	float GetB()					{ return _B; };


private:
	bool _DeathRow;
	bool _Alive;
	float _CellX;
	float _CellY;
	float _R;
	float _G;
	float _B;
	char _Type;		// '1' = Rock, '2' = Paper, '3' = Scissors
};

