#include "pch.h"
#include "AnimationAsset.h"
#include <iostream>

bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//�ؽ�Ʈ ������ ��� csv���� ����� �о�´�.
	//�Ʒ� �Լ��� csv������ ó���Ѵ�.
	if (FilePath == std::wstring(L"Background"))
	{
		LoadAnimationFromCSV(0, L"Background.csv");
	}
	if (FilePath == std::wstring(L"Run"))
	{
		LoadAnimationFromCSV(1, L"Run.csv");
	}
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)
{
	std::wifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "������ ���� �����ϴ�." << std::endl;	return false;
	}
	std::wstring line;				//������ ���ڿ�
	int FrameCount = 0;				//�������� ����
	{
		std::getline(file, line);	//ù��° �� �б�
		std::wstringstream wss(line);
		wss >> FrameCount;			//Ÿ��ĳ�����Ͽ� �־��ֱ�
	}
	m_Animations[index].Frames.resize(FrameCount);

	//resize�� ����ؾ� ������ ������ ������ �ٷ� �ε��� ������ �����ϴ�.
	//reserve�� ����ϰ� �Ǹ� capacity(�뷮) �� �޸������� ������ �Ǵ°��̶� pushback�� ����Ѵٸ� ��������,
	//�ε��������� �����Ϸ��� �ϸ� ������ �߻��Ѵ�.

	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		 //�����б�
		std::wstringstream wss(line);//������ �о wstringstream�� ����
		std::wstring token;			 //������ �а��� ������ ��Ҹ� ������ ����. //�ӽð���(��ġ tempó��)�� ������ �ϰ�����
		{
			getline(wss, token, L',');// wss�� ������ ,�� �������� ���ڿ��� �и�
			m_Animations[index].Frames[j].Source.left = _wtof(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.top = _wtof(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.right = _wtof(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.bottom = _wtof(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.x = _wtof(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.y = _wtof(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Duration = _wtof(token.c_str());
		}
	}
	return true;
}

