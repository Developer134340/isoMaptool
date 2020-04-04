#include "stdafx.h"
#include "mapToolIso.h"

HRESULT mapToolIso::init()
{
	for (int i = 0; i < MAXTILE; i++)
	{
		_point1[i].x = 20*(i);
		_point1[i].y =  _point1[i].x / 2 + 10*MAXTILE;

		_point2[i].x = 20 * MAXTILE + _point1[i].x;
		_point2[i].y = _point2[i].x / 2 - 10 * MAXTILE;

		_point3[i].x = _point1[i].x;
		_point3[i].y = -_point3[i].x / 2 + 10 * MAXTILE;
		
		_point4[i].x = 20*i + 20 * MAXTILE;
		_point4[i].y = -_point4[i].x / 2 + 30 * MAXTILE;
		 
	}

	for (int i = 0; i < MAXTILE; i++)	//y좌표
	{
		for (int j = 0; j < MAXTILE; j++)	//x좌표
		{
			arrayTile[j][i].imgOn = false;
			arrayTile[j][i].keyNum = NULL;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		select[i] = RectMake(600, 100 + 30 * i, 40, 30);
	}

	for (int i = 1; i < 8; i++)
	{
		char keyName[10];
		char fileName[100];
		sprintf(keyName, "타일%d", i);
		sprintf(fileName, "images/TILE%d.bmp", i);
		IMAGEMANAGER->addImage(keyName, fileName, 40, 30, true, RGB(255, 0, 255));
	}

	selectTile.imgOn = false;
	selectTile.keyNum = NULL;
	 
	sprintf(test, "x : ");

	return S_OK;
} 

void mapToolIso::release()
{
	
}

void mapToolIso::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&select[0], _ptMouse))
		{
			selectTile.imgOn = false;
			selectTile.keyNum = NULL;
		}

		for (int i = 1; i < 8; i++)
		{
			if (PtInRect(&select[i], _ptMouse))
			{
				selectTile.imgOn = true;
				selectTile.keyNum = i;
			}
		}

//충돌조건--------------------		
		
		for (int i = 0; i < MAXTILE; i++)	//y좌표
		{    
			for (int j = 0; j < MAXTILE; j++)	//x좌표
			{
				if ((_ptMouse.y < ((_ptMouse.x - 10 * MAXTILE) / 2) - (20 * i) + 100 + 10 * MAXTILE) &&
					(_ptMouse.y > ((_ptMouse.x - 10 * MAXTILE) / 2) - (20 * (i + 1)) + 100 + 10 * MAXTILE) &&
					(_ptMouse.y > (-(_ptMouse.x - 10 * MAXTILE) / 2) + (20 * j) + 100 + 10 * MAXTILE) &&
					(_ptMouse.y < (-(_ptMouse.x - 10 * MAXTILE) / 2) + (20 * (j + 1)) + 100 + 10 * MAXTILE))
				{
					sprintf(test, "x : %d     y : %d", j, i);
					arrayTile[j][i].position.x = 20 * i + 20 * (j+1) + 10 * MAXTILE-20;
					arrayTile[j][i].position.y = -(10 * (i+1)) + 10 * j + 100 + 10 * MAXTILE;
					arrayTile[j][i].imgOn = true;
					arrayTile[j][i].keyNum = selectTile.keyNum;
				}
			}
		}
		

	}//l버튼 키매니저의 끝
}

void mapToolIso::render()
{

	for (int i = 0; i < MAXTILE; i++)
	{
		MoveToEx(getMemDC(), 100+ _point1[i].x, 100 + _point1[i].y, NULL);
		LineTo(getMemDC(), 100 + _point2[i].x, 100 + _point2[i].y);
	}

	MoveToEx(getMemDC(), 100 + 20 * MAXTILE, 100 + ((20 * MAXTILE) / 2) + 10 * MAXTILE, NULL);
	LineTo(getMemDC(), 100 + 20 * MAXTILE * 2, 100 + 20 * MAXTILE - 10 * MAXTILE);
	
	for (int i = 0; i < MAXTILE; i++)
	{
		MoveToEx(getMemDC(), 100 + _point3[i].x, 100 + _point3[i].y, NULL);
		LineTo(getMemDC(), 100 + _point4[i].x, 100 + _point4[i].y);
	}

	MoveToEx(getMemDC(), 100 + 20 * MAXTILE, 100, NULL);
	LineTo(getMemDC(), 100 + 20 * MAXTILE * 2, 100 -20*MAXTILE + 30*MAXTILE);
	
	//-----------------------------------------------------------------------

	for (int i = 0; i < 8; i++)
	{
		FrameRect(getMemDC(), select[i], RGB(0, 255, 0));
	}

	for (int i = 1; i < 8; i++)
	{
		char tempKey[64];
		sprintf(tempKey, "타일%d", i);
		IMAGEMANAGER->findImage(tempKey)->render(getMemDC(), select[i].left, select[i].top);
	}
	

	for (int i = MAXTILE-1; i >= 0; i--)
	{
		for (int j = 0; j < MAXTILE; j++)
		{
			if (arrayTile[j][i].imgOn)
			{
				char tempName[64];
				sprintf(tempName, "타일%d", arrayTile[j][i].keyNum);
				IMAGEMANAGER->findImage(tempName)->render(getMemDC(), arrayTile[j][i].position.x, arrayTile[j][i].position.y);
			}
		}
	}

	if (selectTile.imgOn)
	{
		char tempKey[64];
		sprintf(tempKey, "타일%d", selectTile.keyNum);
		IMAGEMANAGER->findImage(tempKey)->render(getMemDC(), _ptMouse.x - 20, _ptMouse.y - 15);
	}

	TextOut(getMemDC(), 0, 0, test, lstrlen(test));

}
