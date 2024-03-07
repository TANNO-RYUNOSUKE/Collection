//========================================================================================
//
// エネミー
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Enemy.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "meshfield.h"
#include "score.h"
#include "enemymanager.h"
#include "scene.h"
#include "particle.h"
#include "effect.h"
#include "sound.h"
#include "objectX.h"
#include "wave.h"
#include "item.h"
#include "camera.h"
#include "Xmanager.h"
#include "xfile.h"
#define ENEMY_MOVE (0.6f)
#define ENEMY_ACT (2.0f)
//==============================
//コンストラクタ,デストラクタ
//==============================
CHitBox::CHitBox()
{

}
CHitBox::~CHitBox()
{

}
CHitBox * CHitBox::Create(D3DXVECTOR3 max, D3DXVECTOR3 min, D3DXVECTOR3 pos, CHitBox * pNext)
{
	CHitBox * pHitBox;
	pHitBox = DBG_NEW CHitBox;
	pHitBox->m_nShot = 1;
	pHitBox->m_max = max;
	pHitBox->m_min = min;
	pHitBox->m_pos = pos;
	pHitBox->m_pNext = pNext;
	return pHitBox;
}

//=============================================
//コンストラクタ
//=============================================
CEnemy::CEnemy():CObject()
{
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CEnemyManager * pManger = CManager::GetEnemyManager();
	m_pMotion = NULL;
	m_nLife = 0;
	m_nID = -1;
	pManger->Regist(this);
	if (m_nID < 0)
	{
		//CObject::Release();
	}
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		m_apModel[nCnt] = NULL;
	}
	
}
//=============================================
//デストラクタ
//=============================================
CEnemy::~CEnemy()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy::Init()
{
	m_State = STATE_NONE;
	m_nStateCount = 0;
	m_nCoolTime = 0;
	m_bStag = false;

	m_posDest.x = GetPos().x + (float)(rand() % 2000 - 1000);
	m_posDest.z = GetPos().z + (float)(rand() % 2000 - 1000);
	m_posDest.y = GetPos().y + (float)(rand() % 200 - 100);
	m_pMark = DBG_NEW  CJumpmarker;
	m_pLockMark = DBG_NEW  CLockonmarker;
	m_pMark->Init();
	m_pLockMark->Init();
	m_pPointMark = m_pPointMark->Create(55.0f, 55.0f, GetPos(), "data\\TEXTURE\\Enemymark.png");
	

	
	m_pMotion = DBG_NEW  CMotion;
	m_pMotion->SetModel(&m_apModel[0]);
	SetType(CObject::TYPE_ENEMY);

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy::Uninit()
{
	if (pHitBox != NULL)
	{
		delete pHitBox;
		pHitBox = NULL;
	}
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}
	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt]; // ポインタを解放
		m_apModel[nCnt] = NULL;
		}
		
	}
	
}
//=============================================
//更新関数
//=============================================
void CEnemy::Update()
{
	m_nCoolTime--;
	m_pPointMark->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 500.0f, GetPos().z));
	if (m_nCoolTime <= 0)
	{
		m_nCoolTime = 0;
	}
	if (m_apModel[0] != NULL)
	{
		pHitBox->SetPos(GetPos() + m_apModel[0]->GetPos());
	}

	posOld = GetPos();
	
	CCamera * pCamera = CGame::GetCamera();

	CSound * pSound = CManager::GetSound();

	if (m_nLife <= 0 )
	{
		if (m_State != STATE_DEAD)
		{


			D3DXVECTOR3 vec = GetMove();
		
			D3DXVec3Normalize(&vec, &vec);
			vec.y = 0.1f;
			SetMove(vec * 200.0f);
			SetState(STATE_DEAD, 60);
		}
	}
	if (m_apModel[0]!=NULL)
	{


		m_pMark->SetPosdest(m_apModel[0]->GetPos() + GetPos());
		m_pMark->SetDisp(m_bStag);
		m_pLockMark->SetPosdest(m_apModel[0]->GetPos() + GetPos());
		m_pLockMark->SetDisp(m_bLocked);
	}
	if (m_State == STATE_DEAD)
	{
		CParticle::Create(GetPos(),D3DXCOLOR(1.0f,0.6f,0.2f,0.1f), 1, 60, 120, 120, 1);
		m_apModel[0]->SetRot(D3DXVECTOR3(m_apModel[0]->GetRot().x + 0.1f, m_apModel[0]->GetRot().y + 0.4f, m_apModel[0]->GetRot().z+0.1f ));
		
	}
	else
	{
		if (m_pMotion != NULL)
		{
			m_pMotion->Update();

		}

		

		D3DXVECTOR3 turn = m_rotDest - GetRot();
		if (turn.x < -D3DX_PI)
		{
			turn.x += D3DX_PI * 2;
		}
		else if (turn.x > D3DX_PI)
		{
			turn.x += -D3DX_PI * 2;
		}
		if (turn.y < -D3DX_PI)
		{
			turn.y += D3DX_PI * 2; 
		}
		else if (turn.y > D3DX_PI)
		{
			turn.y += -D3DX_PI * 2;
		}
		if (turn.z < -D3DX_PI)
		{
			turn.z += D3DX_PI * 2;
		}
		else if (turn.z > D3DX_PI)
		{
			turn.z += -D3DX_PI * 2;
		}
		SetRot(GetRot() + (turn * 0.2f));
	}
	SetPos(GetPos() + GetMove());
	
	m_nStateCount--;
	if (m_nStateCount <= 0)
	{
		m_nStateCount = 0;
		switch (m_State)
		{
		case CEnemy::STATE_NONE:
			break;
		case CEnemy::STATE_DAMAGE:
			m_State = STATE_NONE;
			break;
		case CEnemy::STATE_DEAD:
				for (int i = 0; i < 3; i++)
				{
					CItem::Create(GetPos(), D3DXVECTOR3((rand() % 200 - 100) * 0.1f, (rand() % 200 - 100) * 0.1f, (rand() % 200 - 100) * 0.1f), 200);

				}
				CGame::GetScore()->Add(2500);
				pCamera->SetShake(30);
				for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
				{
					if (m_apModel[nCnt] != NULL)
					{
						D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[nCnt]->GetMatrix()._41, m_apModel[nCnt]->GetMatrix()._42, m_apModel[nCnt]->GetMatrix()._43);
						CDebri::Create(m_apModel[nCnt]->GetName(), pos, GetRot(), D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10), D3DXVECTOR3((rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f, (rand() % 20 - 10) * 0.01f), 120);
					}

				}
				pSound->Play(CSound::SOUND_LABEL_SE_DESTRUCT);
				pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);
				CParticle::Create(GetPos(), D3DXCOLOR(0.8f, 0.3f, 0.1f, 1.0f), 12, 60, 640.0f, 1000, 1);
				CParticle::Create(GetPos(), D3DXCOLOR(0.8f, 0.3f, 0.1f, 1.0f), 6, 60, 110.0f, 50, 5, 1.01f);
				if (m_pMark != NULL)
				{
					m_pMark->Release();

				}
				if (m_pPointMark != NULL)
				{
					m_pPointMark->Release();
				}


				if (m_pLockMark != NULL)
				{
					m_pLockMark->Release();
				}
				Release();
				return;
			break;
		default:
			m_State = STATE_NONE;
			break;
		}
	}
	CPlayer * pPlayer = NULL;
	pPlayer = CGame::GetPlayer();
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 vecplayer = pPlayer->GetPos() - (pos + GetMove());
		float fDisPlayer = CManager::GetDistance(vecplayer);
		m_fdIstance = fDisPlayer;
	}
	CXManager * pManger = CManager::GetXManager();
	CObjectX ** pObjectX = CManager::GetXManager()->GetX();
	for (int i = 0; i < NUM_OBJECTX; i++)
	{
		if (*(pObjectX + i) != NULL)
		{
			pObjectX[i]->CorrectMovementForBoundingBox(posOld, GetPosAddress(), &GetMove());
		}
	}
	CGame::positionLimiter(GetPosAddress());
	m_bLocked = false;
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	//if (pInputKeyboard->GetPress(DIK_K))
	//{
	//	m_nLife = 0;
	//}
}
void CEnemy::SetLock(bool bLock)
{
	if (m_bLocked == false && bLock == true)
	{
		CSound * pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_SE_LOCKON);
	}
	m_bLocked = bLock;
}
//=============================================
//描画関数
//=============================================
void CEnemy::Draw()
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCnt = 0; nCnt < NUM_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}

}
//=============================================
//生成関数
//=============================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, int nLife)
{
	
	CEnemy * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy;
	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	return pEnemy;
}
void CEnemy::Release(void)
{

	CManager::GetEnemyManager()->Release(m_nID);

	CObject::Release();
	
}

CEnemy_Walker::CEnemy_Walker() :CEnemy()
{

}

CEnemy_Walker::~CEnemy_Walker()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy_Walker::Init()
{
	CEnemy::Init();
	m_pMotion->Load("data\\TEXT\\legtank.txt");
	m_pMotion->SetType(0);
	m_Move = MOVE_NONE;
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_posDest.x =GetPos().x ;
	m_posDest.z =GetPos().z ;
	m_posDest.y = GetPos().y;
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy_Walker::Uninit()
{
	
	CEnemy::Uninit();

}
//=============================================
//更新関数
//=============================================
void CEnemy_Walker::Update()
{

	CPlayer * pPlayer = NULL;
	pPlayer = CGame::GetPlayer();
	if (m_State != STATE_DEAD)
	{
		switch (m_Move)
		{
		case CEnemy_Walker::MOVE_NONE:
			m_Move = MOVE_WALK;
			break;
		case CEnemy_Walker::MOVE_WALK:
			if (pPlayer != NULL)
			{

				D3DXVECTOR3 pos = GetPos();

				D3DXVECTOR3 vecplayer = pPlayer->GetPos() - (pos + GetMove());
				float fDisPlayer = CManager::GetDistance(vecplayer);
				m_fdIstance = fDisPlayer;
				D3DXVec3Normalize(&vecplayer, &vecplayer);

				D3DXVECTOR3 vec = m_posDest - GetPos();
				vec.y = 0.0f;
				float fDis = CManager::GetDistance(vec);
				if (fDisPlayer <= 10000.0f)
				{
					m_Move = MOVE_ATTACK;
				}
				if (CGame::GetWave()->GetPlayLevel() > 3 && fDisPlayer <= 15000.0f)
				{
					m_Move = MOVE_ATTACK;
				}
				if (fDis <= 100.0f)
				{
					m_Move = MOVE_ATTACK;
					m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 1000 - 500);
					m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 1000 - 500);
				}
				D3DXVec3Normalize(&vec, &vec);
				D3DXVECTOR3 move = GetMove();
				move.x = vec.x;
				move.z = vec.z;
				SetMove(GetMove() + move * 0.5f);
			}
			break;
		case CEnemy_Walker::MOVE_ATTACK:
			if (pPlayer != NULL && m_nCoolTime == 0)
			{

				D3DXVECTOR3 pos = GetPos();
				pos.y += 100.0f;
				D3DXVECTOR3 vecplayer;
				if (CGame::GetWave()->GetPlayLevel() > 1)
				{

					vecplayer = CPlayer::LinePrediction(pos, (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 50.0f) - pos;
				}
				else
				{
					vecplayer = (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()) - pos;
				}

				float fDisPlayer = CManager::GetDistance(vecplayer);
				m_fdIstance = fDisPlayer;
				D3DXVec3Normalize(&vecplayer, &vecplayer);

				m_rotDest = D3DXVECTOR3(0.0f, atan2f(-vecplayer.x, -vecplayer.z), 0.0f);
				if (CManager::GetDistance(m_rotDest - GetRot()) < 0.1f)
				{
					if (CGame::GetWave()->GetPlayLevel() > 3)
					{
						CBullet * pBullet = CBullet::Create(pos, vecplayer * 25.0f, 150, CBullet::TYPE_ENEMY, true);
						pBullet->SetPowor(0.1f);
						m_nCoolTime = 90;
					}
					else
					{
						CBullet::Create(pos, vecplayer * 50.0f, 150, CBullet::TYPE_ENEMY, false);
						m_nCoolTime = 30;
					}
					
					
					m_Move = MOVE_WALK;
				}
			}
			else
			{
				m_Move = MOVE_WALK;
			}
			break;
		case CEnemy_Walker::MOVE_MAX:
			break;
		default:
			break;
		}
	}
	

	D3DXVECTOR3 move = GetMove();
	move.x *= 0.92f;//原則係数
	move.z *= 0.92f;//原則係数
	move.y -= GRAVITY;

	if (CGame::GetMeshfield()->Collision(GetPosAddress()) == true)
	{
		move.y = 0.0f;
	}
	SetMove(move);
	CEnemy::Update();
}

//=============================================
//描画関数
//=============================================
void CEnemy_Walker::Draw()
{
	CEnemy::Draw();
}
//=============================================
//生成関数
//=============================================
CEnemy_Walker * CEnemy_Walker::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Walker * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Walker;
	
	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	if (pEnemy->GetID() < 0)
	{
		pEnemy->Release();
		return NULL;
	}
	return pEnemy;
}

CEnemy_Drone::CEnemy_Drone() :CEnemy()
{

}

CEnemy_Drone::~CEnemy_Drone()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy_Drone::Init()
{
	CEnemy::Init();
	delete m_pMotion;
	m_pMotion = NULL;
	m_nCount = 0;
	m_nHeat = 0;
	m_bOverHeat = false;

	m_nMaxHeat = rand() % 1000 + 100;
	m_apModel[0] = m_apModel[0]->Create("data\\MODEL\\Quad.x");
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_fRot = rand() % 628 - 314 * 0.01f;
	m_fLength = rand() % 1000000 * 0.1f + 200.0f;
	m_posDest = {};
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy_Drone::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//更新関数
//=============================================
void CEnemy_Drone::Update()
{
	
	m_nHeat--;
	if (m_nHeat <= 0)
	{
		m_bOverHeat = false;
		m_nHeat = 0;
	}
	CPlayer * pPlayer = NULL;
	pPlayer = CGame::GetPlayer();
	if (m_State != STATE_DEAD)
	{
		if (pPlayer != NULL)
		{
			m_posDest.x = pPlayer->GetPos().x + sinf(m_fRot) * m_fLength;
			m_posDest.z = pPlayer->GetPos().z + cosf(m_fRot) * m_fLength;
			m_posDest.y = pPlayer->GetPos().y + 800.0f;

			D3DXVECTOR3 pos = GetPos();
			pos.y -= 150.0f;
			D3DXVECTOR3 vecplayer;
			if (CGame::GetWave()->GetPlayLevel() > 2)
			{
			
				vecplayer = CPlayer::LinePrediction(pos, (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 100.0f) - pos;
			}
			else
			{
				 vecplayer = (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()) - pos;
			}
			
			m_rotDest = D3DXVECTOR3(0.0f, atan2f(vecplayer.x, vecplayer.z), 0.0f);
			if (CManager::GetDistance(vecplayer) <= 15000.0f && m_bOverHeat == false)
			{
				m_nCount++;
				if (m_nCount % 6 == 0)
				{
				
					D3DXVec3Normalize(&vecplayer, &vecplayer);
					
					CBullet::Create(pos, vecplayer * 100.0f, 120, CBullet::TYPE_ENEMY, false);
					m_nHeat += 50;
				}
			}
			else if (m_nCoolTime <= 0 && CGame::GetWave()->GetPlayLevel() > 3)
			{
				float fSpeed = (rand() % 200 * 0.001f);
				SetMove(GetMove() + (m_posDest - GetPos())* fSpeed);
			
				m_nCoolTime = (int)(fSpeed *2000);
			}
			
			if (m_nHeat > m_nMaxHeat)
			{
				m_bOverHeat = true;
			}
		}
	}
	D3DXVECTOR3 vec = m_posDest - GetPos();
	D3DXVec3Normalize(&vec, &vec);
	SetMove(GetMove() + vec * 1.0f);

	D3DXVECTOR3 move = GetMove();
	move.x *= 0.92f;//原則係数
	move.y *= 0.92f;//原則係数
	move.z *= 0.92f;//原則係数
	

	if (CGame::GetMeshfield()->Collision(GetPosAddress()) == true)
	{
		move.y = 0.0f;
	}
	SetMove(move);
	CEnemy::Update();
}

//=============================================
//描画関数
//=============================================
void CEnemy_Drone::Draw()
{
	CEnemy::Draw();
}
//=============================================
//生成関数
//=============================================
CEnemy_Drone * CEnemy_Drone::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Drone * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Drone;

	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	if (pEnemy->GetID() < 0)
	{
		pEnemy->Release();
		return NULL;
	}
	return pEnemy;
}


CEnemy_Elite::CEnemy_Elite():CEnemy()
{
	m_State = ENEMYE_STATE_NONE;
	m_Act = ACT_NONE;
	m_nActCount = 0;
	m_nCooling = 0;
	m_nActCounter = 0;
}

CEnemy_Elite::~CEnemy_Elite()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy_Elite::Init()
{
	CEnemy::Init();
	m_pMotion->Load("data\\TEXT\\none_head.txt");
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_pOrbit = COrbit::Create(1.0f, 32, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), GetPos());
	m_pOrbit2 = COrbit::Create(1.0f, 32, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), GetPos());
	pHitBox->SetShot(5);
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy_Elite::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//更新関数
//=============================================
void CEnemy_Elite::Update()
{
	CPlayer * pPlayer = NULL;
	pPlayer = CGame::GetPlayer();
	
	
	m_pOrbit->SetOffset(D3DXVECTOR3(m_apModel[5]->GetMatrix()._41, m_apModel[5]->GetMatrix()._42, m_apModel[5]->GetMatrix()._43), D3DXVECTOR3(m_apModel[7]->GetMatrix()._41, m_apModel[7]->GetMatrix()._42, m_apModel[7]->GetMatrix()._43));
	m_pOrbit2->SetOffset(D3DXVECTOR3(m_apModel[6]->GetMatrix()._41, m_apModel[6]->GetMatrix()._42, m_apModel[6]->GetMatrix()._43), D3DXVECTOR3(m_apModel[8]->GetMatrix()._41, m_apModel[8]->GetMatrix()._42, m_apModel[8]->GetMatrix()._43));
	
	if (pPlayer != NULL)
	{

		D3DXVECTOR3 vecplayer = pPlayer->GetPos() - (GetPos() + GetMove());
		float fDisPlayer = CManager::GetDistance(vecplayer);
		D3DXVec3Normalize(&vecplayer, &vecplayer);

		D3DXVECTOR3 vec = m_posDest - GetPos();
		float fDis = CManager::GetDistance(vec);
		if (fDis <= 1000.0f)
		{
			m_State = ENEMYE_STATE_ATTACK;
			m_nActCount = 180;
			m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 10000 - 5000);
			m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 10000 - 5000);
			m_posDest.y = pPlayer->GetPos().y + 200.0f;
		}
		D3DXVec3Normalize(&vec, &vec);

		SetMove(GetMove() + vec * ENEMY_MOVE * 0.5f * CGame::GetWave()->GetPlayLevel());

		if (m_bLocked == true && m_State != ENEMYE_STATE_ACT && m_nCooling <= 0)
		{
			m_State = ENEMYE_STATE_ACT;
			m_nActCount = 120;
			m_nCooling = (m_nActCount + 300);
			m_pMotion->SetType(CEnemy_Elite::ENEMYELITE_MOTION_ACT);
		}
		if (m_State == ENEMYE_STATE_ATTACK && m_nCoolTime == 0)
		{
			CPlayer * pPlayer = CGame::GetPlayer();
			if (pPlayer != NULL)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[9]->GetMtxWorld()._41, m_apModel[9]->GetMtxWorld()._42, m_apModel[9]->GetMtxWorld()._43);
				D3DXVECTOR3 vecplayer = CPlayer::LinePrediction(pos, (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 150.0f) - pos;
				float fDisPlayer = CManager::GetDistance(vecplayer);
				m_fdIstance = fDisPlayer;
				D3DXVec3Normalize(&vecplayer, &vecplayer);
				if (m_nActCount % 12 == 0)
				{
				
					if (CGame::GetWave()->GetPlayLevel() > 1)
					{
						CBullet::Create(D3DXVECTOR3(m_apModel[9]->GetMtxWorld()._41, m_apModel[9]->GetMtxWorld()._42, m_apModel[9]->GetMtxWorld()._43), vecplayer * 150.0f, 120, CBullet::TYPE_ENEMY, true);
					}
					else
					{
						CBullet::Create(D3DXVECTOR3(m_apModel[9]->GetMtxWorld()._41, m_apModel[9]->GetMtxWorld()._42, m_apModel[9]->GetMtxWorld()._43), vecplayer * 100.0f, 120, CBullet::TYPE_ENEMY, false);
					}
				}
				if (m_nActCount % 60 == 0 && CGame::GetWave()->GetPlayLevel() > 2)
				{
					for (int i = 0; i < 10; i++)
					{
						D3DXVECTOR3 rot = vecplayer;
						rot =CBullet::VectorToAngles(rot);
						rot.x += (rand() % 200 - 100) * 0.001f;
						rot.y += (rand() % 200 - 100) * 0.001f;
						rot = CBullet::AnglesToVector(rot);
						D3DXVec3Normalize(&rot, &rot);
						CBullet::Create(pos, rot * 300.0f, 120, CBullet::TYPE_ENEMY, false);
					}
				}
				if (m_nActCount % 6 == 0 && CGame::GetWave()->GetPlayLevel() > 3)
				{
					for (int i = 0; i < 6; i++)
					{
						D3DXVECTOR3 rot = vecplayer;
						rot = CBullet::VectorToAngles(rot);
						rot.x += (rand() % 314 - 157) * 0.01f;
						rot.y += GetRot().y + D3DX_PI*0.5f;
						if (i %2 == 0)
						{
							rot.y *= -1;
						}
						rot = CBullet::AnglesToVector(rot);
						D3DXVec3Normalize(&rot, &rot);
					
						CBullet * pBullet = CBullet::Create(pos, rot * 65.0f, 300, CBullet::TYPE_ENEMY, true);
						pBullet->SetPowor(0.025f);
					}
				}
				if (m_nActCount % 100 == 0 && CGame::GetWave()->GetPlayLevel() > 4)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							D3DXVECTOR3 rot = vecplayer;
							rot = CBullet::VectorToAngles(rot);
							rot.y = (D3DX_PI * 2.0f) * 0.1f * i - D3DX_PI;
							rot.x = (D3DX_PI) * 0.1f * j ;
							rot = CBullet::AnglesToVector(rot);
							D3DXVec3Normalize(&rot, &rot);
							
							CBullet * pBullet = CBullet::Create(pos, rot * 100.0f, 120, CBullet::TYPE_ENEMY, true);
							pBullet->SetPowor(0.05f);
							
						}
					
					}
				}
			}
		}
		else
		{
			
		}
		if (m_State == ENEMYE_STATE_ACT)
		{
			CEffect::Create(GetPos(), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 12, D3DXCOLOR(0.9f, 0.5f, 1.0f, 1.0f), 160.0f);
			
			__readonly int nInterval = 40;
			m_nActCounter++;
			if (m_Act == ACT_NONE || m_nActCounter % nInterval == 0)
			{
				
					m_Act = (ACT)(rand() % ACT_B + 1);
			
			}
			// 移動速度のベクトルを (vx, vy, vz) とする
			float horizontalDistance = sqrtf(GetMove().x * GetMove().x + GetMove().z * GetMove().z);
			float elevation = atan2f(GetMove().y, horizontalDistance); // 仰角（上向きが正、下向きが負）

			m_rotDest = D3DXVECTOR3(elevation,atan2f(-GetMove().x, -GetMove().z), GetRot().z + 1.0f);
			D3DXVECTOR3 move = GetMove();
	
			if (m_Act == ACT_L)
			{
				move.x += sinf(atan2f(vecplayer.x, vecplayer.z) + (D3DX_PI * 0.35f)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();
				move.z += cosf(atan2f(vecplayer.x, vecplayer.z) + (D3DX_PI * 0.35f)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();
				
			}
			else if (m_Act == ACT_R)
			{
				move.x += sinf(atan2f(vecplayer.x,vecplayer.z) - (D3DX_PI * 0.35f)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();
				move.z += cosf(atan2f(vecplayer.x, vecplayer.z) - (D3DX_PI * 0.35f)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();
				
			}
			else if (m_Act == ACT_F)
			{
				move.x += sinf(atan2f(vecplayer.x, vecplayer.z)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();
				move.z += cosf(atan2f(vecplayer.x, vecplayer.z)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();

			}
			else if (m_Act == ACT_B)
			{
				move.x += -sinf(atan2f(vecplayer.x, vecplayer.z) ) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();
				move.z += -cosf(atan2f(vecplayer.x, vecplayer.z)) * ENEMY_ACT* 0.5f * CGame::GetWave()->GetPlayLevel();

			}
			else if (m_Act == ACT_UP)
			{
				move.y += ENEMY_ACT;
			}
			else if (m_Act == ACT_DOWN )
			{
				move.y -= ENEMY_ACT;
			}
		
			SetMove(move);
			
		}
		else
		{
			m_pMotion->SetType(CEnemy_Elite::ENEMYELITE_MOTION_NEUTRAL);
			m_rotDest = D3DXVECTOR3(GetRot().x, GetRot().y, 0.0f);
			m_rotDest = D3DXVECTOR3(0.0f, atan2f(-vecplayer.x, -vecplayer.z), 0.0f);
			m_nActCounter = 0;
		}
		
		
		D3DXVECTOR3 dis = GetPos() - pPlayer->GetPos();;
		m_fdIstance = CManager::GetDistance(dis);
		m_nActCount--;
		m_nCooling--;
		if (m_nActCount <= 0)
		{
			m_nActCount = 0;
		
			if (m_State == ENEMYE_STATE_ATTACK)
			{
				m_nCoolTime = 180;
			}
			m_State = ENEMYE_STATE_NONE;
		
			m_Act = ACT_NONE;
		}
		if (m_nCooling <= 0)
		{
			m_nCooling = 0;
		}
	}
	if (CGame::GetMeshfield()->Collision(GetPosAddress()))
	{
		m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 10000 - 5000);
		m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 10000 - 5000);
		m_posDest.y = pPlayer->GetPos().y + (float)(rand() % 500);
	}
	SetMove(GetMove() * 0.99f);
	if (m_nLife <= 0 && GetState() != STATE_DEAD)
	{

		D3DXVECTOR3 dis = (pPlayer->GetPos()+ pPlayer->GetModelUp()->GetPos()) - GetPos() ;
		dis = CBullet::VectorToAngles(dis);
		CManager::SetHitStop(240);
		
		CGame::GetCamera()->SetRDest(GetPos());
		CGame::GetCamera()->SetRot(dis);
		CGame::GetCamera()->SetLenght(2000.0f + m_fdIstance);
		CGame::GetCamera()->SetDirection(true);
	}
	CGame::positionLimiter(&m_posDest);
	CEnemy::Update();
}
//=============================================
//描画関数
//=============================================
void CEnemy_Elite::Draw()
{
	CEnemy::Draw();
}


//=============================================
//生成関数
//=============================================
CEnemy_Elite * CEnemy_Elite::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Elite * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Elite;
	
	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	if (pEnemy->GetID() < 0)
	{
		pEnemy->Release();
		return NULL;
	}
	return pEnemy;
}

CEnemy_Boss::CEnemy_Boss() :CEnemy()
{

	m_nActCount = 0;
	m_nCooling = 0;
	m_nActCounter = 0;
	for (int i = 0; i < 15; i++)
	{
		m_nBitID[i] = -1;
	}
}

CEnemy_Boss::~CEnemy_Boss()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CEnemy_Boss::Init()
{
	CSound * pSound = CManager::GetSound();
	pSound->Stop();
	pSound->Play(CSound::SOUND_LABEL_BGM002);
	CEnemy::Init();
	m_nActCount = 0;
	m_nAttack = 0;
	m_Mode = MODE_NEUTRAL;
	m_pMotion->Load("data\\TEXT\\none_headRed.txt");
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_pOrbit = COrbit::Create(1.0f, 32, D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.8f), GetPos());
	m_pOrbit2 = COrbit::Create(1.0f, 32, D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.8f), GetPos());
	pHitBox->SetShot(5);
	for (int i = 0; i < 15; i++)
	{
		CEnemy_Bit * pEnemy = CEnemy_Bit::Create(GetPos(), 20);
		m_nBitID[i]= pEnemy->GetID();
	}

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy_Boss::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//更新関数
//=============================================
void CEnemy_Boss::Update()
{
	CPlayer * pPlayer = NULL;
	pPlayer = CGame::GetPlayer();
	bool bBit = false;
	m_nAttack--;
	m_pOrbit->SetOffset(D3DXVECTOR3(m_apModel[5]->GetMatrix()._41, m_apModel[5]->GetMatrix()._42, m_apModel[5]->GetMatrix()._43), D3DXVECTOR3(m_apModel[7]->GetMatrix()._41, m_apModel[7]->GetMatrix()._42, m_apModel[7]->GetMatrix()._43));
	m_pOrbit2->SetOffset(D3DXVECTOR3(m_apModel[6]->GetMatrix()._41, m_apModel[6]->GetMatrix()._42, m_apModel[6]->GetMatrix()._43), D3DXVECTOR3(m_apModel[8]->GetMatrix()._41, m_apModel[8]->GetMatrix()._42, m_apModel[8]->GetMatrix()._43));

	if (m_Mode == MODE_NEUTRAL)
	{
		
		m_nLife = 50 * CGame::GetWave()->GetPlayLevel() + 10.0f;
	}
	if (pPlayer != NULL)
	{

		D3DXVECTOR3 pos = D3DXVECTOR3(m_apModel[9]->GetMtxWorld()._41, m_apModel[9]->GetMtxWorld()._42, m_apModel[9]->GetMtxWorld()._43);
		D3DXVECTOR3 vecplayer = CPlayer::LinePrediction(pos, (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 150.0f) - pos;
		m_rotDest = D3DXVECTOR3(0.0f, atan2f(-vecplayer.x, -vecplayer.z), 0.0f);
		SetRot(m_rotDest);
		D3DXVECTOR3 vec = m_posDest - GetPos();
		float fDis = CManager::GetDistance(vec);
	
		D3DXVec3Normalize(&vec, &vec);
		D3DXVec3Normalize(&vecplayer, &vecplayer);

		SetMove(GetMove() + vec * ENEMY_MOVE * 3.0f);
		if (m_Mode == MODE_NEUTRAL)
		{
			if (fDis <= 1000.0f)
			{

				m_nAttack = 180;
				m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 10000 - 5000);
				m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 10000 - 5000);
				m_posDest.y = pPlayer->GetPos().y + 300.0f;
			}
			int nAct = 0;
		
			for (int i = 0; i < 15; i++)
			{
				CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();
			
				int nNum = 0;
				for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
				{
					if (nNum >= CManager::GetEnemyManager()->GetNum())
					{
						break;
					}
					if (pEnemy[nCnt] != NULL)
					{
						nNum++;
						for (int i = 0; i < 15; i++)
						{
							if (pEnemy[nCnt]->GetID() == m_nBitID[i])
							{
								CEnemy_Bit * pEnemyBit = (CEnemy_Bit*)pEnemy[nCnt];
								if (pEnemyBit != NULL)
								{
									bBit = true;
									if (nAct < 5)
									{

										pEnemyBit->SetMode(CEnemy_Bit::MODE_ACT, 300);
										nAct++;
									}
									else
									{
										if (pEnemyBit->GetMode() != CEnemy_Bit::MODE_ACT)
										{
											pEnemyBit->SetPosDest(GetPos());
										}
									
									}
								}
							}
						}
					}
				}
			
			}

			if (m_nAttack > 0)
			{
				if (m_nAttack % 30 == 0)
				{
					CBullet::Create(D3DXVECTOR3(m_apModel[9]->GetMtxWorld()._41, m_apModel[9]->GetMtxWorld()._42, m_apModel[9]->GetMtxWorld()._43), vecplayer * 70.0f, 300, CBullet::TYPE_ENEMY, true);
				}
			}
		}
		else
		{
			if (m_nActCount % 420 == 0)
			{
			
				SetMove(GetMove() + (m_posDest - GetPos())* 0.1f);
			}
			if (fDis <= 1000.0f)
			{

				m_nAttack = 300;
				m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 10000 - 5000);
				m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 10000 - 5000);
				m_posDest.y = pPlayer->GetPos().y + 300.0f;
			}
			if (m_nAttack > 0)
			{
				if (m_nAttack % 60 == 0)
				{
					CBullet * pBullet = CBullet::Create(D3DXVECTOR3(m_apModel[9]->GetMtxWorld()._41, m_apModel[9]->GetMtxWorld()._42, m_apModel[9]->GetMtxWorld()._43), vecplayer * 25.0f, 600, CBullet::TYPE_ENEMY, true);
					pBullet->SetPowor(0.1f);
				}
				if (m_nAttack % 75 == 0)
				{
				 CEnemy_Bit * pBit = CEnemy_Bit::Create(GetPos(), 600);
				 if (pBit->GetID() % 2 == 0)
				 {
					 pBit->SetMove(vecplayer*50.0f);
				 }
				 else
				 {
					 pBit->SetMove(vecplayer*100.0f);
				 }
				
					pBit->Boom();
				}
			}
			m_nActCount++;
		}
		if (CGame::GetMeshfield()->Collision(GetPosAddress()))
		{
			m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 10000 - 5000);
			m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 10000 - 5000);
			m_posDest.y = pPlayer->GetPos().y + (float)(rand() % 500);
		}
		CXManager * pManger = CManager::GetXManager();
		CObjectX ** pObjectX = CManager::GetXManager()->GetX();
		for (int i = 0; i < NUM_OBJECTX; i++)
		{
			if (*(pObjectX + i) != NULL)
			{
				if (pObjectX[i]->CorrectMovementForBoundingBox(posOld, GetPosAddress(), &GetMove()))
				{
					m_posDest.x = pPlayer->GetPos().x + (float)(rand() % 10000 - 5000);
					m_posDest.z = pPlayer->GetPos().z + (float)(rand() % 10000 - 5000);
					m_posDest.y = pPlayer->GetPos().y + (float)(rand() % 500);
					break;
				}
			}
		}
	}
	if (!bBit &&m_Mode != MODE_ACT)
	{
		CParticle::Create(GetPos(), D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f),1,120, 60, 120, 60);
		m_Mode = MODE_ACT;
	}

	
	SetMove(GetMove() * 0.95f);
	if (m_nLife <= 0 && GetState() != STATE_DEAD)
	{

		CEnemyManager * pManger = CManager::GetEnemyManager();
     CEnemy ** pEnemy=		pManger->GetEnemy();
	 for (int i = 0; i < NUM_ENEMY; i++)
	 {
		 if (pEnemy[i] != NULL)
		 {
			 pEnemy[i]->SetLife(0);
		 }
		
	 }
		D3DXVECTOR3 dis = (pPlayer->GetPos() + pPlayer->GetModelUp()->GetPos()) - GetPos();
		dis = CBullet::VectorToAngles(dis);
		CManager::SetHitStop(300);

		CGame::GetCamera()->SetRDest(GetPos());
		CGame::GetCamera()->SetRot(dis);
		CGame::GetCamera()->SetLenght(2000.0f + m_fdIstance);
		CGame::GetCamera()->SetDirection(true);
	}
	CGame::positionLimiter(&m_posDest);
	CEnemy::Update();
}
//=============================================
//描画関数
//=============================================
void CEnemy_Boss::Draw()
{
	CEnemy::Draw();
}


CEnemy_Bit::CEnemy_Bit() :CEnemy()
{
	m_bBom = false;
}

CEnemy_Bit::~CEnemy_Bit()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CEnemy_Bit::Init()
{
	
	CEnemy::Init();
	m_mode = MODE_NEUTRAL;
	m_nModeCount = 0;
	delete m_pMotion;
	m_pMotion = NULL;
	m_nCount = 0;
	m_nHeat = 0;
	m_bOverHeat = false;
	m_pOrbit = COrbit::Create(1.0f, 64, D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.8f), GetPos());
	m_nMaxHeat = rand() % 1000 + 100;
	m_apModel[0] = m_apModel[0]->Create("data\\MODEL\\droneRed.x");
	pHitBox = CHitBox::Create(m_apModel[0]->GetMax(), m_apModel[0]->GetMin(), m_apModel[0]->GetPos() + GetPos());
	m_fRot = rand() % 628 - 314 * 0.01f;
	m_fLength = rand() % 1000 * 0.1f + 1000.0f;
	m_posDest = {};
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CEnemy_Bit::Uninit()
{

	CEnemy::Uninit();

}
//=============================================
//更新関数
//=============================================
void CEnemy_Bit::Update()
{
	m_pOrbit->SetOffset(D3DXVECTOR3(GetPos().x, GetPos().y+10.0f, GetPos().z), D3DXVECTOR3(GetPos().x, GetPos().y + -10.0f, GetPos().z));
	m_nCoolTime--;
	if (m_nCoolTime < 0)
	{
		m_nCoolTime = 0;
	}
	if (m_nModeCount <= 0)
	{
		m_nModeCount = 0;
		m_mode = MODE_NEUTRAL;
	}
	if (m_nHeat <= 0)
	{
		m_bOverHeat = false;
		m_nHeat = 0;
	}
	if (GetState() != CEnemy::STATE_DEAD)
	{

		if (!m_bBom)
		{
			m_nHeat--;
			m_nModeCount--;
			CPlayer * pPlayer = NULL;
			pPlayer = CGame::GetPlayer();
			if (m_State != STATE_DEAD)
			{
				if (pPlayer != NULL)
				{
					if (m_mode == MODE_NEUTRAL)
					{
						m_posDest.x = m_posDest.x + sinf(m_fRot) * m_fLength;
						m_posDest.z = m_posDest.z + cosf(m_fRot) * m_fLength;
						m_posDest.y = m_posDest.y;
						SetPos(GetPos() + (m_posDest - GetPos()) / 3);

						m_apModel[0]->SetRot(GetRot());
						if (GetID() % 2 == 0)
						{
							m_fRot += 0.025f;
							SetRot(D3DXVECTOR3(GetRot().x + 0.01f, GetRot().y + 0.01f, GetRot().z + 0.01f));
						}
						else
						{
							SetRot(D3DXVECTOR3(GetRot().x - 0.01f, GetRot().y - 0.01f, GetRot().z - 0.01f));
							m_fRot -= 0.025f;
						}

					}
					else
					{
						m_nCount++;
						if (m_nCount % 180 == 0)
						{
							m_posDest.x = pPlayer->GetPos().x + sinf(m_fRot) * m_fLength;
							m_posDest.z = pPlayer->GetPos().z + cosf(m_fRot) * m_fLength;
							m_posDest.y = pPlayer->GetPos().y + 300.0f;
						}
						D3DXVECTOR3 vecplayer = CPlayer::LinePrediction(GetPos(), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 150.0f) - GetPos();
						D3DXVECTOR3 vec = m_posDest - GetPos();
						if (m_nCount % 6 == 0)
						{

							D3DXVec3Normalize(&vecplayer, &vecplayer);

							CBullet::Create(GetPos(), vecplayer * 100.0f, 120, CBullet::TYPE_ENEMY, false);
							m_nHeat += 50;
						}
					
					}
				}
			}
			D3DXVECTOR3 vec = m_posDest - GetPos();
			D3DXVec3Normalize(&vec, &vec);
			SetMove(GetMove() + vec * 20.0f);

			D3DXVECTOR3 move = GetMove();
			move.x *= 0.92f;//原則係数
			move.y *= 0.92f;//原則係数
			move.z *= 0.92f;//原則係数


			if (CGame::GetMeshfield()->Collision(GetPosAddress()) == true)
			{
				move.y = 0.0f;
			}
			SetMove(move);
		}
		else
		{
			m_nHeat++;
			if (m_nHeat % 3 == 0)
			{
				D3DXVECTOR3 vec = {};
				vec.x = (rand() % 200 - 100) * 0.01f;
				vec.y = (rand() % 200 - 100) * 0.01f;
				vec.z = (rand() % 200 - 100) * 0.01f;
				D3DXVec3Normalize(&vec, &vec);
				if (GetID() % 2 == 0)
				{
					CBullet * pBullet = CBullet::Create(GetPos(), vec * 50.0f, 120, CBullet::TYPE_ENEMY, true);
				}
				else
				{
					CPlayer * pPlayer = NULL;
					pPlayer = CGame::GetPlayer();
					if (pPlayer != NULL)
					{
						D3DXVECTOR3 vecplayer = CPlayer::LinePrediction(GetPos(), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPos()), (pPlayer->GetModelUp()->GetPos() + pPlayer->GetPosOld()), 150.0f) - GetPos();
					
						D3DXVec3Normalize(&vecplayer, &vecplayer);
						CBullet * pBullet = CBullet::Create(GetPos(), vecplayer * 100.0f, 120, CBullet::TYPE_ENEMY, false);
					}

				}

			}
			m_nLife--;
			if (CGame::GetMeshfield()->Collision(GetPosAddress()) == true)
			{
				m_nLife = 0;
			}
			if (m_nLife <= 0)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						D3DXVECTOR3 rot = {};
						rot = CBullet::VectorToAngles(rot);
						rot.y = (D3DX_PI * 2.0f) * 0.2f * i - D3DX_PI;
						rot.x = (D3DX_PI * 2.0f) * 0.2f * j;
						rot = CBullet::AnglesToVector(rot);
						D3DXVec3Normalize(&rot, &rot);
						if (GetID() % 2 == 0)
						{
							CBullet * pBullet = CBullet::Create(GetPos(), rot * 100.0f, 120, CBullet::TYPE_ENEMY, true);
						}
						else
						{

							CBullet * pBullet = CBullet::Create(GetPos(), rot * 100.0f, 120, CBullet::TYPE_ENEMY, false);
						}

					}

				}
			}
		
			SetMove(GetMove());
		}
	}

	CEnemy::Update();
}

//=============================================
//描画関数
//=============================================
void CEnemy_Bit::Draw()
{
	CEnemy::Draw();
}
//=============================================
//生成関数
//=============================================
CEnemy_Bit * CEnemy_Bit::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Bit * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Bit;

	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	if (pEnemy->GetID() < 0)
	{
		pEnemy->Release();
		return NULL;
	}
	return pEnemy;
}

//=============================================
//生成関数
//=============================================
CEnemy_Boss * CEnemy_Boss::Create(D3DXVECTOR3 pos, int nLife)
{

	CEnemy_Boss * pEnemy = NULL;
	pEnemy = DBG_NEW  CEnemy_Boss;

	pEnemy->SetPos(pos);
	pEnemy->m_nLife = nLife;
	pEnemy->Init();
	if (pEnemy->GetID() < 0)
	{
		pEnemy->Release();
		return NULL;
	}
	return pEnemy;
}