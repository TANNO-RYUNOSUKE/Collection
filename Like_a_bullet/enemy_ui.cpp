//========================================================================================
//
// ナンバー
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
//=============================================
//コンストラクタ
//=============================================
CEnemy_UI::CEnemy_UI()
{
	for (int nCnt = 0; nCnt < NUM_E_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_ndata = 0;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 10 + 130.0f , SCREEN_HEIGHT / 10, 0.0f);
}



//=============================================
//デストラクタ
//=============================================
CEnemy_UI::~CEnemy_UI()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CEnemy_UI::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_E_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(1);
		m_apNumber[nCnt]->Set(D3DXVECTOR3(m_pos.x + 50.0f * nCnt, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 175.0f, 65.0f);
	}
	m_pUi = m_pUi->Create(D3DXVECTOR3(SCREEN_WIDTH / 10 , SCREEN_HEIGHT / 10, 0.0f), 90.0f, 243.0f, 6, "data\\TEXTURE\\EnemyCount.png");
	return S_OK;
}
//=============================================
//生成関数
//=============================================
CEnemy_UI * CEnemy_UI::Create(void)
{
	CEnemy_UI * pEnemy_UI = NULL;
	pEnemy_UI = DBG_NEW CEnemy_UI;
	pEnemy_UI->Init();
	return pEnemy_UI;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CEnemy_UI::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_E_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CEnemy_UI::Update(void)
{
	CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();
	m_ndata = 0;
	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (pEnemy[nCnt] != NULL)
		{
			m_ndata++;
		}
	}

	m_apNumber[0]->Setdata(m_ndata % 100 / 10);
	m_apNumber[1]->Setdata(m_ndata % 10 / 1);
	for (int nCnt = 0; nCnt < NUM_E_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
	
	
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CEnemy_UI::Draw(void)
{
		for (int nCnt = 0; nCnt < NUM_E_UINUMBER; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
}
