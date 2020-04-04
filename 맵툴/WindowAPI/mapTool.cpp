#include "stdafx.h"
#include "mapTool.h"


HRESULT mapTool::init()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			_vTile[i][j].rc = RectMake(100 + i * 32, 100 + j * 32, 32, 32);
			_vTile[i][j].imgOn = false;
			_vTile[i][j].keyNum = NULL;
		}
	}

	for (int i = 0; i < 12; i < i++)
	{
		select[i] = RectMake(500, 100 + i * 32, 32, 32);
		selectOn[i] = false;
	}

	selectTile.rc = RectMake(_ptMouse.x - 16, _ptMouse.y - 16, 32, 32);
	selectTile.imgOn = false;
	selectTile.keyNum = NULL;

	for (int i = 0; i < 12; i++)
	{
		char fileName[100];
		sprintf(fileName, "images/0_Tile01_%d.bmp", i);
		char keyName[100];
		sprintf(keyName, "鸥老%d", i);
		IMAGEMANAGER->addImage(keyName, fileName, 32, 32, true, RGB(255, 0, 255));
	}

	_button[0].rc = RectMake(100, 500, 100, 50);
	_button[1].rc = RectMake(220, 500, 100, 50);
	_button[2].rc = RectMake(340, 500, 100, 50);

	sprintf(_button[0].text, "SAVE");
	sprintf(_button[1].text, "LOAD");
	sprintf(_button[2].text, "CLEAR");
	
	
	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		for (int j = 0; j < 12; j++)
		{
			selectOn[j] = false;
		}

		for (int i = 0; i < 12; i++)
		{
			if (PtInRect(&select[i], _ptMouse))
			{
				if (selectOn[i])
				{
					selectOn[i] = false;
				}
				else
				{
					selectOn[i] = true;
				}
			}
		}


		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (PtInRect(&_vTile[i][j].rc, _ptMouse))
				{

					_vTile[i][j].imgOn = true;
					_vTile[i][j].keyNum = selectTile.keyNum;

				}
			}
		}


		//SAVE
		if (PtInRect(&_button[0].rc, _ptMouse))
		{
			this->Save();
		}

		//LOAD
		if (PtInRect(&_button[1].rc, _ptMouse))
		{
			this->Load();
		}

		//CLEAR
		if (PtInRect(&_button[2].rc, _ptMouse))
		{
			this->init();
		}


	}

	//-------------------------------KEYMANAGER 场--------------

	for (int i = 0; i < 12; i++)
	{
		if (selectOn[i])
		{
			selectTile.rc = RectMake(_ptMouse.x - 16, _ptMouse.y - 16, 32, 32);
			selectTile.imgOn = true;
			selectTile.keyNum = i;
		}
	}

}

void mapTool::render()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			FrameRect(getMemDC(), _vTile[i][j].rc, RGB(255, 255, 0));
		}
	}

	for (int i = 0; i < 12; i++)
	{
		char keyName[100];
		sprintf(keyName, "鸥老%d", i);

		if (selectOn[i] ==  false)
		{
			FrameRect(getMemDC(), select[i], RGB(255, 0, 0));
		}
		else
		{
			FrameRect(getMemDC(), select[i], RGB(0, 255, 0));
			IMAGEMANAGER->findImage(keyName)->render(getMemDC(), selectTile.rc.left, selectTile.rc.top);
		}

		IMAGEMANAGER->findImage(keyName)->render(getMemDC(), select[i].left, select[i].top);
		
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_vTile[i][j].imgOn)
			{
				char tempName[100];
				sprintf(tempName, "鸥老%d", _vTile[i][j].keyNum);
				IMAGEMANAGER->findImage(tempName)->render(getMemDC(), _vTile[i][j].rc.left, _vTile[i][j].rc.top);
				
			}
		}

	}

	for (int i = 0; i < 3; i++)
	{
		Rectangle(getMemDC(), _button[i].rc);
		DrawText(getMemDC(), _button[i].text, -1, &_button[i].rc, DT_CENTER | DT_VCENTER);
	}

}



void mapTool::Save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _vTile, sizeof(tagTile)*100, &write, NULL);
	CloseHandle(file);
}

void mapTool::Load()
{
	HANDLE file;
	DWORD read;


	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _vTile, sizeof(tagTile) * 100, &read, NULL);
	CloseHandle(file);

}
