#include "Wave.h"
#include "manager.h"
#include "scene.h"
#include "wave_ui.h"
#include "fade.h"
#include "sound.h"
#include "score.h"

//==============================
//コンストラクタ,デストラクタ
//==============================
CWave::CWave()
{

}
CWave::~CWave()
{

}
void CWave::Init(void)
{
	m_nPlayLevel = MAX_PLAYLEVEL / 2;
	m_nAttackLevel = 0;
	m_nCntFlowless = 0;
	m_nMax_Wave = 0;
	m_bDamage = false;
	m_nTimeCounter = 0;
	for (int nCnt1 = 0; nCnt1 < NUM_WAVE; nCnt1++)
	{
		m_anWaveScore[nCnt1] = 0;
		for (int nCnt2 = 0; nCnt2 < NUM_ENEMY; nCnt2++)
		{
			m_aWave[nCnt1][nCnt2] = {};
		}
	}
	m_nCnt = 0;

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		Regist(CEnemy::TYPE_WALKER, D3DXVECTOR3((float)(rand() % 6000 - 3000 + 8000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000 - 8000)), 5, 0);
	
	}
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		Regist(CEnemy::TYPE_WALKER, D3DXVECTOR3((float)(rand() % 6000 - 3000 + 8000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000 - 8000)), 5, 1);
		Regist(CEnemy::TYPE_DORONE, D3DXVECTOR3((float)(rand() % 60000 - 30000), (float)(rand() % 5000 + 1000), (float)(rand() % 60000 - 30000)), 5, 1);

	}
	Regist(CEnemy::TYPE_ELITE, D3DXVECTOR3((float)(rand() % 6000 - 3000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000)), 25, 2);
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		Regist(CEnemy::TYPE_WALKER, D3DXVECTOR3((float)(rand() % 6000 - 3000 + 8000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000 + 8000)), 5, 3);
		Regist(CEnemy::TYPE_DORONE, D3DXVECTOR3((float)(rand() % 60000 - 30000), (float)(rand() % 5000 + 1000), (float)(rand() % 60000 - 30000)), 5, 3);
	}
	Regist(CEnemy::TYPE_ELITE, D3DXVECTOR3((float)(rand() % 6000 - 3000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000)), 25, 3);
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		Regist(CEnemy::TYPE_WALKER, D3DXVECTOR3((float)(rand() % 6000 - 3000 + 8000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000 - 8000)), 5, 4);
		Regist(CEnemy::TYPE_DORONE, D3DXVECTOR3((float)(rand() % 60000 - 30000), (float)(rand() % 5000 + 1000), (float)(rand() % 60000 - 30000)), 5, 4);
	}
	Regist(CEnemy::TYPE_ELITE, D3DXVECTOR3((float)(rand() % 6000 - 3000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000)), 50, 5);
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Regist(CEnemy::TYPE_WALKER, D3DXVECTOR3((float)(rand() % 6000 - 3000 + 8000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000 - 8000)), 15, 6);
		Regist(CEnemy::TYPE_DORONE, D3DXVECTOR3((float)(rand() % 6000 - 3000 + 8000), (float)(rand() % 500 + 100), (float)(rand() % 60000 - 30000)), 10, 6);
	}
	Regist(CEnemy::TYPE_ELITE, D3DXVECTOR3((float)(rand() % 6000 - 3000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000)), 30, 7);
	Regist(CEnemy::TYPE_ELITE, D3DXVECTOR3((float)(rand() % 6000 - 3000), (float)(rand() % 500 + 100), (float)(rand() % 6000 - 3000)), 30, 7);


}
void CWave::Update(void)
{
	if (CManager::GetScene()->GetFade()->GetState() == CFade::STATE_NONE)
	{
		if (m_nCnt < NUM_WAVE)
		{
			int nCnt = CManager::GetEnemyManager()->GetNum();
			if (nCnt == 0)
			{
				if (m_bDamage == false && m_nCnt > 0)
				{
					m_nPlayLevel++;
					m_nCntFlowless++;
					CObject2D * pObj =CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH*0.85f, SCREEN_HEIGHT*0.9f,0.0f),56.0f,257.0f,0,"data\\TEXTURE\\FlawLess.png");
					pObj->SetMove(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
					pObj->SetLife(60);
					CGame::GetScore()->Add(m_anWaveScore[m_nCnt] * 0.2f);
				}
				else
				{
					m_nPlayLevel--;
				}
				if (m_nPlayLevel >= MAX_PLAYLEVEL)
				{
					m_nPlayLevel = MAX_PLAYLEVEL;
				}
				else if(m_nPlayLevel <= 0)
				{
					m_nPlayLevel = 0;
				}
				if (m_nCnt == 5)
				{
					if (m_nPlayLevel >= 4)
					{
						Regist(CEnemy::TYPE_BOSS, D3DXVECTOR3(0.0f,500.0f, 0.0f),120, 8);
					}
				}
			
				m_nTimeCounter = 0;
				if (m_nCnt < m_nMax_Wave)
				{

					CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOCK);
					CGame::GetWaveUI()->SetDisp(120);
					for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
					{
						switch (m_aWave[m_nCnt][nCnt].type)
						{
						case CEnemy::TYPE_WALKER:
							CEnemy_Walker::Create(m_aWave[m_nCnt][nCnt].pos, m_aWave[m_nCnt][nCnt].nLife);
							break;
						case CEnemy::TYPE_DORONE:
							CEnemy_Drone::Create(m_aWave[m_nCnt][nCnt].pos, m_aWave[m_nCnt][nCnt].nLife);
							break;
						case CEnemy::TYPE_ELITE:
							CEnemy_Elite::Create(m_aWave[m_nCnt][nCnt].pos, m_aWave[m_nCnt][nCnt].nLife);
							break;
						case CEnemy::TYPE_BOSS:
							CEnemy_Boss::Create(m_aWave[m_nCnt][nCnt].pos, m_aWave[m_nCnt][nCnt].nLife);
							break;
						default:
							break;
						}
					}
					m_nCnt++;
					m_bDamage = false;
				}
			}
		}
	}
}
//==============================
//登録処理
//==============================
void CWave::Regist(CEnemy::TYPE type, D3DXVECTOR3 pos, int nLife, int nWave)
{
	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (m_aWave[nWave][nCnt].nLife == 0)
		{
			if (m_nMax_Wave < nWave + 1)
			{
				m_nMax_Wave = nWave + 1;
			}
			
			m_aWave[nWave][nCnt].type = type;
			m_aWave[nWave][nCnt].pos = pos;
			m_aWave[nWave][nCnt].nLife = nLife;
			break;
		}
	}
}

