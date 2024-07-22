#pragma once
#include "AnimationAsset.h"
class AnimatorAsset;
class ResourceManager
{

public:
	ResourceManager() = default;
	~ResourceManager();

	static ResourceManager* GetInstance()
	{
		static ResourceManager _instance;
		return &_instance;
	}

	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;				//비트맵이미지 관리용
	std::map<std::wstring, AnimationAsset*> m_AnimationAssetMap;	//애니메이션 관리용

	bool CreateD2DBitmap(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	//이미 사용된 비트맵을 재활용할수있도록 맵에서 있는지 없는지 찾아줌
	// 없으면 만드는 기능.
	void ReleaseD2DBitmap(std::wstring strFilePath);

	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset);
	void ReleaseAnimationAsset(std::wstring strFilePath);
};
