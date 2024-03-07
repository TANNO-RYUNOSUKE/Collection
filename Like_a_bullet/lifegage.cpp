//========================================================================================
//
// ゲージ
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "Enemy_UI.h"
#include "object2D.h"
#include "scene.h"
#include "Enemy.h"
#include "manager.h"
#include "enemymanager.h"
#include "lifegage.h"
#include "player.h"
#include "scene.h"
//=============================================
//コンストラクタ
//=============================================
CGage::CGage()
{
	m_pGage = NULL;
	m_pGageRed = NULL;
}



//=============================================
//デストラクタ
//=============================================
CGage::~CGage()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CGage::Init(void)
{
	m_ndata = 0;
	for (int nCnt = 0; nCnt < LIFE_LENGTH; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(1);
		m_apNumber[nCnt]->Set(D3DXVECTOR3(GetPos().x + 20.0f * nCnt - m_fWidth / 2, GetPos().y - 50.0f, GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 81.0f, 21.0f);
	}
	m_pGageRed = CObject2D::Create(GetPos(), 15.0f, m_fWidth);
	m_pGage = CObject2D::Create(GetPos(), 15.0f, m_fWidth);

	m_pGageRed->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	return S_OK;
}
//=============================================
//生成関数
//=============================================
CGage * CGage::Create(D3DXVECTOR3 pos, float fWidth, int nMax)
{
	CGage * pEnemy_UI = NULL;
	pEnemy_UI = DBG_NEW CGage;
	pEnemy_UI->m_fWidth = fWidth;
	pEnemy_UI->SetPos(pos);
	pEnemy_UI->m_nMax = nMax;
	pEnemy_UI->Init();
	return pEnemy_UI;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CGage::Uninit(void)
{
	for (int nCnt = 0; nCnt < LIFE_LENGTH; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CGage::Update(void)
{
	CPlayer * pPlayer = CGame::GetPlayer();
	if (pPlayer != NULL)
	{
		m_ndata = pPlayer->GetLife();
		
		m_pGage->SetWidth(m_pGage->GetWidth() + (((m_fWidth/(float)m_nMax)* pPlayer->GetLife()) - m_pGage->GetWidth()) * 0.3f);
		m_pGageRed->SetWidth(m_pGageRed->GetWidth() + (((m_fWidth / (float)m_nMax)* pPlayer->GetLife()) - m_pGageRed->GetWidth()) * 0.05f);
	}
	else
	{
		m_ndata = 0;
		m_pGage->SetWidth(m_pGage->GetWidth() - m_pGage->GetWidth() * 0.3f);
		m_pGageRed->SetWidth(m_pGageRed->GetWidth() - m_pGageRed->GetWidth() * 0.05f);
	}
	//if (m_pGage->GetWidth() != (((m_fWidth / (float)m_nMax)* pPlayer->GetLife())))
	//{
	//	m_pGage->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	//	for (int nCnt = 0; nCnt < LIFE_LENGTH; nCnt++)
	//	{
	//		m_apNumber[nCnt]->Get2D()->SetCol(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	//	}
	//}
	//else
	//{
	//	m_pGage->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	for (int nCnt = 0; nCnt < LIFE_LENGTH; nCnt++)
	//	{
	//		m_apNumber[nCnt]->Get2D()->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	}
	//}

	m_apNumber[0]->Setdata(m_ndata % 100000 / 10000);
	m_apNumber[1]->Setdata(m_ndata % 10000 / 1000);
	m_apNumber[2]->Setdata(m_ndata % 1000 / 100);
	m_apNumber[3]->Setdata(m_ndata % 100 / 10);
	m_apNumber[4]->Setdata(m_ndata % 10 / 1);

	for (int nCnt = 0; nCnt < LIFE_LENGTH; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CGage::Draw(void)
{
	for (int nCnt = 0; nCnt < LIFE_LENGTH; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}
