#pragma once
#include <string>
#include <unordered_map>
#include <Windows.h>

class ResourceManager
{
private:
	static ResourceManager* m_inst;

private:
	std::unordered_map<std::string, std::vector<class CBitmap*>> m_mapBitmap;

public:
	static ResourceManager* GetInst()
	{
		if (m_inst == nullptr)
			m_inst = new ResourceManager();
		return m_inst;
	}

	bool Init();

	bool LoadImageFromPath(LPCSTR _path);
};