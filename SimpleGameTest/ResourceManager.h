#pragma once
#include <string>
#include <unordered_map>
#include <Windows.h>

class ResourceManager
{
private:
	static ResourceManager* m_inst;

private:
	std::unordered_map<LPWSTR, std::vector<class CBitmap*>> m_mapBitmap;

public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInst()
	{
		if (m_inst == nullptr)
			m_inst = new ResourceManager();
		return m_inst;
	}

	static void DeleteInst()
	{
		if (m_inst != nullptr)
		{
			delete m_inst;
			m_inst = nullptr;
		}
	}

	bool Init();

	bool LoadImageFromPath(LPWSTR _path);
};