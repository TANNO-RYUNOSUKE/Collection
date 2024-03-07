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
#include "bullet.h"
#include "input.h"

#include "enemy.h"
#include "sound.h"

#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "player.h"
#include "meshfield.h"
#include "objectX.h"
#include "Xmanager.h"
#include "scene.h"

#include "Supporter.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBullet::CBullet(int nPriority):CObject(nPriority)
{
	m_nLife = 0;

	m_Type = TYPE_NONE;
	m_pOrbit = NULL;
	m_pOrbit2 = NULL;
}
//=============================================
//�f�X�g���N�^
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CBullet::Init()
{
	m_pColl = NULL;
	Update();
	switch (m_Type)
	{
	case CBullet::TYPE_NONE:
		break;
	case CBullet::TYPE_PLAYER:
		m_pColl = CSphereCollision::Create(CSphereCollision::TYPE_AUDIENCEATTACK, 10.0f, 5, VECTO3ZERO, VECTO3ZERO,GetMatrixAddress(),this);
		m_pOrbit = COrbit::Create(60, D3DXCOLOR(0.7f, 1.0f, 0.3f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), GetMatrixAddress());
		m_pOrbit2 = COrbit::Create(60, D3DXCOLOR(0.7f, 1.0f, 0.3f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), GetMatrixAddress());
		break;
	case CBullet::TYPE_ENEMY:
		m_pColl = CSphereCollision::Create(CSphereCollision::TYPE_ENEMYATTACK, 10.0f, 5, VECTO3ZERO, VECTO3ZERO, GetMatrixAddress(), this);
		m_pOrbit = COrbit::Create(60, D3DXCOLOR(0.7f, 0.3f, 0.7f, 1.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), GetMatrixAddress());
		m_pOrbit2 = COrbit::Create(60, D3DXCOLOR(0.7f, 0.3f, 0.7f, 1.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), GetMatrixAddress());
		break;
	case CBullet::TYPE_MAX:
		break;
	default:
		break;
	}
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CBullet::Uninit()
{
	if (m_pOrbit != NULL)
	{
		m_pOrbit->end();
		m_pOrbit = nullptr;
	}
	if (m_pOrbit2 != NULL)
	{
		m_pOrbit2->end();
		m_pOrbit2 = nullptr;
	}
	if (m_pColl != NULL)
	{
		delete m_pColl;
		m_pColl = NULL;
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CBullet::Update()
{

	m_nLife--;
	SetPos(GetPos() + GetMove());
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtx);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxTrans);
	if (m_pColl != NULL)
	{
		m_pColl->SetRadius(GetDistance(GetMove()));
	}
	
	if (m_nLife <= 0)
	{
		CObject::Release();
	}
	
}
//=============================================
//�`��֐�
//=============================================
void CBullet::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();


}
//=============================================
//�����֐�
//=============================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE type)
{
	CBullet * pBullet = NULL;
	pBullet = DBG_NEW  CBullet;
	
	pBullet->SetPos(pos);
	
	pBullet->SetMove(move);
	
	pBullet->m_Type = type;
	pBullet->m_nLife = nLife;

	pBullet->Init();
	return pBullet;
}


CMissile::CMissile()
{
}

CMissile::~CMissile()
{
}
HRESULT CMissile::Init()
{
	CBullet::Init();
	return S_OK;
}
void CMissile::Uninit()
{
	CBullet::Uninit();
	if (m_pTarget != NULL)
	{
		delete m_pTarget;
		m_pTarget = NULL;
	}
}
void CMissile::Update()
{
	Homing();
	CBullet::Update();
}
void CMissile::Draw()
{
	CBullet::Draw();
}
CMissile * CMissile::Create(D3DXVECTOR3 pos,  D3DXVECTOR3 vec,int nLife, TYPE type, float fSpeed, float fPower, CObject * Target)
{
	CMissile * pBullet = NULL;
	pBullet = DBG_NEW  CMissile;

	pBullet->SetPos(pos);
	pBullet->SetMove(vec);
	pBullet->SetLife(nLife);
	pBullet->m_pTarget = DBG_NEW CObject*;
	pBullet->m_fSpeed = fSpeed;
	pBullet->m_fPower = fPower;
	pBullet->m_Type = type;
	*(pBullet->m_pTarget) = Target;
	pBullet->Init();
	return pBullet;
}
void CMissile::Homing()
{
	
	if (*m_pTarget != NULL)
	{
		float fSpeed = CManager::GetInstance()->GetDistance(GetMove());
		D3DXVECTOR3 Move = GetMove();
		D3DXVec3Normalize(&Move, &Move);
		D3DXVECTOR3 vec = ((*m_pTarget)->GetPos() + D3DXVECTOR3(0.0f,50.0f,0.0f)) - GetPos();
		D3DXVec3Normalize(&vec, &vec);

		Move = VectorToAngles(Move);




		D3DXVECTOR3 fRotMove, fRotDest, fRotDiff = {};
		D3DXVECTOR3 vecEnemy;

		vecEnemy = D3DXVECTOR3(atan2f(vec.y, sqrtf(powf(vec.x, 2.0f) + powf(vec.z, 2.0f))), atan2f(vec.x, vec.z), 0.0f);

		fRotDiff = vecEnemy - Move;


		if (fRotDiff.x < -D3DX_PI)
		{
			fRotDiff.x += D3DX_PI * 2;
		}
		else if (fRotDiff.x > D3DX_PI)
		{
			fRotDiff.x += -D3DX_PI * 2;
		}
		if (fRotDiff.y < -D3DX_PI)
		{
			fRotDiff.y += D3DX_PI * 2;
		}
		else if (fRotDiff.y > D3DX_PI)
		{
			fRotDiff.y += -D3DX_PI * 2;
		}
		Move += fRotDiff * m_fPower;
		Move = AnglesToVector(Move);
		Move *= m_fSpeed;

		SetMove(Move);
	}
}



CSwarm::CSwarm()
{
}

CSwarm::~CSwarm()
{
}
HRESULT CSwarm::Init()
{
	m_pColl = NULL;
	Update();
	
	switch (m_Type)
	{
	case CBullet::TYPE_NONE:
		break;
	case CBullet::TYPE_PLAYER:
	{
		CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
		D3DXCOLOR Colo = {};
		if (pPlayer != NULL)
		{
			if (pPlayer->GetRank() < 6)
			{
				Colo = D3DXCOLOR(0.3f, 1.0f, 0.7f, 0.5f);
			}
			else
			{
				Colo = D3DXCOLOR(rand() % 80 * 0.01f + 0.2f, rand() % 80 * 0.01f + 0.2f, rand() % 80 * 0.01f + 0.2f, 1.0f);
			}
		}
		if (true)
		{

		}
		m_pColl = CSphereCollision::Create(CSphereCollision::TYPE_AUDIENCEATTACK, 30.0f, 5, VECTO3ZERO, VECTO3ZERO, GetMatrixAddress(), this);
		m_pOrbit = COrbit::Create(120, Colo, D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), GetMatrixAddress());
		m_pOrbit2 = COrbit::Create(120, Colo, D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), GetMatrixAddress());
		break;
		}
	case CBullet::TYPE_ENEMY:
		break;
	case CBullet::TYPE_MAX:
		break;
	default:
		break;
	}
	return S_OK;
	
}
void CSwarm::Uninit()
{
	CBullet::Uninit();
	if (m_pTarget != NULL)
	{
		delete m_pTarget;
		m_pTarget = NULL;
	}
}
void CSwarm::Update()
{
	m_nStop--;
	if (m_nStop > 0)
	{
		SetMove(GetMove()*0.8f);
	}
	else if (m_nStop == 0)
	{
		Homing();
	}
	
	
	
	CBullet::Update();
}
void CSwarm::Draw()
{
	CBullet::Draw();
}
CSwarm * CSwarm::Create(D3DXVECTOR3 pos, D3DXVECTOR3 vec, int nLife, TYPE type, int nStop, CObject * Target)
{
	CSwarm * pBullet = NULL;
	pBullet = DBG_NEW  CSwarm;

	pBullet->SetPos(pos);
	pBullet->SetMove(vec);
	pBullet->SetLife(nLife);
	pBullet->m_pTarget = DBG_NEW CObject*;
	pBullet->m_nStop = nStop;

	pBullet->m_Type = type;
	*(pBullet->m_pTarget) = Target;
	pBullet->Init();
	return pBullet;
}
void CSwarm::Homing()
{

	if (*m_pTarget != NULL)
	{
		float fSpeed = CManager::GetInstance()->GetDistance(GetMove());
		D3DXVECTOR3 Move = GetMove();
		D3DXVec3Normalize(&Move, &Move);
		D3DXVECTOR3 vec = ((*m_pTarget)->GetPos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f)) - GetPos();
		D3DXVec3Normalize(&vec, &vec);

		Move = VectorToAngles(Move);




		D3DXVECTOR3 fRotMove, fRotDest, fRotDiff = {};
		D3DXVECTOR3 vecEnemy;

		vecEnemy = D3DXVECTOR3(atan2f(vec.y, sqrtf(powf(vec.x, 2.0f) + powf(vec.z, 2.0f))), atan2f(vec.x, vec.z), 0.0f);

		fRotDiff = vecEnemy - Move;


		if (fRotDiff.x < -D3DX_PI)
		{
			fRotDiff.x += D3DX_PI * 2;
		}
		else if (fRotDiff.x > D3DX_PI)
		{
			fRotDiff.x += -D3DX_PI * 2;
		}
		if (fRotDiff.y < -D3DX_PI)
		{
			fRotDiff.y += D3DX_PI * 2;
		}
		else if (fRotDiff.y > D3DX_PI)
		{
			fRotDiff.y += -D3DX_PI * 2;
		}
		Move += fRotDiff;
		Move = AnglesToVector(Move);
		Move *= 30.0f;

		SetMove(Move);
	}
}
