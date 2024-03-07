//========================================================================================
//CExplosion
// フェード
// Author: 丹野 竜之介
//
//========================================================================================
#include "explosion.h"
#include "manager.h"
#include "animbillboard.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "effekseerControl.h"
#include "camera.h"
CExplosion::CExplosion()
{

}

CExplosion::~CExplosion()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CExplosion::Init()
{
	
	CEffekseer::GetInstance()->Create("data\\Effekseer\\explosion_bossAttack.efkefc", GetPos(), VECTO3ZERO, VECTO3ZERO, 100.0f);
	pCol = NULL;
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CExplosion::Uninit()
{
	if (pCol != NULL)
	{
		delete pCol;
		pCol = NULL;
	}
}
//=============================================
//更新関数
//=============================================
void CExplosion::Update()
{
	m_nLife--;
	if (m_nLife == 0)
	{
		CEffekseer::GetInstance()->Create("data\\Effekseer\\fire.efkefc", GetPos(), VECTO3ZERO, VECTO3ZERO, 100.0f);
		pCol = CSphereCollision::Create(CSphereCollision::TYPE_ENEMYATTACK, 600.0f, 15, GetPos(), D3DXVECTOR3(0.0f, 50.0f, 0.0f), NULL, this);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
		CCamera* pCamera = CManager::GetInstance()->GetScene()->GetCamera();
		pCamera->SetShake(12);
	} 
	if (m_nLife <= -30)
	{
		Release();
	}
}
//=============================================
//描画関数
//=============================================
void CExplosion::Draw()
{

}
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, int nLife)
{
	CExplosion * pEx = NULL;
	pEx = DBG_NEW CExplosion();
	pEx->SetPos(pos);
	pEx->SetLife(nLife);
	pEx->Init();
	return pEx;
}