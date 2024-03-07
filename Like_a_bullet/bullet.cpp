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
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "player.h"
#include "meshfield.h"
#include "objectX.h"
#include "Xmanager.h"
#include "scene.h"
#include "wave.h"

LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CBullet::CBullet(int nPriority):CBillboard(nPriority)
{
	m_nLife = 0;
	m_fHomingPowor = 0.05f;
	m_bHoming = false;
	m_nMoveCount = 0;
	m_nHomingCount = 0;
	m_Type = TYPE_NONE;
	m_pTarget = NULL;
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
	switch (m_Type)
	{

	case CBullet::TYPE_PLAYER:
		pOrbit = COrbit::Create(10.0f, 64, D3DXCOLOR(5.0f, 0.01f, 0.01f, 1.0f), GetPos());
		break;
	case CBullet::TYPE_ENEMY:
		if (m_bHoming)
		{
			pOrbit = COrbit::Create(15.0f, 64, D3DXCOLOR(0.0f, 0.6f, 1.0f, 1.0f), GetPos());
		}
		else
		{	
			pOrbit = COrbit::Create(20.0f, 16, D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f), GetPos());			
		}
	
		break;

	default:
		break;
	}

	D3DXVECTOR3 pos1, pos2;
	pos1 = GetPos(); pos2 = GetPos();
	pos1.y += 10.0f;
	pos2.y -= 10.0f;
	pOrbit->SetOffset(pos1, pos2);
	pOrbit->SetDisp(false);
	pOrbit->Update();
	pOrbit->SetDisp(true);
	CBillboard::Init();
	SetType(CObject::TYPE_BULLET);
	m_nMoveCount = 0;
	m_nHomingCount = 0;
	CTexture * pTex = CManager::GetTexture();
	m_pIdxTex = DBG_NEW  int;
	*m_pIdxTex = pTex->Regist("data\\TEXTURE\\Bullet000.png");
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CBullet::Uninit()
{
	if (m_pIdxTex != NULL)
	{
		delete m_pIdxTex;
		m_pIdxTex = NULL;
	}
	CBillboard::Uninit();
	
}
//=============================================
//�X�V�֐�
//=============================================
void CBullet::Update()
{
    CMeshfield * pMesh =	CGame::GetMeshfield();
	D3DXVECTOR3 vec;
	D3DXVECTOR3 pos1, pos2;
	pos1 = GetPos(); pos2 = GetPos();
	CCamera * pCamera = CGame::GetCamera();
	switch (m_Type)
	{
	case CBullet::TYPE_NONE:
		break;
	case CBullet::TYPE_PLAYER:
		m_posOld = GetPos();
	
		pos1.y += 10.0f;
		pos2.y -= 10.0f;
		pOrbit->SetOffset(pos1, pos2);
		LinerHoming();
		
		VERTEX_3D * pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//���_���W�̐ݒ�

		m_pVtxBuff->Unlock();
	
		CollisionEnemy(GetPos());
		
		break;
	case CBullet::TYPE_ENEMY:
		pos1.y += 10.0f;
		pos2.y -= 10.0f;
		pOrbit->SetOffset(pos1, pos2);
		
		if (m_bHoming == true)
		{
			Homing(m_fHomingPowor);
		}
		CollisionPlayer(GetPos());
		if (pMesh->Collision(GetPosAddress()))
		{
			m_nLife = 0;
		}
	
		break;
	case CBullet::TYPE_MAX:
		break;
	default:
		break;
	}

	SetPos(GetPos() + GetMove());
	m_nLife--;
	bool bRay = false;
	CXManager * pManger = CManager::GetXManager();
	CObjectX ** pObjectX = CManager::GetXManager()->GetX();
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			if (pObjectX[i]->Ray(GetPosOld(), GetPos()))
			{

				m_nLife = 0;
				break;
			}
		}
	}
	if (m_nLife <= 0)
	{
		pOrbit->end();
		CSound * pSound = CManager::GetSound();
	/*	pSound->Stop(CSound::SOUND_LABEL_SE_EXPLOSION);
		pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);*/
		CParticle::Create(CBullet::GetPos(), D3DXCOLOR(0.3f, 0.6f, 1.0f, 1.0f), 1, 15, 80.0f, 30, 5,1.01f);
		CParticle::Create(CBullet::GetPos(), D3DXCOLOR(0.3f, 0.6f, 1.0f, 1.0f), 1, 15, 480.0f, 300, 1);
		if (pCamera->GetShake() < 3)
		{
			pCamera->SetShake(3);
		}
	
		
		
		CObject::Release();
	}
	
}
//=============================================
//�`��֐�
//=============================================
void CBullet::Draw()
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	
	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//a�u�����f�B���O��ʏ�ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================
//�����֐�
//=============================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE type, bool bHoming, CEnemy ** pTag)
{
	CBullet * pBullet = NULL;
	pBullet = DBG_NEW  CBullet;
	
	pBullet->SetPos(pos);
	pBullet->m_posOld = pos;;
	pBullet->SetWidth(25.0f);
	pBullet->SetHeight(25.0f);
	pBullet->SetMove(move);
	pBullet->m_fSpeed = CManager::GetDistance(move);
	pBullet->m_Type = type;
	pBullet->m_nLife = nLife;
	pBullet->m_pTarget = pTag;
	pBullet->m_bHoming = bHoming;
	pBullet->Init();
	return pBullet;
}
//=============================================
//�z�[�~���O�֐�
//=============================================
void CBullet::LinerHoming(void)
{
	if (*m_pTarget != NULL)
	{
		const int Hominginterval = 20;
		const int nMoveMax = 4;
		
		const int nDistur = 5000;//�c��
		D3DXVECTOR3 vec = (*m_pTarget)->GetPos() - GetPos();
		float fDis = CManager::GetDistance(vec);
		if (m_nHomingCount % Hominginterval == 0)
		{
			if (fDis > 1000.0f && m_nMoveCount < nMoveMax)
			{
				m_nMoveCount++;
				vec.x += float(rand() % nDistur - (nDistur/2));
				vec.y += float(rand() % (nDistur/2));
				vec.z += float(rand() % nDistur - (nDistur/2));
				D3DXVec3Normalize(&vec, &vec);
				SetMove(vec * (100.0f + fDis * 0.01f));
			}
			
		}
		if (fDis <= 1000.0f || m_nMoveCount >= nMoveMax)
		{
			D3DXVec3Normalize(&vec, &vec);
			D3DXVECTOR3 move = GetMove();
			SetMove(vec * (100.0f + fDis * 0.01f));
		}
		m_nHomingCount++;
	}
}
void CBullet::Homing(float fPower)
{
	CPlayer * pPlayer = CGame::GetPlayer();
	if (pPlayer != NULL)
	{
		float fSpeed = CManager::GetDistance(GetMove());
		D3DXVECTOR3 Move = GetMove();
		D3DXVec3Normalize(&Move, &Move);
	

		D3DXVECTOR3 vec = (pPlayer->GetModelUp()->GetPos()+ pPlayer->GetPos()) - GetPos();
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
		Move += fRotDiff * fPower;
		Move = AnglesToVector(Move);
		Move *= m_fSpeed;
	
		SetMove(Move);
	}
}
//=============================================
//�R���W����
//=============================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{

	if (*m_pTarget != NULL)
	{
		CModel * pModel = (*m_pTarget)->GetModel();
		CHitBox * pHitBox = (*m_pTarget)->GetHitBox();
		do
		{
			D3DXVECTOR3 max = pHitBox->GetMax() + (*m_pTarget)->GetPos();
			D3DXVECTOR3 min = pHitBox->GetMin() + (*m_pTarget)->GetPos();

			if (pos.x <= max.x + 10.0f && pos.y <= max.y + 10.0f && pos.z <= max.z + 10.0f)
			{
				if (pos.x >= min.x - 10.0f && pos.y >= min.y - 10.0f && pos.z >= min.z - 10.0f)
				{
					m_nLife = 0;
					(*m_pTarget)->AddLife(-1);
					(*m_pTarget)->SetStag(true);
					return true;
				}
			}
			pHitBox = pHitBox->GetNext();
		} while (pHitBox != NULL);
		
	}
	return false;
}
bool CBullet::CollisionPlayer(D3DXVECTOR3 pos)
{
	CPlayer * pPlayer = CGame::GetPlayer();
	if (pPlayer != NULL)
	{
		if (pPlayer->GetJump() == NULL)
		{
			CModel * pModel = pPlayer->GetModelUp();


			D3DXVECTOR3 max = pModel->GetMax() + pPlayer->GetPos();
			D3DXVECTOR3 min = pModel->GetMin() + pPlayer->GetPos();

			if (pos.x <= max.x && pos.y <= max.y && pos.z <= max.z)
			{
				if (pos.x >= min.x && pos.y >= min.y && pos.z >= min.z)
				{
					CGame::GetWave()->Damagecheck(true);
					m_nLife = 0;
					pPlayer->AddLife(-1);
					pPlayer->SetFilterDisp(6);
					CCamera * pCamera = CGame::GetCamera();
					pCamera->SetShake(30);

					return true;
				}
			}
		}
	}
	return false;
}

// �x�N�g�����p�x�ɕϊ�����֐�
D3DXVECTOR3 CBullet::VectorToAngles(const D3DXVECTOR3& vector)
{
	D3DXVECTOR3 angles;

	// Yaw�i���[�j���v�Z
	angles.y = atan2(vector.x, vector.z);

	// Pitch�i�s�b�`�j���v�Z
	angles.x = atan2(vector.y, sqrt(vector.x * vector.x + vector.z * vector.z));

	// Roll�i���[���j��0�x�ɐݒ�
	angles.z = 0.0f;



	return angles;
}

// �p�x���x�N�g���ɕϊ�����֐�
D3DXVECTOR3 CBullet::AnglesToVector(const D3DXVECTOR3& angles)
{
	D3DXVECTOR3 vector;

	// ���W�A����x�ɕϊ�
	float yaw = (angles.y);
	float pitch = (angles.x);

	// �x�N�g�����v�Z
	vector.x = sin(yaw) * cos(pitch);
	vector.y = sin(pitch);
	vector.z = cos(yaw) * cos(pitch);

	return vector;
}