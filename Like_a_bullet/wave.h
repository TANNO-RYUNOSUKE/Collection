//==================
//ウェーブヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Wave_H_//二重インクルード防止のマクロ
#define _Wave_H_
//インクルード
#include "main.h"
#include "enemy.h"
#include "enemymanager.h"

#define MAX_PLAYLEVEL (5)
#define NUM_WAVE (16)//エネミーの最大数
//クラス定義
class CWave //マネージャクラス
{
public:
	CWave();
	~CWave();
	struct Waves
	{
		CEnemy::TYPE type;
		D3DXVECTOR3 pos;
		int nLife;
	};
	void Init(void);
	void Update(void);
	void Regist(CEnemy::TYPE type, D3DXVECTOR3 pos, int nLife, int nWave);
//	Waves ** GetWave(void) { return &m_aWave[0][0]; }
	int GetCnt(void) { return m_nCnt; }
	void AddScore(int nScore) { m_anWaveScore[m_nCnt] += nScore; }
	void Damagecheck(bool bdamage) { m_bDamage = bdamage; }
	int GetPlayLevel() { return m_nPlayLevel; }
private:
    Waves m_aWave[NUM_WAVE][NUM_ENEMY];//エネミーの配列
	int m_nCnt;//合計数
	int m_nNum;
	int m_nTimeCounter;
	int m_nCntFlowless;
	int m_nMax_Wave;
	bool m_bDamage;
	int m_anWaveScore[NUM_WAVE];
	int m_nAttackLevel;
	int m_nPlayLevel;
};

#endif // ! _Wave_H_
