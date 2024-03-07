//========================================================================================
//
// �o���b�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Collision.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "player.h"
#include "enemymanager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CCollision::CCollision(int nPriority) :CObject(nPriority)
{
	
	m_Type = TYPE_NONE;
	
}
//=============================================
//�f�X�g���N�^
//=============================================
CCollision::~CCollision()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CCollision::Init()
{

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CCollision::Uninit()
{
	if (m_pIdxTex != NULL)
	{
		delete m_pIdxTex;
		m_pIdxTex = NULL;
	}

}
//=============================================
//�X�V�֐�
//=============================================
void CCollision::Update()
{


}
//=============================================
//�`��֐�
//=============================================
void CCollision::Draw()
{
	
}
//=============================================
//�����֐�
//=============================================
CCollision * CCollision::Create(D3DXVECTOR3 pos, int nDamage, TYPE type)
{
	CCollision * pCollision = NULL;
	pCollision = DBG_NEW  CCollision;

	pCollision->SetPos(pos);
	pCollision->m_Type = type;
	pCollision->m_nDamage = nDamage;
	pCollision->Init();
	return pCollision;
}
//=============================================
//�R���W����
//=============================================
bool CCollision::CollisionEnemy(D3DXVECTOR3 pos)
{
	CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();

	SetPos(pos);
	
	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (*(pEnemy + nCnt) != NULL)
		{
			D3DXVECTOR3 vec = pos - pEnemy[nCnt]->GetPos();
			if (CManager::GetDistance(vec) <= 300.0f)
			{
				pEnemy[nCnt]->AddLife(-m_nDamage);
			}
		}
	}
	return false;
}
bool CCollision::CollisionPlayer(D3DXVECTOR3 pos)
{
	CPlayer * pPlayer = CGame::GetPlayer();
	if (pPlayer != NULL)
	{

		CModel * pModel = pPlayer->GetModelUp();


		D3DXVECTOR3 max = pModel->GetMax() + pPlayer->GetPos();
		D3DXVECTOR3 min = pModel->GetMin() + pPlayer->GetPos();

		if (pos.x <= max.x && pos.y <= max.y && pos.z <= max.z)
		{
			if (pos.x >= min.x && pos.y >= min.y && pos.z >= min.z)
			{
				pPlayer->AddLife(-1);
				return true;
			}
		}

	}
	return false;
}