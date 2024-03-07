//========================================================================================
//
// アイテム
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "item.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"
#include "score.h"
#include "itemmanager.h"
#include "scene.h"
#include "meshfield.h"

//=============================================
//コンストラクタ
//=============================================
CItem::CItem():CObject()
{
	CItemManager * pManager = NULL;
	pManager = CManager::GetItemManager();
	m_nScore = 0;
	m_nLifeCount = 0;
	pManager->Regist(this);
}
//=============================================
//デストラクタ
//=============================================
CItem::~CItem()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CItem::Init()
{
	m_nLife = 1800;
	m_pParticle = CParticle::Create(GetPos(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1800, 10, 60, 230, 1, 0.9f, "data\\TEXTURE\\square.jpg");

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CItem::Uninit()
{
	CItemManager * pManager = NULL;
	
	
	pManager = CManager::GetItemManager();
	pManager->Release(m_nID);
}
//=============================================
//更新関数
//=============================================
void CItem::Update()
{
	m_nLifeCount++;
	m_nLife--;
	SetPos(GetPos() + GetMove());
	SetMove(GetMove()*0.99f);
	
	
	if (m_nLife <= 0)
	{
		m_pParticle->Release();
		Release();
	}
	else
	{
		m_pParticle->SetLife(6);
		m_pParticle->SetColor(D3DXCOLOR((rand() % 10) * 0.01f, (rand() % 10) * 0.01f, (rand() % 100) * 0.01f, 1.0f));
		m_pParticle->SetPos(GetPos());
	}
	if (CGame::GetMeshfield()->Collision(GetPosAddress()) == true)
	{
		SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
	}
}
//=============================================
//描画関数
//=============================================
void CItem::Draw()
{
	
}
//=============================================
//生成関数
//=============================================
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nScore)
{
	CItem * pItem = NULL;
	pItem = DBG_NEW CItem;
	pItem->SetPos(pos);
	pItem->SetMove(move);
	pItem->m_nScore = nScore;
	pItem->Init();
	return pItem;
}
//=============================================
//コリジョン
//=============================================
bool CItem::Collision(D3DXVECTOR3 pos)
{
	if (CManager::GetDistance(GetPos() - pos) < 300.0f)
	{
		CParticle::Create(GetPos(), D3DXCOLOR(0.2f, 0.2f, 0.5f, 0.2f), 1, 200, 100, 100, 16, 0.99f, "data\\TEXTURE\\square.jpg");
		CGame::GetScore()->Add(m_nScore);
		m_pParticle->Release();
		
		Release();
		
		return true;
	}
	
	return false;
}