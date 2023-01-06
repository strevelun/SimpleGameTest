#define _CRT_SECURE_NO_WARNINGS

#include "ResourceManager.h"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <d2d1.h>

#include "Util.h"
#include "CBitmap.h"
#include "Game.h"


ResourceManager* ResourceManager::m_inst = nullptr;

bool ResourceManager::Init()
{
	// 폴더 안에 있는 파일명 전부 긁어오기
	// 파일명으로 이미지 불러오기

	//if (!LoadImageFromPath(PATH_NONWALKABLE))
	//	return false;

	return true;
}

bool ResourceManager::LoadImageFromPath(LPCSTR _path)
{
	WIN32_FIND_DATAA data;
	std::vector<CHAR*> imageList;

	char dest[50];

	sprintf(dest, "%s*", _path);

	try
	{
		HANDLE hFind = FindFirstFileA(dest, &data);
		if (hFind == INVALID_HANDLE_VALUE)
			throw std::runtime_error("FindFirstFile 실패");

		while (FindNextFileA(hFind, &data))
		{
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) &&
				!(data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
			{
				//wchar_t wtext[20];
				//mbstowcs(wtext, data.cFileName, strlen(data.cFileName) + 1);
				char temp[260];
				strcpy_s(temp, data.cFileName);
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
		//LoadBitmapFromFile(image, &d2d1Bitmap, _path);
		bitmap->SetBitmap(d2d1Bitmap);
		vec.push_back(bitmap);
	}
	m_mapBitmap.insert(std::make_pair(_path, vec));

	return true;
}