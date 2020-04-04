#pragma once
#include "gameNode.h"

struct tagTile
{	
	RECT rc;
	int keyNum;
	bool imgOn;
};

struct tagButton
{
	RECT rc;
	char text[10];
};

class mapTool :	public gameNode
{
	tagTile _vTile[10][10];
	RECT select[12];
	tagButton _button[3];
	bool selectOn[12];
	char test[100];
	tagTile selectTile;


public:

	HRESULT init();
	void release();
	void update();
	void render();

	void Save();
	void Load();
	
	mapTool() {}
	~mapTool() {}
};

