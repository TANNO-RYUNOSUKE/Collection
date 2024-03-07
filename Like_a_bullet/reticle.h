//==================
//エクスプロージョンヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _RETICLE_H_//二重インクルード防止のマクロ
#define _RETICLE_H_
//インクルード
#include "main.h"
#include "object.h"
#include "object2D.h"

//クラス定義
class CReticle : public CObject2D //オブジェクトクラスの継承
{
public:
	CReticle();
	~CReticle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CReticle * Create(D3DXVECTOR3 pos);

private:
	int * nIdx;//テクスチャへのインデックス
};

#endif // ! _RETICLE_H_
