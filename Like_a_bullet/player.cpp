//========================================================================================
//
// �v���C���[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "debugproc.h"
#include "camera.h"
#include "particle.h"
#include "enemy.h"
#include "meshfield.h"
#include "camera.h"
#include "effect.h"
#include <stdio.h>
#include "enemymanager.h"
#include "scene.h"
#include "sound.h"
#include "objectX.h"
#include "Xmanager.h"
#include "drone.h"
#include "item.h"
#include "itemmanager.h"
#include "lifegage.h"
#include "wave.h"
#include "score.h"

//�}�N����`
#define MOVE_PLAYER (2.5f)
#define DASH_PLAYER (6.0f)
#define JAMP_PLAYER (50.0f)
//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CObject(nPriority)
{
 	m_bLand = false;
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{		
			m_apModelUp[nCnt] = NULL;
	
	}
	m_pMotionLow = NULL;
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		m_apModelLow[nCnt] = NULL;

	}
	SetType(CObject::TYPE_PLAYER);
	m_bLockon = false;
	m_nLife = 0;
	//m_pLockOnEnemy = NULL;
	m_nCntLockEnemy = 0;
	m_nLock = 0;
	m_nLockCount= 0;
	m_pOrbit = NULL;
	m_pEnemyJump = NULL;
	m_pFilterDamage = NULL;
	Scorebonus = 0;
}
//=============================================
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CPlayer::Init()
{
	m_nFilter = 0;
	Scorebonus = 0;
	m_pFilterDamage = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\RedFilter.png");
	m_pFilterDamage->SetDisp(false);
	//�_�b�V���J�E���g������
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_anDash[nCnt] = 0;
	}
	m_nLife = 10;
	m_nCntLockEnemy = 0;
	
	m_pMotionLow = DBG_NEW CMotion;
	m_pMotionLow->SetModel(&m_apModelLow[0]);

	m_pMotionLow->Load("data\\TEXT\\motion_player_lowerHalf.txt");

	m_pMotionUp = DBG_NEW CMotion;
	m_pMotionUp->SetModel(&m_apModelUp[0]);

	m_pMotionUp->Load("data\\TEXT\\motion_player_upperHalf.txt");
	m_apModelUp[0];
	
	//for (int nCnt = 0; nCnt < MAX_LOCK; nCnt++)
	//{
	//	m_pLockmark[nCnt] = DBG_NEW CLockonmarker;
	//	m_pLockmark[nCnt]->Init();
	//}

	m_pOrbit = COrbit::Create(1.0f, 8, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), GetPos());
	m_pOrbitJump = COrbit::Create(1.0f, 180, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), GetPos());
	CDrone::Create(GetPos(), GetRot());
	CGage::Create(D3DXVECTOR3(SCREEN_WIDTH /10, 650.0f,0.0f),200.0f,m_nLife);
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CPlayer::Uninit()
{
	
	
	if (m_pMotionUp != NULL)
	{
		//m_pMotionUp->Uninit();
		delete m_pMotionUp;
		m_pMotionUp = NULL;
	}
	if (m_pMotionLow != NULL)
	{
	//	m_pMotionLow->Uninit();
		delete m_pMotionLow;
		m_pMotionLow = NULL;
	}
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModelUp[nCnt] != NULL)
		{
			m_apModelUp[nCnt]->Uninit();
			delete (m_apModelUp[nCnt]);
			m_apModelUp[nCnt] = NULL;
		}
		if (m_apModelLow[nCnt] != NULL)
		{
			m_apModelLow[nCnt]->Uninit();
			delete (m_apModelLow[nCnt]);
			m_apModelLow[nCnt] = NULL;
		}
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CPlayer::Update()
{
	m_nFilter--;
	if (m_nFilter <= 0)
	{
		m_nFilter = 0;
		m_pFilterDamage->SetDisp(false);
	}
	else
	{
		m_pFilterDamage->SetDisp(true);
	}
	CSound * pSound = CManager::GetSound();
	CInputGamePad * pInputGamePad = CManager::GetInputGamePad();
	//���[�V�����X�V
	m_pMotionUp->Update();
	m_pMotionLow->Update();

	bool bMove = false;

	


	CCamera * pCamera = CGame::GetCamera();
	CDebugProc * pDeb = CManager::GetDeb();
	CMeshfield * pMeshfield = CGame::GetMeshfield();

	//�����_�̍��W�ݒ�
	D3DXVECTOR3 seepos = GetPos();
	seepos.y += 200.0f;
	if (!CManager::GetPause())
	{
		pCamera->SetRDest(seepos);
	}

	pDeb->Print("WASD:�ړ�\n");
	pDeb->Print("�v���C���[�̍��W(X:%f,Y:%f,Z:%f)\n", GetPos().x, GetPos().y, GetPos().z);
	pDeb->Print("�v���C���[�̈ړ��l(X:%f,Y:%f,Z:%f)\n", GetMove().x, GetMove().y, GetMove().z);
	//���_���W�̐ݒ�

	if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK1 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK2 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK3)
	{
		if ((GetMove().x >= 1.0f || GetMove().x <= -1.0f) || (GetMove().z >= 1.0f || GetMove().z <= -1.0f))
		{
			if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_WALK)
			{
				m_pMotionLow->SetType(CPlayer::LOWERMOTION_WALK);
			}
			
		}
	}
	
	SetPosOld(GetPos());//posold�̍X�V
	Move();
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputMouse * pMouse = CManager::GetInputMouse();
	
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 camrot = pCamera->GetRot();
	

	//�ˌ�========================================================
	if (pMouse->GetPress(CInputMouse::MOUSE::MOUSE_RIGTH) || pInputGamePad->GetPress(CInputGamePad::Button_RB,0))
	{
		LockOn();
		if (pMouse->GetPress(CInputMouse::MOUSE::MOUSE_LEFT) || pInputGamePad->GetPress(CInputGamePad::Button_LB, 0))
		{
			if (m_pMotionUp->GetType() != CPlayer::UPPERMOTION_SHOT && m_pEnemyJump == NULL)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_MISSILE);
				m_pMotionUp->SetType(CPlayer::UPPERMOTION_SHOT);
				D3DXVECTOR3 GunPos = D3DXVECTOR3(m_apModelUp[8]->GetMtxWorld()._41, m_apModelUp[8]->GetMtxWorld()._42, m_apModelUp[8]->GetMtxWorld()._43);
				CParticle::Create(GunPos, D3DXCOLOR(1.0f, 0.6f, 0.3f, 1.0f), 5, 5, 32.0f, 60, 1);
				for (int nCnt = 0; nCnt < MAX_LOCK; nCnt++)
				{
					if (m_pEnemy[nCnt] != NULL)
					{
						D3DXVECTOR3 shotvec = (*m_pEnemy[nCnt])->GetPos() - GunPos;
						D3DXVec3Normalize(&shotvec, &shotvec);
						int Shot = (*m_pEnemy[nCnt])->GetHitBox()->GetShot();
						for (int nShot = 0; nShot < Shot; nShot++)
						{
							CBullet::Create(GunPos, shotvec * 80.0f, 120,CBullet::TYPE_PLAYER,true,m_pEnemy[nCnt]);
						}
					
					}
				}

			}
		}
	}
	else
	{
		for (int nCNt = 0; nCNt < MAX_LOCK; nCNt++)
		{//���b�N�I�����̏�����
			m_pEnemy[nCNt] = NULL;
			m_nLockCount = 0;
		}
	}
	
	if (pMouse->GetPress(CInputMouse::MOUSE::MOUSE_LEFT) || pInputGamePad->GetTrigger(CInputGamePad::Button_LB, 0))
	{
		float fDis = 10000.0f;
		float fDisCheck = 0.0f;
		CCamera * pCamera = CGame::GetCamera();
		CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();
		CEnemy * pEnemyMelle = NULL;
		for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
		{
			if (pEnemy[nCnt] != NULL)
			{
				fDisCheck = pEnemy[nCnt]->GetDis();
			
				if (fDisCheck < fDis)
				{
					float fAngle = CheckEnemyAngle(-pCamera->GetVec(), ((pEnemy[nCnt])->GetPos() - pCamera->GetPosV()));
					if (fAngle < 35.0f && fAngle > -35.0f)
					{
						pEnemyMelle = pEnemy[nCnt];
						fDis = fDisCheck;
					}
				}
			}
		}
		if (pEnemyMelle != NULL)
		{
			D3DXVECTOR3 move = pEnemyMelle->GetPos() - GetPos();
			D3DXVec3Normalize(&move, &move);
			//SetRot(D3DXVECTOR3(GetRot().x, atan2f(move.z, move.x), GetRot().z));
		}
		if (m_pMotionUp->GetType() != CPlayer::UPPERMOTION_SHOT && m_pMotionUp->GetType() != CPlayer::UPPERMOTION_ATTACK1 && m_pMotionUp->GetType() != CPlayer::UPPERMOTION_ATTACK2&& m_pMotionUp->GetType() != CPlayer::UPPERMOTION_ATTACK3)
		{
			if (pEnemyMelle == NULL)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				move.x -= sinf(camrot.y) * 150.0f;
				move.z -= cosf(camrot.y) * 150.0f;
				SetMove(GetMove() + move);
			}
			else
			{
				D3DXVECTOR3 move = pEnemyMelle->GetPos() - GetPos();
			
				
				SetMove(GetMove() + move * 0.05f);
				SetPos(pEnemyMelle->GetPos());
			}

			pSound->Play(CSound::SOUND_LABEL_SE_SLASHSWING);
			m_pMotionUp->SetType(CPlayer::UPPERMOTION_ATTACK1);
			m_pMotionLow->SetType(CPlayer::LOWERMOTION_ATTACK1);
		}
	
		
	}

	for (int nCnt = 0; nCnt < MAX_LOCK; nCnt++)
	{
		if (m_pEnemy[nCnt] != NULL)
		{
			/*D3DXVECTOR3 vec = GetPos() - m_pLockOnEnemy->GetPos();
			SetRot(D3DXVECTOR3(GetRot().x, atan2f(vec.x, vec.z), GetRot().z));*/
		/*	m_pLockmark[nCnt]->SetPosdest((*m_pEnemy[nCnt])->GetPos());
			m_pLockmark[nCnt]->SetDisp(true);*/
			(*m_pEnemy[nCnt])->SetLock(true);
		
		}
		else
		{
			/*m_pLockmark[nCnt]->SetDisp(false);*/
		}
	}

	
	
	if (m_pMotionUp->GetType() == 2 && m_pMotionUp->GetKey() == 1)
	{
		
	
	}
	

	BulletJump();
	D3DXMATRIX  mtxTrans, mtxRot, mtx; //�v�Z�p�}�g���N�X
	D3DXVECTOR3 pos1, pos2,S;


	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&mtx);


	pos1 = D3DXVECTOR3(m_apModelUp[9]->GetMtxWorld()._41, m_apModelUp[9]->GetMtxWorld()._42, m_apModelUp[9]->GetMtxWorld()._43); pos2 = pos1;

	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_apModelUp[9]->GetRot().y, m_apModelUp[9]->GetRot().x, m_apModelUp[9]->GetRot().z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -240.0f);

	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	D3DXMatrixMultiply(&mtx, &mtx, &m_apModelUp[9]->GetMtxWorld());
	m_pOrbit->SetOffset(pos1 + GetMove(), D3DXVECTOR3(mtx._41, mtx._42, mtx._43) + GetMove());
	if (m_pMotionUp->GetType() != CPlayer::UPPERMOTION_ATTACK1 && m_pMotionUp->GetType() != CPlayer::UPPERMOTION_ATTACK2&& m_pMotionUp->GetType() != CPlayer::UPPERMOTION_ATTACK3)
	{
		m_apModelUp[0]->SetRot(D3DXVECTOR3(m_apModelUp[0]->GetRot().x, camrot.y - GetRot().y, m_apModelUp[0]->GetRot().z));
		m_pOrbit->SetDisp(false);
	}
	else
	{
		m_pOrbit->SetDisp(true);
		Melee(D3DXVECTOR3(mtx._41, mtx._42, mtx._43));
	}


	m_bLand = pMeshfield->Collision(GetPosAddress());
	if (m_bLand == true)
	{
		m_nBoost = 180;
		SetMove(D3DXVECTOR3(GetMove().x, -50.0f, GetMove().z));
	
	}
	else
	{ 
		if (m_pEnemyJump == NULL)
		{
			if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_JUMP &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK1 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK2 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK3)
			{
				m_pMotionLow->SetType(CPlayer::LOWERMOTION_JUMP);
				m_pMotionLow->SetkeyNumber(1);
			}
		}
	}
	pCamera->SetLenght(300.0f + CManager::GetDistance(GetMove())*10.0f);



	if (m_nLife <= 0)
	{
		for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
		{
			if (m_apModelUp[nCnt] != NULL)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(m_apModelUp[nCnt]->GetMatrix()._41, m_apModelUp[nCnt]->GetMatrix()._42, m_apModelUp[nCnt]->GetMatrix()._43);
				CDebri::Create(m_apModelUp[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
			}
			if (m_apModelLow[nCnt] != NULL)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(m_apModelLow[nCnt]->GetMatrix()._41, m_apModelLow[nCnt]->GetMatrix()._42, m_apModelLow[nCnt]->GetMatrix()._43);
				CDebri::Create(m_apModelLow[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
			}
		}
		CGame::SetPlayer(NULL);
		
		Release();
	}
	
}
//=============================================
//�`��֐�
//=============================================
void CPlayer::Draw()
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y + 117.0f , pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		
		if (m_apModelLow[nCnt] != NULL)
		{
			m_apModelLow[nCnt]->Draw();
		}
	}
	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModelUp[nCnt] != NULL)
		{
			m_apModelUp[nCnt]->Draw();
		}
	}
}
//=============================================
//�����֐�
//=============================================
CPlayer * CPlayer::Create(void)
{
	CPlayer * pPlayer = NULL;
	pPlayer = DBG_NEW CPlayer;
	pPlayer->Init();

	return pPlayer;
}
void CPlayer::Move()
{
	
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_anDash[nCnt]++;
	}
	if (m_bLand == true && m_pMotionLow->GetType() != CPlayer::LOWERMOTION_NEUTRAL && m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK1 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK2 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK3)
	{
		D3DXVECTOR3 pos1, pos2;
		pos1 = D3DXVECTOR3(m_apModelLow[3]->GetMatrix()._41, m_apModelLow[3]->GetMatrix()._42, m_apModelLow[3]->GetMatrix()._43);
		pos2 = D3DXVECTOR3(m_apModelLow[6]->GetMatrix()._41, m_apModelLow[6]->GetMatrix()._42, m_apModelLow[6]->GetMatrix()._43);
		if (pos1.y < GetPos().y + 30.0f)
		{
			CParticle::Create(pos1, D3DXCOLOR(0.2f, 0.2f, 0.15f, 1.0f), 1, 30, 12, 6, 1, 1.1f);
		}
		if (pos2.y < GetPos().y + 30.0f)
		{
			CParticle::Create(pos2, D3DXCOLOR(0.2f, 0.2f, 0.15f, 1.0f), 1, 30, 12, 6, 1, 1.1f);
		}
		
	}
	SetPosOld(GetPos());//posold�̍X�V
	CCamera * pCamera = CGame::GetCamera();
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamePad = CManager::GetInputGamePad();

	CInputMouse * pMouse = CManager::GetInputMouse();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 camrot = pCamera->GetRot();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();
	float fSpeed = MOVE_PLAYER;
	bool bMove = false;
	float fHeight = GetHeight();
	float fWidth = GetWidth();
	

	if (pInputGamePad->GetPedalL(0))
	{
		m_bDash = true;
	}
	if ((m_bDash == true &&(pInputKeyboard->GetPress(DIK_W) || pInputKeyboard->GetPress(DIK_A) || pInputKeyboard->GetPress(DIK_S) || pInputKeyboard->GetPress(DIK_D)))|| pInputGamePad->GetPedalL(0))
	{
		fSpeed = DASH_PLAYER;
		
	}
	else
	{
		m_bDash = false;
	}
	//�_�b�V��
	if (pInputGamePad->GetStickL(0, 0.1f).x != 0.0f || pInputGamePad->GetStickL(0, 0.1f).y != 0.0f)
	{
		D3DXVECTOR3 Stick = pInputGamePad->GetStickL(0, 0.1f);
		float fAngle = atan2f(Stick.x, -Stick.y);


		if (Stick != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			move.x -= sinf(camrot.y + fAngle)*fSpeed;
			move.z -= cosf(camrot.y + fAngle)*fSpeed;
		}
		bMove = true;
	}
	if (pInputKeyboard->GetTrigger(DIK_W))
	{
		if (m_anDash[0] <= 30)
		{
			m_bDash = true;
			fSpeed = DASH_PLAYER*2.0f;
		}
		m_anDash[0] = 0;
	}
	if (pInputKeyboard->GetTrigger(DIK_S))
	{
		if (m_anDash[1] <= 30)
		{
			m_bDash = true;
			fSpeed = DASH_PLAYER*2.0f;
		}
		m_anDash[1] = 0;
	}
	if (pInputKeyboard->GetTrigger(DIK_A))
	{
		if (m_anDash[2] <= 30)
		{
			m_bDash = true;
			fSpeed = DASH_PLAYER*2.0f;
		}
		m_anDash[2] = 0;
	}
	if (pInputKeyboard->GetTrigger(DIK_D))
	{
		if (m_anDash[3] <= 30)
		{
			m_bDash = true;
			fSpeed = DASH_PLAYER*2.0f;
		}
		m_anDash[3] = 0;
	}
	//�ړ�
	if (pInputKeyboard->GetPress(DIK_W))
	{
		move.x -= sinf(camrot.y) * fSpeed;
		move.z -= cosf(camrot.y) * fSpeed;
		bMove = true;
	}
	if (pInputKeyboard->GetPress(DIK_S))
	{
		move.x += sinf(camrot.y) * fSpeed;
		move.z += cosf(camrot.y) * fSpeed;
		bMove = true;
	}
	if (pInputKeyboard->GetPress(DIK_A))
	{
		move.x += sinf(camrot.y + (D3DX_PI / 2)) * fSpeed;
		move.z += cosf(camrot.y + (D3DX_PI / 2)) * fSpeed;
		bMove = true;
	}
	if (pInputKeyboard->GetPress(DIK_D))
	{
		move.x -= sinf(camrot.y + (D3DX_PI / 2)) * fSpeed;
		move.z -= cosf(camrot.y + (D3DX_PI / 2)) * fSpeed;
		bMove = true;
	}

	//���s���[�V�����ݒ�
	if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK1 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK2 &&m_pMotionLow->GetType() != CPlayer::LOWERMOTION_ATTACK3)
	{
		if ((GetMove().x >= 1.0f || GetMove().x <= -1.0f) || (GetMove().z >= 1.0f || GetMove().z <= -1.0f))
		{
			if (bMove == true)
			{
				if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_WALK)
				{
					m_pMotionLow->SetType(CPlayer::LOWERMOTION_WALK);
				}
			}
			else
			{
				if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_STOP)
				{
					m_pMotionLow->SetType(CPlayer::LOWERMOTION_STOP);
				}
			}
		}
		else
		{
			if (m_pMotionLow->GetType() != CPlayer::LOWERMOTION_NEUTRAL)
			{
				m_pMotionLow->SetType(CPlayer::LOWERMOTION_NEUTRAL);
			}
			if (m_pMotionUp->GetType() != CPlayer::UPPERMOTION_SHOT)
			{
				if (m_pMotionUp->GetType() != CPlayer::UPPERMOTION_WALK)
				{
					m_pMotionUp->SetType(CPlayer::UPPERMOTION_NEUTRAL);
				}
			}
		}
	}
	//�W�����v
	if ((pInputKeyboard->GetTrigger(DIK_SPACE) || pInputGamePad->GetTrigger(CInputGamePad::Button_A, 0)) && m_bLand == true)
	{
		move.y = JAMP_PLAYER;

	}
	if ((pInputKeyboard->GetPress(DIK_SPACE)|| pInputGamePad->GetPress(CInputGamePad::Button_A, 0)) && m_bLand == false && GetMove().y <= 0.0f && m_nBoost > 0)
	{
		CSound * pSound = CManager::GetSound();
		pSound->Stop(CSound::SOUND_LABEL_SE_HIGHSPEED);
		CEffect::Create(GetPos(), D3DXVECTOR3((float)(rand() % 10 - 5), -15.0f, (float)(rand() % 10 - 5)), 30, D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 40.0f,1.01f);
		move.y -= move.y * 0.1f;
		m_nBoost--;
	}
	rot.y = atan2f(-move.x, -move.z);
	move.y -= GRAVITY;//�d�͂�^����
	move.x *= 0.92f;//�����W��
	move.z *= 0.92f;//�����W��
	SetPos(pos + move);
	SetRot(rot);
	SetMove(move);
	
	CXManager * pManger = CManager::GetXManager();
	CObjectX ** pObjectX = CManager::GetXManager()->GetX();
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			if (pObjectX[i]->CorrectMovementForBoundingBox(GetPosOld(), GetPosAddress(), GetMoveAddress()))
			{
				m_pEnemyJump = NULL;
				break;
			}
		}
	}
	CGame::positionLimiter(GetPosAddress());

    CItemManager * pItemmanager =	CManager::GetItemManager();
	CItem ** pItem = pItemmanager->GetItem();

	for (int i = 0; i < NUM_Item; i++)
	{
		if (pItem[i] != NULL)
		{
			pItem[i]->Collision(GetPos());
		}
	}
	

	/*CXManager * pManger = CManager::GetXManager();
	CObjectX ** pObjectX = CManager::GetXManager()->GetX();
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			if (pObjectX[i]->Ray(GetPosOld(), GetPos(),GetPosAddress()))
			{
				
				break;
			}
		}
	}*/
}
//=============================================
//���b�N�I���֐�
//=============================================
void CPlayer::LockOn()
{
	CInputMouse * pMouse = CManager::GetInputMouse();
	CCamera * pCamera = CGame::GetCamera();
	CMeshfield * pMesh = CGame::GetMeshfield();
	for (int nCNt = 0; nCNt < MAX_LOCK; nCNt++)
	{//���b�N�I�����̏�����
		m_pEnemy[nCNt] = NULL;
	}
	int nCntLock = 0;
	m_nLockCount++;


	CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();


	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (*(pEnemy + nCnt) != NULL)
		{


			if (pEnemy[nCnt]->GetDis() <= MAX_LANGE)
			{
				float fAngle = CheckEnemyAngle(-pCamera->GetVec(), ((pEnemy[nCnt])->GetPos() - pCamera->GetPosV()));
				if (fAngle < 20.0f && fAngle > -20.0f)
				{
					if (true != pMesh->MeshRay(pCamera->GetPosV(), (pEnemy[nCnt])->GetPos() + (pEnemy[nCnt])->GetModel()->GetPos()))
					{
						bool bRay = false;
						CXManager * pManger = CManager::GetXManager();
						CObjectX ** pObjectX = CManager::GetXManager()->GetX();
						for (int i = 0; i < NUM_OBJECTX; i++)
						{
							if (*(pObjectX + i) != NULL)
							{
								if (pObjectX[i]->Ray(pCamera->GetPosV(), (pEnemy[nCnt])->GetPos() + (pEnemy[nCnt])->GetModel()->GetPos()))
								{
									bRay = true;
									break;
								}
							}
						}
						if (bRay == false)
						{
							m_pEnemy[nCntLock] = &pEnemy[nCnt];

							nCntLock++;
						}
					}
				}
			}
		}

		if (nCntLock >= MAX_LOCK - 1 || m_nLockCount / 6 < nCntLock)
		{
			break;
		}
	}


	

	if (nCntLock == 0)
	{
		m_nLockCount = 0;
	}
	/*if (nCntLock == 0)
	{
		m_pLockOnEnemy = NULL;
		return;
	}
	if (m_pLockOnEnemy == NULL)
	{
		m_nCntLockEnemy = 0;
		m_pLockOnEnemy = m_pEnemy[0];
	}
	if (pMouse->GetMove().z >= 5.0f)
	{
		m_nCntLockEnemy += 1;
		if (m_nCntLockEnemy >= nCntLock)
		{
			m_nCntLockEnemy = 0;
		}
		
		m_pLockOnEnemy = m_pEnemy[m_nCntLockEnemy];
	}
	if (pMouse->GetMove().z <= -5.0f)
	{
		m_nCntLockEnemy -= 1;
		if (m_nCntLockEnemy < 0)
		{
			m_nCntLockEnemy = nCntLock - 1;
		}
		m_pLockOnEnemy = m_pEnemy[m_nCntLockEnemy];
	}*/
	
}
void CPlayer::Melee(D3DXVECTOR3 pos)
{
	if (m_pEnemyJump == NULL)
	{
		CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();

		CCamera * pCamera = CGame::GetCamera();
		CSound * pSound = CManager::GetSound();
		CEnemy * pEnemyTag = NULL;
		D3DXVECTOR3 dis = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
		{

			if (*(pEnemy + nCnt) != NULL)
			{
				D3DXVECTOR3 vec = pos - D3DXVECTOR3(pEnemy[nCnt]->GetModel()->GetMatrix()._41, pEnemy[nCnt]->GetModel()->GetMatrix()._42, pEnemy[nCnt]->GetModel()->GetMatrix()._43);

				if (CManager::GetDistance(vec) <= CManager::GetDistance(dis))
				{
					float fAngle = CheckEnemyAngle(-pCamera->GetVec(), ((pEnemy[nCnt])->GetPos() - pCamera->GetPosV()));
					if (fAngle < 30.0f && fAngle > -30.0f)
					{
						pEnemyTag = *(pEnemy + nCnt);
					}
				}
			}
		}
		if (pEnemyTag != NULL)
		{
			D3DXVECTOR3 vecmoove = pEnemyTag->GetPos() - GetPos();

			D3DXVec3Normalize(&vecmoove, &vecmoove);
			SetMove(GetMove() + vecmoove);
		}

		for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
		{
			if (*(pEnemy + nCnt) != NULL)
			{
				if (pEnemy[nCnt]->GetState() == CEnemy::STATE_NONE)
				{
					
					D3DXVECTOR3 vec = pos - D3DXVECTOR3(pEnemy[nCnt]->GetModel()->GetMatrix()._41, pEnemy[nCnt]->GetModel()->GetMatrix()._42, pEnemy[nCnt]->GetModel()->GetMatrix()._43);

					if (CManager::GetDistance(vec) <= 500.0f)
					{
						CSound * pSound = CManager::GetSound();
						pSound->Stop(CSound::SOUND_LABEL_SE_DESTRUCT);
						pCamera->SetShake(20);
						vec = GetPos() - D3DXVECTOR3(pEnemy[nCnt]->GetModel()->GetMatrix()._41, pEnemy[nCnt]->GetModel()->GetMatrix()._42, pEnemy[nCnt]->GetModel()->GetMatrix()._43);
						pSound->Play(CSound::SOUND_LABEL_SE_SLASHHIT);
						CParticle::Create(pos, D3DXCOLOR(1.0f, 0.2f, 0.5f, 1.0f), 1, 30, 40.0f, 120, 32, 1.005f);
						vec.y = 0.0f;
						D3DXVec3Normalize(&vec, &vec);
						pEnemy[nCnt]->SetMove(-vec * 150.0f);
						pEnemy[nCnt]->AddLife(-3);

						CManager::SetHitStop(30);
						pEnemy[nCnt]->SetState(CEnemy::STATE_DAMAGE, 12);
					}
				}
			}
		}
	}
}
D3DXVECTOR3 CPlayer::LinePrediction(D3DXVECTOR3 shotPosition, D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetPrePosition, float bulletSpeed)
{

	//�ڕW��1�t���[���̈ړ����x
	D3DXVECTOR3 v3_Mv = targetPosition - targetPrePosition;
	//�ˌ�����ʒu���猩���ڕW�ʒu
	D3DXVECTOR3 v3_Pos = targetPosition - shotPosition;

	//�s�^�S���X�̒藝����Q�̃x�N�g���̒������������ꍇ�̎������
	//�񎟕������̉��̌������g���Ēe��������\�����Ԃ��v�Z����
	float A = (v3_Mv.x * v3_Mv.x + v3_Mv.y * v3_Mv.y + v3_Mv.z * v3_Mv.z) - bulletSpeed * bulletSpeed;
	float B = 2 * (v3_Pos.x * v3_Mv.x + v3_Pos.y * v3_Mv.y + v3_Pos.z * v3_Mv.z);
	float C = (v3_Pos.x * v3_Pos.x + v3_Pos.y * v3_Pos.y + v3_Pos.z * v3_Pos.z);

	//0����֎~����
	if (A == 0)
	{
		if (B == 0)
		{
			return targetPosition;
		}
		else
		{
			return targetPosition + v3_Mv * (-C / B);
		}
	}

	//�e�������鎞�Ԃ̃t���[�����v�Z����
	float flame1, flame2;
	//�񎟕������̉��̌����̔��ʎ��ŕ���
	float D = B * B - 4 * A * C;
	if (D > 0)
	{
		float E = sqrtf(D);
		flame1 = (-B - E) / (2 * A);
		flame2 = (-B + E) / (2 * A);
		//����2�Ȃ̂Ő��̐��̍ŏ��l���g��
		flame1 = PlusMin(flame1, flame2);
	}
	else
	{
		//������
		//������Ȃ��̂ō��̈ʒu��_��
		flame1 = 0;
	}

	//�\�z�ʒu��Ԃ�
	return targetPosition + v3_Mv * flame1;
}
//�v���X�̍ŏ��l��Ԃ�(�����}�C�i�X�Ȃ�0)
float CPlayer::PlusMin(float a, float b)
{
	if (a < 0 && b < 0) return 0;
	if (a < 0) return b;
	if (b < 0) return a;
	return a < b ? a : b;
}
float CPlayer::CheckEnemyAngle(const D3DXVECTOR3& cameraDirection, const D3DXVECTOR3& enemyDirection)
{
	// �x�N�g���̐��K��
	D3DXVECTOR3 normalizedCameraDir, normalizedEnemyDir;
	D3DXVec3Normalize(&normalizedCameraDir, &cameraDirection);
	D3DXVec3Normalize(&normalizedEnemyDir, &enemyDirection);
	// �x�N�g���̓��ς��v�Z
	float dotProduct = D3DXVec3Dot(&normalizedCameraDir, &normalizedEnemyDir);
	// ���W�A������x���@�ɕϊ����ĕԂ�
	return acosf(dotProduct) * (180.0f / D3DX_PI);
}


void CPlayer::BulletJump(void)
{
	CInputGamePad * pInputGamePad = CManager::GetInputGamePad();
	CSound * pSound = CManager::GetSound();
	float fDis = FLT_MAX;
	float fDisCheck = 0.0f;
	CCamera * pCamera = CGame::GetCamera();
	CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();

	CInputMouse * pMouse = CManager::GetInputMouse();
	if (pMouse->GetPress(CInputMouse::MOUSE::MOUSE_CENTER) || pInputGamePad->GetTrigger(CInputGamePad::Button_X, 0) && m_pEnemyJump == NULL)
	{

		for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
		{
			if (pEnemy[nCnt] != NULL)
			{
				if (pEnemy[nCnt]->GetState() != CEnemy::STATE_DEAD)
				{
					if (pEnemy[nCnt]->GetStag() == true)
					{

						fDisCheck = pEnemy[nCnt]->GetDis();
						if (fDisCheck <= 30000.0f)
						{
							float fAngle = CheckEnemyAngle(-pCamera->GetVec(), ((pEnemy[nCnt])->GetPos() - pCamera->GetPosV()));
							if (fAngle < 20.0f && fAngle > -20.0f)
							{
								pSound->Play(CSound::SOUND_LABEL_SE_HIGHSPEED);
								if (fDisCheck < fDis)
								{
									m_pEnemyJump = &pEnemy[nCnt];
									fDis = fDisCheck;
								}
							}
						}
					}
				}
			}
		}
	}
	if (m_pEnemyJump != NULL)
	{
 		m_pMotionUp->SetType(CPlayer::UPPERMOTION_ATTACK1);
		m_pMotionLow->SetType(CPlayer::LOWERMOTION_ATTACK1);
		m_pOrbitJump->SetOffset(GetPos() + GetMove(), D3DXVECTOR3(GetPos().x, GetPos().y + 150.0f, GetPos().z) + GetMove());
		m_pOrbitJump->SetDisp(true);
		if (*m_pEnemyJump != NULL)
		{
			pCamera->SetVDest((*m_pEnemyJump)->GetPos());
			D3DXVECTOR3 vec = (*m_pEnemyJump)->GetPos() - GetPos();
			D3DXVec3Normalize(&vec, &vec);
			D3DXVECTOR3 move = vec * (100.0f + CManager::GetDistance((*m_pEnemyJump)->GetPos()-GetPos()) * 0.025f);
			if (CManager::GetDistance(move) >= 500.0f)
			{
				D3DXVec3Normalize(&move, &move);
				move *= 500.0f;
			}
			SetMove(move);
		
			SetPos(GetPos() + GetMove());
			if ((*m_pEnemyJump)->GetDis() <= 500.0f)
			{
				/*for (int i = 0; i < NUM_MODEL; i++)
				{
					if (m_apModelUp[i] != NULL)
					{
						CAfterImage::Create(m_apModelUp[i]->GetName(), D3DXVECTOR3(m_apModelUp[i]->GetMtxWorld()._41, m_apModelUp[i]->GetMtxWorld()._42, m_apModelUp[i]->GetMtxWorld()._43), m_apModelUp[i]->GetRot(), D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f), 120);
					}
					if (m_apModelLow[i] != NULL)
					{
						CAfterImage::Create(m_apModelLow[i]->GetName(), D3DXVECTOR3(m_apModelLow[i]->GetMtxWorld()._41, m_apModelLow[i]->GetMtxWorld()._42, m_apModelLow[i]->GetMtxWorld()._43), m_apModelLow[i]->GetRot(), D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f), 120);
					}
				}*/
				Scorebonus += 500;
				CGame::GetScore()->Add(Scorebonus);
				SetMove(GetMove() * -2.0f);
				pSound->Play(CSound::SOUND_LABEL_SE_SLASH);
				m_nBoost = 180;
				CManager::SetHitStop(10);
				CParticle::Create((*m_pEnemyJump)->GetPos(), D3DXCOLOR(1.0f, 0.3f, 0.1f, 1.0f), 15, 60, 480.0f, 600, 2);
				(*m_pEnemyJump)->AddLife(-5);
				(*m_pEnemyJump)->SetStag(false);
				//*m_pEnemyJump = NULL;
		
				m_pEnemyJump = nullptr;
			
				fDis = 15001.0f;
				for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
				{
					if (pEnemy[nCnt] != NULL)
					{
						if (pEnemy[nCnt]->GetStag() == true)
						{
							fDisCheck = pEnemy[nCnt]->GetDis();
							if (fDisCheck <= 15000.0f)
							{		
									if (fDisCheck < fDis)
									{
										m_pEnemyJump = &pEnemy[nCnt];
										fDis = fDisCheck;
									}
							}
						}
					}
				}
			}
		}
		else
		{
			//m_pOrbitJump->SetDisp(false);
			m_pEnemyJump = NULL;
			Scorebonus = 0;
		}
	}
}