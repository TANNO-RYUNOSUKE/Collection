//========================================================================================
//
// オブジェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "debugproc.h"

//静的メンバ変数の初期化
//CObject *CObject::m_apObject[NUM_PRIORITY][NUM_OBJECT] = {}; 
CObject *CObject::m_apTop[NUM_PRIORITY] = {};
CObject *CObject::m_apCur[NUM_PRIORITY] = {}; 
CObject *CObject::m_pStaticNext = NULL;
int CObject::m_nNumALL = 0;

//=============================================
//コンストラクタ
//=============================================
CObject::CObject(int nPriority)
{
	m_pNext = NULL;
	m_pPrev = NULL;
	if (nPriority >= 0 && nPriority < NUM_PRIORITY)
	{
		m_nPriority = nPriority;
		if (m_apTop[nPriority] == NULL)
		{
			m_apTop[nPriority] = this;
		}
		if (m_apCur[nPriority] == NULL)
		{
			m_apCur[nPriority] = this;
		}
		else
		{
			m_apCur[nPriority]->m_pNext = this;
			this->m_pPrev = m_apCur[nPriority];
			m_apCur[nPriority] = this;
		}
	}
	m_nNumALL++;
	/*m_nID = -1;
	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apObject[nPriority][nCnt] == NULL)
		{
			m_apObject[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_nPriority = nPriority;
			m_nNumALL++;
			break;
		}
	}*/
	m_Type = TYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pIdxTex = NULL;
	
}
//=============================================
//デストラクタ
//=============================================
CObject::~CObject()
{
}
//=============================================
//メモリ解放
//=============================================
void CObject::Release(void)
{
	if (m_pNext != NULL)
	{
		m_pNext->SetPrev(m_pPrev);
	}
	if (m_pPrev != NULL)
	{
		m_pPrev->SetNext(m_pNext);
	}
	if (m_apTop[m_nPriority] == this)
	{
		m_apTop[m_nPriority] = m_pNext;
	}
	if (m_apCur[m_nPriority] == this)
	{
		m_apCur[m_nPriority] = m_pPrev;
	}
	if (m_pStaticNext == this)
	{
		m_pStaticNext = m_pNext;
	}
	this->Uninit();
	delete this;

	m_nNumALL--;
	/*int nIdx = m_nID;
	int nPriority = m_nPriority;
		if (m_apObject[nPriority][nIdx] != NULL)
		{
			m_apObject[nPriority][nIdx]->Uninit();
			delete m_apObject[nPriority][nIdx];
			m_apObject[nPriority][nIdx] = NULL;
			m_nNumALL--;
		}*/
}
//=============================================
//全メモリ解放
//=============================================
void CObject::ReleaseAll(void)
{
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Release();
			pObject = m_pStaticNext;
		}
	}
	m_nNumALL = 0;
}
//=============================================
//更新
//=============================================
void CObject::UpDateAll(void)
{
	CObject * pObject;
	CManager::GetDeb()->Print("原因のオブジェクト数:%d\n", m_nNumALL);
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Update();
			pObject = m_pStaticNext;
		}
		/*for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
		{
			if (m_apObject[nPriority][nCnt] != NULL)
			{
				m_apObject[nPriority][nCnt]->Update();
			}
		}*/
	}
}
//=============================================
//描画
//=============================================
void CObject::DrawAll(void)
{
	CCamera * pCamera = CGame::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Set();
	}
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Draw();
			pObject = m_pStaticNext;
		}
	}
}

D3DXVECTOR3 CObject::GetPos() 
{ 
	return m_pos; 
}//座標取得
