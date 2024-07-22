#pragma once
#include "Scene.h"
#include <string>

class D2DRenderer;
class BitmapScene : public Scene
{
public:
	BitmapScene();
	virtual ~BitmapScene();

	bool Load(const std::wstring& strFileName);

	std::wstring m_strFileName;
	ID2D1Bitmap* m_pBitmap = nullptr;


	void Update();
	void Render();
};

