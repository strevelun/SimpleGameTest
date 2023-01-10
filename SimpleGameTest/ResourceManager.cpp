#define _CRT_SECURE_NO_WARNINGS

#include "ResourceManager.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <d2d1.h>

#include "CBitmap.h"
#include "Game.h"
#include "CCore.h"

ResourceManager* ResourceManager::m_inst = nullptr;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::Init()
{
	// ���� �ȿ� �ִ� ���ϸ� ���� �ܾ����
	// ���ϸ����� �̹��� �ҷ�����
	
	//if (!LoadImageFromPath(L"Resource\\Image\\Tile\\NonWalkable\\"))
	//	return false;

	return true;
}

bool ResourceManager::LoadImageFromPath(LPWSTR _path)
{
	WIN32_FIND_DATAW data;
	std::vector<LPCWSTR> imageList;

	WCHAR dest[1024]; 
	wsprintf(dest, L"%s*", _path);


	try
	{
		HANDLE hFind = FindFirstFileW(dest, &data);
		if (hFind == INVALID_HANDLE_VALUE)
			throw std::runtime_error("FindFirstFile ����");

		while (FindNextFile(hFind, &data))
		{
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) &&
				!(data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
			{				
				wchar_t* temp = new wchar_t[lstrlenW(_path) + lstrlenW(data.cFileName) + 1];
				//wcscpy_s(temp, lstrlenW(temp), data.cFileName); �״�� �ٿ��ִ� �ڵ�
				wsprintf(temp, L"%s%s", _path, data.cFileName);
				imageList.push_back(temp);
				
			}
		}
		FindClose(hFind);
	}
	catch (std::runtime_error e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	std::vector<CBitmap*> vec;

	for (auto& image : imageList)
	{
		CBitmap* bitmap = new CBitmap();
		ID2D1Bitmap* d2d1Bitmap = nullptr;
		CCore::GetInst()->LoadBitmapFromFile(image, &d2d1Bitmap);
		bitmap->SetBitmap(d2d1Bitmap);
		vec.push_back(bitmap);
		delete image;
	}
	m_mapBitmap.insert(std::make_pair(_path, vec));

	return true;
}