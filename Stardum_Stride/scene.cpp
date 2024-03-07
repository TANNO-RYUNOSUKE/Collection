//========================================================================================
//
// シーン
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "scene.h"

#include "camera.h"
#include "light.h"
#include "animbillboard.h"

#include "player.h"
#include "input.h"

#include "sound.h"
#include "debugproc.h"	
#include "fade.h"
#include "meshfield.h"
#include "collision.h"
#include "list.h"
#include "objectX.h"
#include "texture.h"
#include "audience.h"
#include "effect.h"
#include "lifegage.h"
#include "effekseerControl.h"
CFade * CScene::m_pFade = NULL;
int m_nScore;
//=============================================
//コンストラクタ
//=============================================
CScene::CScene()
{
	m_Mode = MODE_NONE;
	m_nFrame = 0;
}
//=============================================
//デストラクタ
//=============================================
CScene::~CScene()
{
}
//=============================================
//生成関数
//=============================================
CScene * CScene::Create(MODE mode)
{
	CScene * pScene = NULL;
	switch (mode)
	{
	case CScene::MODE_TITLE:
		pScene = DBG_NEW CTitle;
		break;
	case CScene::MODE_TUTORIAL:
		pScene = DBG_NEW CTutorial;
		break;
	case CScene::MODE_GAME:
		pScene = DBG_NEW CGame;
		break;
	case CScene::MODE_RESULT:
		pScene = DBG_NEW CResult;
		break;
	default:
		break;
	}

	pScene->SetMode(mode);
	pScene->Init();

	return pScene;
}
//=================================================================================================
//タイトル
//=================================================================================================
//=============================================
//コンストラクタ
//=============================================
CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}


//=============================================
//初期化関数
//=============================================
HRESULT CTitle::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pLight = DBG_NEW CLight;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	};
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	};
	CObjectX::Create("data\\MODEL\\city2.x", D3DXVECTOR3(0.0f, -50.0f, 0.0f), VECTO3ZERO, 0);
	CMeshfield::Create(1000.0f, 1000.0f, 70, 70);
	CObjectX* pSky;
	pSky = CObjectX::Create("data\\MODEL\\sky.x", VECTO3ZERO, VECTO3ZERO, 0);
	pSky->SetLight(false);
	pSky->m_bShadow = false;
	m_pCamera->SetPosR(D3DXVECTOR3(1050.0f, 150.0f, -2950.0f));
	m_pCamera->SetPosV(D3DXVECTOR3(1000.0f, 10.0f, -3000.0f));
	CEffekseer::GetInstance()->Create("data\\Effekseer\\atmosphere.efkefc", D3DXVECTOR3(950.0f, 150.0f, -3500.0f), VECTO3ZERO, VECTO3ZERO, 100.0f);
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT/2, 0.0f),SCREEN_HEIGHT,SCREEN_WIDTH,0, "data\\TEXTURE\\TITLE\\ss.png");
	
	CSound * pSound = CManager::GetInstance()->GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_SANCTUARY);
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CTitle::Uninit()
{

}
//=============================================
//更新関数
//=============================================
void CTitle::Update()
{
	
	//m_pCamera->Update();
	m_pLight->Update();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		m_pFade->FadeOut(MODE::MODE_GAME);
	}
}
//=============================================
//描画関数
//=============================================
void CTitle::Draw()
{
	
}
//=================================================================================================
//チュートリアル
//=================================================================================================
//=============================================
//コンストラクタ
//=============================================
CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}


//=============================================
//初期化関数
//=============================================
HRESULT CTutorial::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();

	CSound * pSound = CManager::GetInstance()->GetSound();

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CTutorial::Uninit()
{

}
//=============================================
//更新関数
//=============================================
void CTutorial::Update()
{
	
	
	
}
//=============================================
//描画関数
//=============================================
void CTutorial::Draw()
{

}
//=================================================================================================
//ゲーム
//=================================================================================================



CGame::CGame()
{
}

CGame::~CGame()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CGame::Init()
{
	b_Pause = false;
	m_nCnt = 0;
	m_nScore = 0;
	m_nEnemy = 0;
	m_pFade = DBG_NEW CFade;
	m_pPause = DBG_NEW CPause;
	m_pPause->Init();
	m_pFade->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pLight = DBG_NEW CLight;
	m_pMeshfield = CMeshfield::Create(1000.0f, 1000.0f, 70, 70);
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\howto.png");
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, -5000.0f));

	m_nEnemyCount = 0;
	CTexture * pTex = CManager::GetInstance()->GetTexture();
	//初期化設定;
	
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	};
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	};
	m_pCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, -5000.0f));
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 0.0f, -5000.0f));
	pSky = CObjectX::Create("data\\MODEL\\sky.x", VECTO3ZERO, VECTO3ZERO,0);
	pSky->SetLight(false);
	pSky->m_bShadow = false;
	CObjectX::Create("data\\MODEL\\city2.x", D3DXVECTOR3(0.0f,-50.0f,0.0f), VECTO3ZERO, 0);
	pTex->Regist("data\\TEXTURE\\spelhit.png");
	pTex->Regist("data\\TEXTURE\\HitEffect.png");
	pTex->Regist("data\\TEXTURE\\HitEffect2.png");
	pTex->Regist("data\\TEXTURE\\beams_00000.jpg");
	m_nWaveCount = 0;
	
	CEffekseer::GetInstance()->Create("data\\Effekseer\\atmosphere.efkefc", VECTO3ZERO, VECTO3ZERO, VECTO3ZERO, 100.0f);
	CSound * pSound = CManager::GetInstance()->GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_CITY);

	CObject2D::Create(D3DXVECTOR3(250.0f, 60.0f, 0.0f), 59.0f, 413.0f, 6, "data\\TEXTURE\\life.png");

	return S_OK;
	
}
//=============================================
//終了関数
//=============================================
void CGame::Uninit()
{

	if (m_pCamera != NULL)
	{
		//メモリ解放
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		//メモリ解放
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	if (m_pPause != NULL)
	{
		//メモリ解放
		m_pPause->Uninit();
	
		m_pPause = NULL;
	}

	CSphereCollision::List.GetList()->clear();
}
//=============================================
//更新関数
//=============================================
void CGame::Update()
{
	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();
	m_pPause->Update();
	m_pPlayer->GetPos().z;
	if (m_nWaveCount <= 3)
	{
		if (m_pPlayer->GetPos().z > -5000.0f + (m_nWaveCount + 1) * 1500.0f)
		{
			m_nWaveCount++;
			if (m_nWaveCount > 3)
			{
				CSound * pSound = CManager::GetInstance()->GetSound();
				CEnemy_Boss::Create(D3DXVECTOR3(0.0f, 1000.0f, 1500.0f + m_pPlayer->GetPos().z), 1000);
				pSound->Stop();
				pSound->Play(CSound::SOUND_LABEL_BGM_BOSS);
			}
			else
			{
				for (int i = 0; i < m_nWaveCount + 1; i++)
				{
					D3DXVECTOR3 pos = D3DXVECTOR3((rand() % 10000 - 5000) * 0.1f, 0.0f, (rand() % 5000) * 0.1f) + m_pPlayer->GetPos();
					CAnimBillboard::Create(200.0f, 200.0f, 6, 6, 36, 24, false, pos, "data\\TEXTURE\\spelhit.png");
					CEnemy_army::Create(pos, 100);
				}

				for (int i = 0; i < m_nWaveCount - 1; i++)
				{
					D3DXVECTOR3 pos = D3DXVECTOR3((rand() % 10000 - 5000) * 0.1f, 300.0f, (rand() % 5000) * 0.1f) + m_pPlayer->GetPos();
					CAnimBillboard::Create(200.0f, 200.0f, 6, 6, 36, 24, false, pos, "data\\TEXTURE\\spelhit.png");
					CEnemy_Drone::Create(pos, 100);
				}
			}

		}
	}
	if (!CManager::GetInstance()->GetPause())
	{
		D3DXVECTOR3 rot = pSky->GetRot();
		rot.y += 0.0001f;
		pSky->SetRot(rot);
	}

	m_pCamera->Update();
	m_pLight->Update();
	//m_pMap_Editer->Update();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		if (CManager::GetInstance()->GetPause())
		{
			CManager::GetInstance()->SetPause(false);
		}
		else
		{
			CManager::GetInstance()->SetPause(true);
		}
	}
	if (!CManager::GetInstance()->GetPause())
	{
		if (!CSphereCollision::List.GetList()->empty())
		{
			std::list<CSphereCollision *>::iterator Itr = CSphereCollision::List.GetList()->begin();
			for (; Itr != CSphereCollision::List.GetList()->end(); Itr++)
			{
				CSphereCollision * Col = *Itr;
				if (Col != NULL)
				{
					Col->Collision();
				}
			}
		}
	
	}
	CSound * pSound = CManager::GetInstance()->GetSound();
	if (m_nWaveCount <= 3)
	{
		if (CEnemy::EnemyList.GetNum() == 0 && m_nEnemy != 0)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_BATTLE);
			pSound->Play(CSound::SOUND_LABEL_BGM_CITY);
		}
		else if (CEnemy::EnemyList.GetNum() != 0 && m_nEnemy == 0)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_CITY);
			pSound->Play(CSound::SOUND_LABEL_BGM_BATTLE);
		}
	}
	
	m_nEnemy = CEnemy::EnemyList.GetNum();
	if (m_nWaveCount > 3 && CEnemy::EnemyList.GetNum() == 0)
	{
		m_pFade->FadeOut(MODE::MODE_RESULT);
	}
	if (m_pPlayer->GetLife() <= 0)
	{
		m_pFade->FadeOut(MODE::MODE_RESULT);
	}
	
}
//=============================================
//描画関数
//=============================================
void CGame::Draw()
{
	m_pPause->Draw();
}
void CGame::ScoreUp(int nScore)
{
	m_nScore += nScore * (m_pPlayer->GetRank() + 1);
}
//=============================================
//座標制限
//=============================================
void CGame::positionLimiter(D3DXVECTOR3* pos)
{
	if (pos->x > MAX_X)
	{
		pos->x = MAX_X;
	}
	else if (pos->x < -MAX_X)
	{
		pos->x = -MAX_X;
	}

	if (pos->y > MAX_Y)
	{
		pos->y = MAX_Y;
	}
	

	if (pos->z > MAX_Z)
	{
		pos->z = MAX_Z;
	}
	else if (pos->z < -MAX_Z)
	{
		pos->z = -MAX_Z;
	}
}
//=================================================================================================
//result
//=================================================================================================
//=============================================
//コンストラクタ
//=============================================
CResult::CResult()
{
}

CResult::~CResult()
{
}
//=============================================
//初期化関数
//=============================================
HRESULT CResult::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\Ranking.png");
	m_pRank = CObject2D::Create(D3DXVECTOR3(1050.0f, SCREEN_HEIGHT / 2, 0.0f), 500.0f, 500.0f, 6, "data\\TEXTURE\\rank.png");
	int nRank = m_nScore / 30;
	if (nRank > 7)
	{
		nRank = 7;
	}
	m_pRank->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pRank->SetTexMin(D3DXVECTOR2(1.0f - (1.0f / 8.0f) * (nRank + 1), 0.0f));
	m_pRank->SetTexMax(D3DXVECTOR2(1.0f - (1.0f / 8.0f) * (nRank), 1.0f));
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CResult::Uninit()
{
	
}
//=============================================
//更新関数
//=============================================
void CResult::Update()
{
	if (m_pFade->GetState() == CFade::STATE_NONE)
	{
		m_pRank->SetHeight(m_pRank->GetHeight() + (230.0f - m_pRank->GetHeight()) * 0.1f);
		m_pRank->SetWidth(m_pRank->GetWidth() + (230.0f - m_pRank->GetWidth()) * 0.1f);
		m_pRank->SetCol(m_pRank->GetCol() + (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) - m_pRank->GetCol()) * 0.1f);
	}
	
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0) || pInputGamepad->GetTrigger(CInputGamePad::Button_A, 0))
	{
		m_pFade->FadeOut(MODE::MODE_TITLE);
	}
}
//=============================================
//描画関数
//=============================================
void CResult::Draw()
{
	
}
