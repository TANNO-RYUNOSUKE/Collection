//========================================================================================
//
// マーカー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "manager.h"
#include "lockonmarker.h"
#include "texture.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CMarker::CMarker(int nPriority) :CBillboard(nPriority)
{
	
}
//=============================================
//デストラクタ
//=============================================
CMarker::~CMarker()
{
}

//=============================================
//初期化関数
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
//終了関数
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
//更新関数
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
//描画関数
//=============================================
void CMarker::Draw()
{
	if (m_bDisp == true)
	{
		CRenderer * pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
		pDevice = pRenderer->GetDevice();

		CBillboard::Draw();
	}
}


//=============================================
//コンストラクタ
//=============================================
CLockonmarker::CLockonmarker() 
{

}
//=============================================
//デストラクタ
//=============================================
CLockonmarker::~CLockonmarker()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CLockonmarker::Init()
{
	CMarker::Init();
	CTexture * pTex = CManager::GetTexture();
	*m_pIdxTex = pTex->Regist("data\\TEXTURE\\Lockon_sub.png");

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CLockonmarker::Uninit()
{
	CMarker::Uninit();
}
//=============================================
//更新関数
//=============================================
void CLockonmarker::Update()
{
	CMarker::Update();
}
//=============================================
//描画関数
//=============================================
void CLockonmarker::Draw()
{
	CMarker::Draw();
}

//=============================================
//コンストラクタ
//=============================================
CJumpmarker::CJumpmarker()
{

}
//=============================================
//デストラクタ
//=============================================
CJumpmarker::~CJumpmarker()
{
}

//=============================================
//初期化関数
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
//終了関数
//=============================================
void CJumpmarker::Uninit()
{
	CMarker::Uninit();
}
//=============================================
//更新関数
//=============================================
void CJumpmarker::Update()
{
	CMarker::Update();
}
//=============================================
//描画関数
//=============================================
void CJumpmarker::Draw()
{
	CMarker::Draw();
}