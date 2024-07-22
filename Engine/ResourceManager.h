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

	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;				//��Ʈ���̹��� ������
	std::map<std::wstring, AnimationAsset*> m_AnimationAssetMap;	//�ִϸ��̼� ������

	bool CreateD2DBitmap(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	//�̹� ���� ��Ʈ���� ��Ȱ���Ҽ��ֵ��� �ʿ��� �ִ��� ������ ã����
	// ������ ����� ���.
	void ReleaseD2DBitmap(std::wstring strFilePath);

	bool CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset);
	void ReleaseAnimationAsset(std::wstring strFilePath);
};
