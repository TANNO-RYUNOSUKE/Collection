//==================
//スコアヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Score_H_//二重インクルード防止のマクロ
#define _Score_H_
//インクルード
#include "main.h"
#include "number.h"

//マクロ定義
#define NUM_NUMBER (8)//桁数
//クラス定義
class CScore:public CNumber
{
public:
	CScore();

	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore * Create(void);

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const int ndata) { m_ndata = ndata; }
	void Add(const int ndata) { m_ndata += ndata; }
	int GetScore(void) { return m_ndata; }

private:
	CNumber * m_apNumber[NUM_NUMBER]; //ナンバーオブジェクトへのポインタ
	int m_ndata;//持っている情報
	D3DXVECTOR3 m_pos;//一桁目の座標
};

#endif // ! _Score_H_
