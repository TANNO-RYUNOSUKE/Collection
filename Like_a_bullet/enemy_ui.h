//==================
//ウェーブUIヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Enemy_UI_H_//二重インクルード防止のマクロ
#define _Enemy_UI_H_
//インクルード
#include "main.h"
#include "number.h"

//マクロ定義
#define NUM_E_UINUMBER (2)//桁数
//クラス定義
class CEnemy_UI :public CNumber
{
public:
	CEnemy_UI();

	~CEnemy_UI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy_UI * Create(void);

	
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const int ndata) { m_ndata = ndata; }
private:
	CObject2D * m_pUi;
	CNumber * m_apNumber[NUM_E_UINUMBER]; //ナンバーオブジェクトへのポインタ
	int m_ndata;//持っている情報
	D3DXVECTOR3 m_pos;//一桁目の座標
};

#endif // ! _Enemy_UI_H_