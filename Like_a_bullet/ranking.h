//==================
//スコア処理
//==================
#ifndef _Ranking_H_
#define _Ranking_H_
#include "main.h"
#include "number.h"

//マクロ定義
#define MAX_NUMBER (8)
#define NUM_PLACERANKING (8)
#define INTERVAL (30)

class CRankng
{
public:
	CRankng();
	~CRankng();
	//プロトタイプ宣言
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(int nRanking);
	int GetRanking();
	int Sort();
private:
	CNumber * m_apNumber[NUM_PLACERANKING][MAX_NUMBER]; //ナンバーオブジェクトへのポインタ
	int m_nTarget;
	int m_nScore[NUM_PLACERANKING];
	int m_nDispCount;
	bool m_bDisp;
};


//プロトタイプ宣言
void InitRanking();
void UninitRanking();
void UpdateRanking();
void DrawRanking();
void SetRanking(int nRanking);
int GetRanking();

#endif // !_Ranking_H_
