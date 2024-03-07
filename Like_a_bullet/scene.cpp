//========================================================================================
//
// �V�[��
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "scene.h"
#include "enemymanager.h"
#include "enemy.h"
#include "fog.h"
#include "camera.h"
#include "light.h"
#include "number.h"
#include "score.h"
#include "meshfield.h"
#include "sky.h"
#include "reticle.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "debugproc.h"	
#include "wave.h"
#include "wave_ui.h"
#include "map_editer.h"
#include "enemy_ui.h"
#include "ranking.h"

CFade * CScene::m_pFade = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CScene::CScene()
{
	m_Mode = MODE_NONE;
}
//=============================================
//�f�X�g���N�^
//=============================================
CScene::~CScene()
{
}
//=============================================
//�����֐�
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
//�^�C�g��
//=================================================================================================
//=============================================
//�R���X�g���N�^
//=============================================
CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}


//=============================================
//�������֐�
//=============================================
HRESULT CTitle::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT/2, 0.0f),SCREEN_HEIGHT,SCREEN_WIDTH,0, "data\\TEXTURE\\TITLE\\lab1.png");
	m_pTitle = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f), 305.0f, 600.0f, 0, "data\\TEXTURE\\TITLE\\lab2.png");
	m_posDest = D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f);
	CSound * pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM000);
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CTitle::Uninit()
{

}
//=============================================
//�X�V�֐�
//=============================================
void CTitle::Update()
{
	
	m_pTitle->SetPos(m_pTitle->GetPos() + (m_posDest - m_pTitle->GetPos()) / 120);
	if (CManager::GetDistance((m_pTitle->GetPos() - m_posDest)) <= 10.0f)
	{
		m_posDest = D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f);
	
		m_posDest.x += rand() % 100 - 50;
	}
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		m_pFade->FadeOut(MODE::MODE_TUTORIAL);
	}
}
//=============================================
//�`��֐�
//=============================================
void CTitle::Draw()
{
	
}
//=================================================================================================
//�`���[�g���A��
//=================================================================================================
//=============================================
//�R���X�g���N�^
//=============================================
CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
}


//=============================================
//�������֐�
//=============================================
HRESULT CTutorial::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pTitle[0] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\Labtutorial.png");
	m_pTitle[1] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\Labtutorial2.png");
	m_nDisp = 0;
	m_nCool = 0;
	CSound * pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM000);
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CTutorial::Uninit()
{

}
//=============================================
//�X�V�֐�
//=============================================
void CTutorial::Update()
{
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	CInputMouse * pInputMousee = CManager::GetInputMouse();
	m_nCool--;
	if (m_nCool <= 0)
	{
		m_nCool =0;
	}
	for (int i = 0; i < 2; i++)
	{
		m_pTitle[i]->SetDisp(false);
	}
	if (m_nCool <= 0)
	{
		if ((pInputMousee->GetTrigger(CInputMouse::MOUSE_LEFT) || pInputGamepad->GetTrigger(CInputGamePad::Button_A, 0)) && m_nDisp < 1)
		{
			m_nDisp++;
			m_nCool = 12;
		}
		else if ((pInputMousee->GetTrigger(CInputMouse::MOUSE_RIGTH) || pInputGamepad->GetTrigger(CInputGamePad::Button_B, 0)) && m_nDisp >= 1)
		{
			m_nDisp--;
			m_nCool = 12;
		}
	}
	m_nDisp %= 2;

	if (m_nDisp < 0)
	{
		m_nDisp = 0;
	}

	m_pTitle[m_nDisp]->SetDisp(true);
	if (m_nCool <= 0)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0) || ((pInputMousee->GetTrigger(CInputMouse::MOUSE_LEFT) || pInputGamepad->GetTrigger(CInputGamePad::Button_A, 0)) && m_nDisp > 0))
		{
			m_pFade->FadeOut(MODE::MODE_GAME);
		}
		else if ((pInputMousee->GetTrigger(CInputMouse::MOUSE_RIGTH) || pInputGamepad->GetTrigger(CInputGamePad::Button_B, 0)) && m_nDisp < 1)
		{
			m_pFade->FadeOut(MODE::MODE_TITLE);
		}
	}
}
//=============================================
//�`��֐�
//=============================================
void CTutorial::Draw()
{

}
//=================================================================================================
//�Q�[��
//=================================================================================================
CPlayer * CGame::m_pPlayer = NULL;
CScore * CGame::m_pScore = NULL;
CCamera * CGame::m_pCamera = NULL;
CLight *CGame::m_pLight = NULL;
CMeshfield * CGame::m_pMeshfield = NULL;
CFog * CGame::m_pFog = NULL;
CWave * CGame::m_pWave = NULL;
CWave_UI * CGame::m_pWave_UI = NULL;
CEnemy_UI * CGame::m_pEnemy_UI = NULL;
CMap_Editer * CGame::m_pMap_Editer = NULL;

CGame::CGame()
{
}

CGame::~CGame()
{
}
//=============================================
//�������֐�
//=============================================
HRESULT CGame::Init()
{
	b_Pause = false;
	m_nCnt = 0;
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pLight = DBG_NEW CLight;
	m_pFog = DBG_NEW CFog;
	m_pWave = DBG_NEW CWave;
	m_pWave->Init();
	m_pWave_UI = m_pWave_UI->Create();
	m_pMap_Editer = m_pMap_Editer->Create();
	m_pPause = CPause::Create();
	m_pFog->Init();
	m_pFog->Set(D3DFOG_LINEAR, D3DXCOLOR(0.1313f, 0.1359f, 0.2f, 1.0f), 0.0f, 30000.0f, 0.0f);
	//�������ݒ�;
	
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	};
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	};

	CNumber::Load();
	
	  
	m_pMeshfield = CMeshfield::Create(500.0f, 500.0f, 70, 70);
	CMeshfield::Create(500.0f, 500.0f, 70, 70,D3DXVECTOR3(17250.0f,0.0f,0.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(-17250.0f, 0.0f, 0.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(0.0f, 0.0f, 17250.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(0.0f, 0.0f, -17250.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(17250.0f, 0.0f, 17250.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(-17250.0f, 0.0f, -17250.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(17250.0f, 0.0f, -17250.0f));
	CMeshfield::Create(500.0f, 500.0f, 70, 70, D3DXVECTOR3(-17250.0f, 0.0f, 17250.0f));
			
	CSky::Create();
	CReticle::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pEnemy_UI =CEnemy_UI::Create();

	m_pScore = CScore::Create();
	m_pPlayer = CPlayer::Create();



	CSound * pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM001);


	return S_OK;
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CGame::Uninit()
{
	CNumber::Unload();

	if (m_pScore != NULL)
	{
		//���������
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}
	if (m_pCamera != NULL)
	{
		//���������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		//���������
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	if (m_pFog != NULL)
	{
		//���������
		m_pFog->Uninit();
		delete m_pFog;
		m_pFog = NULL;
	}

	if (m_pWave != NULL)
	{
		//���������
	
		delete m_pWave;
		m_pWave = NULL;
	}
	if (m_pWave_UI != NULL)
	{
		//���������
		m_pWave_UI->Uninit();
		delete m_pWave_UI;
		m_pWave_UI = NULL;
	}
	if (m_pEnemy_UI != NULL)
	{
		//���������
		m_pEnemy_UI->Uninit();
		delete m_pEnemy_UI;
		m_pEnemy_UI = NULL;
	}
	if (m_pMap_Editer != NULL)
	{
		//���������
		m_pMap_Editer->Uninit();
		delete m_pMap_Editer;
		m_pMap_Editer = NULL;
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CGame::Update()
{
	CDebugProc * pDeb = CManager::GetDeb();
	m_nCnt++;
	m_pWave_UI->Update();
	m_pEnemy_UI->Update();
	m_pPause->Update();
	m_pWave->Update();
	m_pFog->Update();
	m_pScore->Update();
	m_pCamera->Update();
	m_pLight->Update();
	//m_pMap_Editer->Update();
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputGamepad->GetTrigger(CInputGamePad::Button_START,0))
	{
		if (CManager::GetPause())
		{
			CManager::SetPause(false);
		}
		else
		{
			CManager::SetPause(true);
		}
	}
	if (m_nCnt % 900 == 0)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			//CEnemy_Walker::Create(D3DXVECTOR3((float)(rand() % 3000 - 1500), 10000.0f, (float)(rand() % 3000 - 1500)), 5);
		}
	}

	pDeb->Print("���݂̓G�̐��F%d\n", CManager::GetEnemyManager()->GetNum());
	if (CManager::GetEnemyManager()->GetNum() <= 0 || m_pPlayer == NULL)
	{
		int nScore = m_pScore->GetScore() * (m_pWave->GetPlayLevel()*0.1f);
		if (CManager::GetEnemyManager()->GetNum() <= 0 && m_pFade->GetState() == CFade::STATE_NONE)
		{
			m_pScore->Add(nScore);
		}
		m_pFade->FadeOut(MODE::MODE_RESULT);
	}
	CManager::SetScore(m_pScore->GetScore());
}
//=============================================
//�`��֐�
//=============================================
void CGame::Draw()
{
	m_pPause->Draw();
	m_pFog->Draw();
}

//=============================================
//���W����
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
//�R���X�g���N�^
//=============================================
CResult::CResult()
{
}

CResult::~CResult()
{
}
//=============================================
//�������֐�
//=============================================
HRESULT CResult::Init()
{
	m_pFade = DBG_NEW CFade;
	m_pFade->Init();
	m_pRanking = DBG_NEW CRankng;
	m_pRanking->Init();
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT, SCREEN_WIDTH, 0, "data\\TEXTURE\\Ranking.png");
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CResult::Uninit()
{
	if (m_pRanking != NULL)
	{
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CResult::Update()
{
	m_pRanking->Update();
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad * pInputGamepad = CManager::GetInputGamePad();
	if (pInputKeyboard->GetTrigger(DIK_RETURN)|| pInputGamepad->GetTrigger(CInputGamePad::Button_START, 0))
	{
		m_pFade->FadeOut(MODE::MODE_TITLE);
	}
}
//=============================================
//�`��֐�
//=============================================
void CResult::Draw()
{
	m_pRanking->Draw();
}
