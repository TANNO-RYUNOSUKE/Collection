#include <stdio.h>
#include <stdlib.h>
#include "Ranking.h"
#include "manager.h"
#include "renderer.h"




//プロトタイプ宣言
int Sort();

//グローバル変数
int g_nRanking[MAX_NUMBER];
int g_nRankingPoint[MAX_NUMBER];
int m_nScore[MAX_NUMBER];


LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;
D3DXVECTOR3 g_posPcoreRanking;


CRankng::CRankng()
{
	m_nDispCount = 0;
}

CRankng::~CRankng()
{
}
//======================================
//初期化処理
//======================================
void CRankng::Init(void)
{
	m_nDispCount = 0;
	m_nTarget = -1;
	for (int i = 0; i < NUM_PLACERANKING; i++)
	{
		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{
			m_apNumber[i][nCnt] = CNumber::Create();
			m_apNumber[i][nCnt]->Set(D3DXVECTOR3(500.0f + 25.0f * nCnt, 150.0f + 60.0f * i, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f);
		}
	}
	Sort();
	
}

//======================================
//終了処理
//======================================
void CRankng::Uninit(void)
{
	for (int i = 0; i < NUM_PLACERANKING; i++)
	{
		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{
			m_apNumber[i][nCnt]->Uninit();
			delete m_apNumber[i][nCnt];
			m_apNumber[i][nCnt] = NULL;
		}
	}
}
//======================================
//更新処理
//======================================
void CRankng::Update(void)
{
	VERTEX_2D *pVtx;

	m_nDispCount++;
	if (m_nDispCount >= INTERVAL)
	{//カウンターがインターバルを超えたとき表示を切り替える
		m_nDispCount = 0;
		if (m_bDisp == true)
		{
			m_bDisp = false;
		}
		else
		{
			m_bDisp = true;
		}
	}

	for (int i = 0; i < NUM_PLACERANKING; i++)
	{
		m_apNumber[i][0]->Setdata(m_nScore[i] % 100000000 / 10000000);
		m_apNumber[i][1]->Setdata(m_nScore[i] % 10000000 / 1000000);
		m_apNumber[i][2]->Setdata(m_nScore[i] % 1000000 / 100000);
		m_apNumber[i][3]->Setdata(m_nScore[i] % 100000 / 10000);
		m_apNumber[i][4]->Setdata(m_nScore[i] % 10000 / 1000);
		m_apNumber[i][5]->Setdata(m_nScore[i] % 1000 / 100);
		m_apNumber[i][6]->Setdata(m_nScore[i] % 100 / 10);
		m_apNumber[i][7]->Setdata(m_nScore[i] % 10 / 1);
		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{
			m_apNumber[i][nCnt]->Update();
		}
	}
}

//======================================
//描画処理
//======================================
void CRankng::Draw(void)
{
	for (int i = 0; i < NUM_PLACERANKING; i++)
	{
		for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
		{
			if (i == m_nTarget)
			{
					m_apNumber[i][nCnt]->Get2D()->SetDisp(m_bDisp);
					m_apNumber[i][nCnt]->Draw();
			}
			else
			{
				m_apNumber[i][nCnt]->Draw();
			}
		}
	}
}
//======================================
//設定処理
//======================================
void CRankng::Set(int nRanking)
{

	int nCntRanking;
	VERTEX_2D *pVtx;
	int aTexU[MAX_NUMBER][NUM_PLACERANKING];
	for (int nCnt1 = 0; nCnt1 < MAX_NUMBER; nCnt1++)
	{
		g_nRanking[nCnt1] = m_nScore[nCnt1];

		aTexU[nCnt1][0] = g_nRanking[nCnt1] % 1000 / 100;
		aTexU[nCnt1][1] = g_nRanking[nCnt1] % 100 / 10;
		aTexU[nCnt1][2] = g_nRanking[nCnt1] % 10 / 1;
	}								
	

	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	
	
	g_pVtxBuffRanking->Unlock();
}

//======================================
//入力処理
//======================================
int CRankng::Sort()
{
	FILE*pFile;
	int nCount;
	int nCheck = 0;
	int nData;
	int nTemp;

	int nAdd = CManager::GetScore();
	
	//読み込み
	pFile = fopen("Ranking.txt", "r");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < NUM_PLACERANKING; nCount++)
		{
			fscanf(pFile, "%d\n", &m_nScore[nCount]);
		}
		fclose(pFile);
	}
	else
	{
		for (nCount = 0; nCount < NUM_PLACERANKING; nCount++)
		{
			m_nScore[nCount] = 0;
		}
	
	}
	

	for (nCheck = 0; nCheck < NUM_PLACERANKING - 1; nCheck++)
	{
		nData = nCheck;
		for (nCount = (nCheck + 1); nCount < NUM_PLACERANKING; nCount++)
		{
			if (m_nScore[nData] < m_nScore[nCount])
			{
				nData = nCount;
			}
		}
		nTemp = m_nScore[nCheck];

		m_nScore[nCheck] = m_nScore[nData];
		m_nScore[nData] = nTemp;
	}

    //今回のスコアと比較
	scanf("%d", &nAdd);
	if (nAdd > m_nScore[NUM_PLACERANKING - 1])
	{
		m_nScore[NUM_PLACERANKING - 1] = nAdd;
	}

	for (nCount = 0; nCount < NUM_PLACERANKING - 1; nCount++)
	{
		for (nCheck = (nCount + 1); nCheck < NUM_PLACERANKING; nCheck++)
		{
			nTemp = m_nScore[nCheck];
			if (m_nScore[nCount] < m_nScore[nCheck])
			{
				m_nScore[nCheck] = m_nScore[nCount];
				m_nScore[nCount] = nTemp;
			}
		}
	}
	
	//書き込み
	pFile = fopen("Ranking.txt", "w");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < NUM_PLACERANKING; nCount++)
		{
			fprintf(pFile, "%d\n", m_nScore[nCount]);
		}
		fclose(pFile);
	}

	for (int nCnt = 0; nCnt < NUM_PLACERANKING; nCnt++)
	{
		if (m_nScore[nCnt] == nAdd)
		{
			m_nTarget = nCnt;
			break;
		}
	}

	return 0;
}