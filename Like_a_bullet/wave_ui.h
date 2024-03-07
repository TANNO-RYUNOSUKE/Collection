//==================
//ウェーブUIヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Wave_UI_H_//二重インクルード防止のマクロ
#define _Wave_UI_H_
//インクルード
#include "main.h"
#include "number.h"

//マクロ定義
#define NUM_UINUMBER (2)//桁数
//クラス定義
class CWave_UI :public CNumber
{
public:
	CWave_UI();

	~CWave_UI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CWave_UI * Create(void);

	void SetDisp(const int nCntDisp) { m_nCntDisp = nCntDisp; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const int ndata) { m_ndata = ndata; }
private:
	CObject2D * m_pUi;
	CNumber * m_apNumber[NUM_UINUMBER]; //ナンバーオブジェクトへのポインタ
	int m_ndata;//持っている情報
	int m_nCntDisp;
	D3DXVECTOR3 m_pos;//一桁目の座標
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_Uipos1;
	D3DXVECTOR3 m_Uipos2;
	D3DXVECTOR3 m_Uisize1;
	D3DXVECTOR3 m_Uisize2;
	D3DXVECTOR3 m_NumberSize1;
	D3DXVECTOR3 m_NumberSize2;
};

#endif // ! _Wave_UI_H_