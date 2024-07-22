#include "pch.h"
#include "AnimationAsset.h"
#include <iostream>

bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//텍스트 파일을 열어서 csv파일 목록을 읽어온다.
	//아래 함수로 csv파일을 처리한다.
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
		std::cout << "파일을 열수 없습니다." << std::endl;	return false;
	}
	std::wstring line;				//한줄의 문자열
	int FrameCount = 0;				//프레임의 갯수
	{
		std::getline(file, line);	//첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> FrameCount;			//타입캐스팅하여 넣어주기
	}
	m_Animations[index].Frames.resize(FrameCount);

	//resize를 사용해야 공간이 잡히기 때문에 바로 인덱스 접근이 가능하다.
	//reserve를 사용하게 되면 capacity(용량) 만 메모리적으로 잡히게 되는것이라서 pushback을 사용한다면 괜찮지만,
	//인덱스적으로 접근하려고 하면 오류가 발생한다.

	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		 //한줄읽기
		std::wstringstream wss(line);//한줄을 읽어서 wstringstream에 저장
		std::wstring token;			 //한줄을 읽고나서 각각의 요소를 저장할 공간. //임시공간(마치 temp처럼)의 역할을 하고있음
		{
			getline(wss, token, L',');// wss의 내용을 ,를 기준으로 문자열을 분리
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

