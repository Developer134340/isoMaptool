#pragma once
#include "gameNode.h"

#define MAXTILE 10

struct TILE
{
	int keyNum;
	bool imgOn;
	POINT position;
};

class mapToolIso :
	public gameNode
{
	POINT _point1[MAXTILE];
	POINT _point2[MAXTILE];
	POINT _point3[MAXTILE];
	POINT _point4[MAXTILE];

	RECT select[8];
	
	TILE arrayTile[MAXTILE][MAXTILE];
	TILE selectTile;

	char test[100];

public:
	HRESULT init();
	void release();
	void update();
	void render();


	mapToolIso() {}
	~mapToolIso() {}
};

