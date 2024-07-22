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
	//���ҽ��Ŵ����� ���ؼ� �����̸����� �����Ѵ�.
	if (m_pAnimationAsset)
	{
		ResourceManager::GetInstance()->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationAsset = nullptr;
	}
}

void AnimationScene::LoadAnimationAsset(const std::wstring strFilePath)
{
	m_strAnimationAssetFilePath = strFilePath;
	//���ҽ� �Ŵ����� ���� AnimationAsset�� �ε��Ѵ�.
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
	// m_FrameTime�� fTimeElapsed�� ��������  Frame.Duration���� ũ�� 
	// m_FrameIndexCurr�� ������Ű�� m_FrameTime�� 0���� �ʱ�ȭ�Ѵ�.
	// �ϴ� ������ �����ϰ� ó���Ѵ�.

	m_SrcRect = Frame.Source;
	float width = m_SrcRect.right - m_SrcRect.left;
	float height = m_SrcRect.bottom - m_SrcRect.top;
	m_DstRect = { -(width / 2),-(height / 2),width / 2,height / 2 };

	if (m_bMirror)	// �¿� ������ �ϱ����ؼ� x�� �������� ���̳ʽ�. Translation�� ����� �̹����� ���� ����
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) * // ���������� �ǵ��� ��ġ��.
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
