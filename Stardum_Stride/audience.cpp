//============================================================
//
//	�U���r�b�g�Ǘ� [audience.cpp]
//	Author�F�O�엳�V��
//
//============================================================
#include "Audience.h"
#include "renderer.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "Supporter.h"
#include "bullet.h"

Clist<CAudience *> CAudience::List = {};

//====================================
//�R���X�g���N�^�A�f�X�g���N�^
//====================================
CAudience::CAudience(int nPriority) : CObject(nPriority)
{
	m_nStateCount = 0;
	m_RotDest = VECTO3ZERO;
	m_PosDest = VECTO3ZERO;
	m_state = STATE_NONE;
	m_pModel = NULL;
	List.Regist(this);
}

CAudience::~CAudience()
{
	List.Delete(this);
}

//====================================
//������
//====================================
HRESULT CAudience::Init(void)
{
	m_bActive = false;
	m_nOffsetCount = 120;
	SetPos(D3DXVECTOR3((float)(rand() % 1000 - 500), (float)(rand() % 500), (float)(rand() % 1000 - 500)));
	m_Offset = D3DXVECTOR3((float)(rand() % 500 - 250), (float)(rand() % 200), (float)(rand() % 500 - 250));
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	m_pModel = CObjectX::Create("data\\MODEL\\Audience.x",VECTO3ZERO);
	m_state = STATE_NEUTRAL;
	m_pActiveAttack = &CAudience::Swarm;
	m_pOrbit = COrbit::Create(60, D3DXCOLOR(0.7f, 1.0f, 0.3f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), GetMatrixAddress());
	m_pOrbit2 = COrbit::Create(60, D3DXCOLOR(0.7f, 1.0f, 0.3f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), GetMatrixAddress());
	m_pOrbit->SetDisp(false);
	m_pOrbit2->SetDisp(false);
	m_pOrbit2->Update();
	m_pOrbit->Update();
	return S_OK;
}
//====================================
//�I��
//====================================
void CAudience::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		m_pModel = NULL;
	}
	if (m_pOrbit != NULL)
	{
		m_pOrbit->Uninit();
		m_pOrbit = NULL;
	}
	if (m_pOrbit2 != NULL)
	{
		m_pOrbit2->Uninit();
		m_pOrbit2 = NULL;
	}
}
//====================================
//�X�V
//====================================
void CAudience::Update(void)
{
	D3DXVECTOR3 animRot = m_RotDest - GetRot();
	if (animRot.x< -D3DX_PI)
	{
		animRot.x += D3DX_PI * 2;
	}
	else if (animRot.x > D3DX_PI)
	{
		animRot.x += -D3DX_PI * 2;
	}
	if (animRot.y< -D3DX_PI)
	{
		animRot.y += D3DX_PI * 2;
	}
	else if (animRot.y > D3DX_PI)
	{
		animRot.y += -D3DX_PI * 2;
	}
	if (animRot.z< -D3DX_PI)
	{
		animRot.z += D3DX_PI * 2;
	}
	else if (animRot.z > D3DX_PI)
	{
		animRot.z += -D3DX_PI * 2;
	}
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (pPlayer != NULL)
	{
	
		if (pPlayer->GetTarget()!= NULL)
		{
			m_PosDest = pPlayer->GetTarget()->GetPos();
			m_PosDest.y += 100.0f;
			m_PosDest += m_Offset;
			D3DXVECTOR3 vec = m_PosDest - GetPos();
			D3DXVec3Normalize(&vec, &vec);
			SetMove(GetMove() + vec* 0.15f);
			SetPos(GetPos() + GetMove());
			SetMove(GetMove()* 0.99f);
		}
		else
		{
			m_PosDest = pPlayer->GetPos();
			m_PosDest.y += 100.0f;
		
			m_PosDest += m_Offset;
			m_RotDest = VectorToAngles(GetPos() - m_PosDest);
			D3DXVECTOR3 vec = m_PosDest - GetPos();
			D3DXVec3Normalize(&vec, &vec);
			SetMove(GetMove() + vec* 0.03f);
			SetPos(GetPos() + GetMove());
			SetMove(GetMove()* 0.99f);
		}
	}
	m_nOffsetCount--;
	if (m_nOffsetCount < 0)
	{
		m_Offset = D3DXVECTOR3((float)(rand() % 500 - 250), (float)(rand() % 200), (float)(rand() % 500 - 250));
		m_nOffsetCount = 120;
	}
	if (!m_bActive)
	{
		m_pOrbit->SetDisp(false);
		m_pOrbit2->SetDisp(false);
		m_Offset.y = 400.0f;
	}
	else
	{
		m_pOrbit->SetDisp(true);
		m_pOrbit2->SetDisp(true);
	}
	SetRot(GetRot() + animRot /30);
	m_pModel->SetPos(GetPos());
	m_pModel->SetRot(GetRot());
	Attack();
}
//====================================
//�`��
//====================================
void CAudience::Draw(void)
{	
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

	m_pModel->Draw();
}
//====================================
//�U��
//====================================
void CAudience::Attack()
{
	if (m_bActive)
	{
		m_nStateCount--;
		switch (m_state)
		{
		case CAudience::STATE_NONE:
			break;
		case CAudience::STATE_NEUTRAL:
			break;
		case CAudience::STATE_AUTOATTACK:
			if (m_nStateCount % 60 == 0)
			{
				CEnemy * pEnemy = NULL;
				int nNum = CEnemy::EnemyList.GetNum();
				if (nNum > 0)
				{
					int nTarget = rand() % nNum;
					pEnemy = CEnemy::EnemyList.Get(nTarget);
				}
				if (pEnemy != NULL)
				{
					D3DXVECTOR3 Vec = pEnemy->GetPos() - GetPos();
					D3DXVec3Normalize(&Vec, &Vec);
					CBullet::Create(GetPos(), Vec * 10.0f, 60, CBullet::TYPE_PLAYER);
				}
			}
			break;
		case CAudience::STATE_MANUALATTACK:

			(this->*m_pActiveAttack)();
			break;
		case CAudience::STATE_DEATH:
			break;
		case CAudience::STATE_MAX:
			break;
		default:
			break;
		}
		if (m_nStateCount <= 0)
		{
			m_nStateCount = 0;
			switch (m_state)
			{
			case CAudience::STATE_NONE:
				break;
			case CAudience::STATE_NEUTRAL:
				SetState(STATE_AUTOATTACK, 300);
				break;
			case CAudience::STATE_AUTOATTACK:
				SetState(STATE_NEUTRAL, 60);
				break;
			case CAudience::STATE_MANUALATTACK:
				SetState(STATE_NEUTRAL, 60);
				break;
			case CAudience::STATE_DEATH:
				break;
			case CAudience::STATE_MAX:
				break;
			default:
				break;
			}
		}
	}
}
void CAudience::Swarm()
{
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (pPlayer != NULL)
	{
		
		if (m_nStateCount % 15 == 0)
		{
			CEnemy * pEnemy = NULL;
			int nNum = CEnemy::EnemyList.GetNum();
			if (nNum > 0)
			{
				int nTarget = rand() % nNum;
				pEnemy = CEnemy::EnemyList.Get(nTarget);
			}
			if (pEnemy != NULL)
			{
				float fSpeed = rand() % 500 * 0.1f;
				

				if (pPlayer->GetTarget() != NULL)
				{
					D3DXVECTOR3 Vec = { (rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f };
					D3DXVec3Normalize(&Vec, &Vec);
					CSwarm::Create(GetPos(), Vec * fSpeed, 60 + 60 + m_nStateCount, CBullet::TYPE_PLAYER, 60 + m_nStateCount, pPlayer->GetTarget());
				}
				else
				{
					D3DXVECTOR3 Vec = { (rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f };
					D3DXVec3Normalize(&Vec, &Vec);
					CSwarm::Create(GetPos(), Vec * fSpeed, 60 + 60 + m_nStateCount, CBullet::TYPE_PLAYER, 60 + m_nStateCount, pEnemy);
				}
			}
		}
	}
}
void CAudience::MissileShower()
{
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (pPlayer != NULL)
	{
		if (m_nStateCount % (30 / (pPlayer->GetRank() + 1)) == 0)
		{
			CEnemy * pEnemy = NULL;
			int nNum = CEnemy::EnemyList.GetNum();
			if (nNum > 0)
			{
				int nTarget = rand() % nNum;
				pEnemy = CEnemy::EnemyList.Get(nTarget);
			}
			if (pEnemy != NULL)
			{
				float fSpeed = rand() % 200 * 0.1f;
				float fPower = rand() % 500 * 0.001f;

				if (pPlayer->GetTarget() != NULL)
				{
					D3DXVECTOR3 Vec = { (rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f };
					D3DXVec3Normalize(&Vec, &Vec);
					CMissile::Create(GetPos(), Vec, 60, CBullet::TYPE_PLAYER, fSpeed, fPower, pPlayer->GetTarget());
				}
				else
				{
					D3DXVECTOR3 Vec = { (rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f,(rand() % 1000 - 500) *0.1f };
					D3DXVec3Normalize(&Vec, &Vec);
					CMissile::Create(GetPos(), Vec, 60, CBullet::TYPE_PLAYER, fSpeed, fPower, pEnemy);
				}


			}
		}
	}
}
//====================================
//����
//====================================
CAudience * CAudience::Create(void)
{
	CAudience * pAudience = DBG_NEW CAudience;
	pAudience->Init();
	return pAudience;
}
void CAudience::SetStateAll(STATE state, int nCnt) 
{
	int nSize = List.GetNum(); for (int i = 0; i < nSize; i++)
	{
		if (List.Get(i)->GetState() != state)
		{
			List.Get(i)->SetState(state, nCnt);
		}
	}
}