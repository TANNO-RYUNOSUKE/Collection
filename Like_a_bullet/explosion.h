//==================
//エクスプロージョンヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _EXPLOSION_H_//二重インクルード防止のマクロ
#define _EXPLOSION_H_
//インクルード
#include "main.h"
#include "object.h"
#include "object2D.h"

//クラス定義
class CExplosion : public CObject2D //オブジェクトクラスの継承
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion * Create(D3DXVECTOR3 pos);

	static HRESULT Load(void);
	static void Unload(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	int m_nCountAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターン
};

#endif // ! _EXPLOSION_H_
