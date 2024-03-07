//==================
//BGヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _BG_H_//二重インクルード防止のマクロ
#define _BG_H_
//インクルード
#include "main.h"
#include "object2D.h"

//マクロ定義
#define NUM_BG (3) //背景の数

//クラス定義
class CBg : public CObject2D //オブジェクトクラスの継承
{
public:
	CBg();
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg * Create(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_BG]; //テクスチャへのポインタ
	D3DXVECTOR2 m_aTexUV[NUM_BG];//テクスチャ座標
	
};

#endif // ! _BG_H_
