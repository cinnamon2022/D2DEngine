#include "pch.h"
#include "AnimationScene.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"

AnimationScene::AnimationScene()
{
}

AnimationScene::~AnimationScene()
{
	//리소스매니저를 통해서 에셋이름으로 해제한다.
	if (m_pAnimationAsset)
	{
		ResourceManager::GetInstance()->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationAsset = nullptr;
	}
}

void AnimationScene::LoadAnimationAsset(const std::wstring strFilePath)
{
	m_strAnimationAssetFilePath = strFilePath;
	//리소스 매니저를 통해 AnimationAsset을 로드한다.
	ResourceManager::GetInstance()->CreateAnimationAsset(m_strAnimationAssetFilePath, &m_pAnimationAsset);
}

void AnimationScene::Update()
{
	__super::Update();
	assert(m_pAnimationAsset != nullptr);
	if (m_pAnimationInfo == nullptr) return;

	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size() - 1;
	m_FrameTime += TimeManager::GetInstance()->GetDeltaTime();
	if (m_FrameTime >= Frame.Duration)
	{
		m_FrameIndexCurr++;
		m_FrameTime = 0;
		if (m_FrameIndexCurr >= MaxFrameCount)
		{
			m_FrameIndexCurr -= MaxFrameCount;
		}
	}
	// m_FrameTime에 fTimeElapsed을 누적시켜  Frame.Duration보다 크면 
	// m_FrameIndexCurr를 증가시키고 m_FrameTime을 0으로 초기화한다.
	// 일단 루프만 가정하고 처리한다.

	m_SrcRect = Frame.Source;
	float width = m_SrcRect.right - m_SrcRect.left;
	float height = m_SrcRect.bottom - m_SrcRect.top;
	m_DstRect = { -(width / 2),-(height / 2),width / 2,height / 2 };

	if (m_bMirror)	// 좌우 반전을 하기위해서 x축 스케일을 마이너스. Translation은 출력할 이미지의 원점 정보
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) * // 원점기준이 되도록 고치기.
			D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
}

void AnimationScene::Render()
{
	if (m_pAnimationInfo == nullptr)return;


	D2D1_MATRIX_3X2_F Transform = m_ImageTransform * m_WorldTransform * D2DRenderer::m_CameraTransform;

	D2DRenderer::Get()->pHRenderTarget->SetTransform(Transform);
	D2DRenderer::Get()->pHRenderTarget->DrawBitmap(m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);


}

void AnimationScene::SetAnimation(int index, bool mirror)
{
	assert(m_pAnimationAsset != nullptr);
	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(index);
	if (pFound == nullptr)return;

	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
}
