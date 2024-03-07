//========================================================================================
//
// ナンバー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "Wave_UI.h"
#include "object2D.h"
#include "scene.h"
#include "wave.h"

//=============================================
//コンストラクタ
//=============================================
CWave_UI::CWave_UI()
{
	for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_ndata = 0;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 180.0f, SCREEN_HEIGHT / 2, 0.0f);
}



//=============================================
//デストラクタ
//=============================================
CWave_UI::~CWave_UI()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CWave_UI::Init(void)
{
	m_nCntDisp = 0;
	for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(1);
		m_apNumber[nCnt]->Set(D3DXVECTOR3(m_pos.x + 130.0f * nCnt, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 175.0f);
		
	}
	m_pos2 = m_pos * 0.2f;
	m_pos2.y += 100.0f;
	m_NumberSize1 = D3DXVECTOR3(m_apNumber[0]->Get2D()->GetWidth(), m_apNumber[0]->Get2D()->GetHeight(), 0.0f);
	m_NumberSize2 = m_NumberSize1* 0.2f;
	m_pUi = m_pUi->Create(D3DXVECTOR3(SCREEN_WIDTH / 2 -100.0f, SCREEN_HEIGHT / 2, 0.0f), 223.0f, 473.0f, 6, "data\\TEXTURE\\WAVE.png");
	m_Uipos1 = m_pUi->GetPos();
	m_Uipos2 = m_Uipos1 * 0.2f;
	m_Uipos2.y += 100.0f;
	m_Uisize1 = D3DXVECTOR3(m_pUi->Get2D()->GetWidth(), m_pUi->Get2D()->GetHeight(), 0.0f);
	m_Uisize2 = m_Uisize1* 0.2f;
	return S_OK;
}
//=============================================
//生成関数
//=============================================
CWave_UI * CWave_UI::Create(void)
{
	CWave_UI * pWave_UI = NULL;
	pWave_UI = DBG_NEW CWave_UI;
	pWave_UI->Init();
	return pWave_UI;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CWave_UI::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CWave_UI::Update(void)
{
	m_ndata = CGame::GetWave()->GetCnt();
	if (m_ndata > 99)
	{
		m_ndata = 99;
	}


	m_apNumber[0]->Setdata(m_ndata % 100 / 10);
	m_apNumber[1]->Setdata(m_ndata % 10 / 1);
	for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
	m_nCntDisp--;
	if (m_nCntDisp <= 0)
	{
		for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
		{
			m_apNumber[nCnt]->Get2D()->SetPos(m_apNumber[nCnt]->Get2D()->GetPos() + (D3DXVECTOR3(m_pos2.x + (m_apNumber[nCnt]->Get2D()->GetWidth() * 0.75f * (float)nCnt), m_pos2.y, m_pos2.z) - m_apNumber[nCnt]->Get2D()->GetPos()) * 0.1f);
			m_apNumber[nCnt]->Get2D()->SetHeight(m_apNumber[nCnt]->Get2D()->GetHeight()+(m_NumberSize2.y - m_apNumber[nCnt]->Get2D()->GetHeight()) * 0.1f);
			m_apNumber[nCnt]->Get2D()->SetWidth(m_apNumber[nCnt]->Get2D()->GetWidth() + (m_NumberSize2.x - m_apNumber[nCnt]->Get2D()->GetWidth()) * 0.1f);
		}
		
		m_nCntDisp = 0;
		m_pUi->SetPos(m_pUi->GetPos() + (m_Uipos2 - m_pUi->GetPos()) * 0.1f);
		m_pUi->SetHeight(m_pUi->GetHeight() + (m_Uisize2.y - m_pUi->GetHeight()) * 0.1f);
		m_pUi->SetWidth(m_pUi->GetWidth() + (m_Uisize2.x - m_pUi->GetWidth()) * 0.1f);
	}
	else
	{
		for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
		{
			m_apNumber[nCnt]->SetDisp(true);
			m_apNumber[nCnt]->Get2D()->SetPos(m_apNumber[nCnt]->Get2D()->GetPos() + (D3DXVECTOR3(m_pos.x + (m_apNumber[nCnt]->Get2D()->GetWidth() * 0.75f * (float)nCnt), m_pos.y, m_pos.z) - m_apNumber[nCnt]->Get2D()->GetPos()) * 0.1f);
			m_apNumber[nCnt]->Get2D()->SetHeight(m_apNumber[nCnt]->Get2D()->GetHeight() + (m_NumberSize1.y - m_apNumber[nCnt]->Get2D()->GetHeight()) * 0.1f);
			m_apNumber[nCnt]->Get2D()->SetWidth(m_apNumber[nCnt]->Get2D()->GetWidth() + (m_NumberSize1.x - m_apNumber[nCnt]->Get2D()->GetWidth()) * 0.1f);
		}
		m_pUi->SetDisp(true);
		m_pUi->SetPos(m_pUi->GetPos() + (m_Uipos1 - m_pUi->GetPos()) * 0.1f);
		m_pUi->SetHeight(m_pUi->GetHeight() + (m_Uisize1.y - m_pUi->GetHeight()) * 0.1f);
		m_pUi->SetWidth(m_pUi->GetWidth() + (m_Uisize1.x - m_pUi->GetWidth()) * 0.1f);
	}
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CWave_UI::Draw(void)
{
	if (m_nCntDisp > 0)
	{
		for (int nCnt = 0; nCnt < NUM_UINUMBER; nCnt++)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}
