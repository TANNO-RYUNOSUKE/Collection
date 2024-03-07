//==================
//バレットヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _BLOCK_H_//二重インクルード防止のマクロ
#define _BLOCK_H_
//インクルード
#include "main.h"
#include "object2D.h"

//クラス定義
class CBlock : public CObject2D //オブジェクトクラスの継承
{
public:
	CBlock(int nPriority = 2);
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBlock * Create(D3DXVECTOR3 pos);

	static HRESULT Load(void);
	static void Unload(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

private:
	bool Collision();

	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ

};

#endif // ! _BLOCK_H_