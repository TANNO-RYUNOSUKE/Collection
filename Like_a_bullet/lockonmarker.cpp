//========================================================================================
//
// �}�[�J�[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "manager.h"
#include "lockonmarker.h"
#include "texture.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================
CMarker::CMarker(int nPriority) :CBillboard(nPriority)
{
	
}
//=============================================
//�f�X�g���N�^
//=============================================
CMarker::~CMarker()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CMarker::Init()
{
	m_posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetHeight(100.0f);
	SetWidth(100.0f);
	CBillboard::Init();
	m_bDisp = false;
	m_pIdxTex = DBG_NEW int;
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CMarker::Uninit()
{
	if (m_pIdxTex != NULL)
	{
		delete m_pIdxTex;
		m_pIdxTex = NULL;
	}
	CBillboard::Uninit();
}
//=============================================
//�X�V�֐�
//=============================================
void CMarker::Update()
{
	CPlayer * pPlayer = CGame::GetPlayer();
	if (pPlayer != NULL)
	{
		if (m_bDisp != true)
		{
			m_posDest = pPlayer->GetPos();
			m_posDest.y += 300.0f;
		}
	}
	SetPos(GetPos() + (m_posDest - GetPos())*0.5f);
	CBillboard::Update();
}
//=============================================
//�`��֐�
//=============================================
void CMarker::Draw()
{
	if (m_bDisp == true)
	{
		CRenderer * pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
		pDevice = pRenderer->GetDevice();

		CBillboard::Draw();
	}
}


//=============================================
//�R���X�g���N�^
//=============================================
CLockonmarker::CLockonmarker() 
{

}
//=============================================
//�f�X�g���N�^
//=============================================
CLockonmarker::~CLockonmarker()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CLockonmarker::Init()
{
	CMarker::Init();
	CTexture * pTex = CManager::GetTexture();
	*m_pIdxTex = pTex->Regist("data\\TEXTURE\\Lockon_sub.png");

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CLockonmarker::Uninit()
{
	CMarker::Uninit();
}
//=============================================
//�X�V�֐�
//=============================================
void CLockonmarker::Update()
{
	CMarker::Update();
}
//=============================================
//�`��֐�
//=============================================
void CLockonmarker::Draw()
{
	CMarker::Draw();
}

//=============================================
//�R���X�g���N�^
//=============================================
CJumpmarker::CJumpmarker()
{

}
//=============================================
//�f�X�g���N�^
//=============================================
CJumpmarker::~CJumpmarker()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CJumpmarker::Init()
{
	CMarker::Init();
	SetHeight(100.0f);
	SetWidth(100.0f);
	CTexture * pTex = CManager::GetTexture();
	*m_pIdxTex = pTex->Regist("data\\TEXTURE\\stagmark.png");
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CJumpmarker::Uninit()
{
	CMarker::Uninit();
}
//=============================================
//�X�V�֐�
//=============================================
void CJumpmarker::Update()
{
	CMarker::Update();
}
//=============================================
//�`��֐�
//=============================================
void CJumpmarker::Draw()
{
	CMarker::Draw();
}