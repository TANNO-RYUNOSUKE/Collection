//==================
//MultiBgヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _MULTIBG_H_//二重インクルード防止のマクロ
#define _MULTIBG_H_
//インクルード
#include "main.h"
#include "object2D.h"

//マクロ定義
#define NUM_MULTIBG (3) //背景の数

//前方宣言
class CObject2D;

//クラス定義
class CMultiBg : public CObject //オブジェクトクラスの継承
{
public:
	CMultiBg();
	~CMultiBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void Unload(void);

	static CMultiBg * Create(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	void BindTexture();
private:
	static CObject2D * m_apObject2D[NUM_MULTIBG];//2dオブジェクト
	static LPDIRECT3DTEXTURE9 m_paTexture[NUM_MULTIBG];	//テクスチャへのポインタ
	D3DXVECTOR2 m_aTexUV;//テクスチャ座標
};

#endif // ! _MULTIBG_H_
