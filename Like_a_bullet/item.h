//==================
//アイテムヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _ITEM_H_//二重インクルード防止のマクロ
#define _ITEM_H_
//インクルード
#include "main.h"
#include "object2D.h"
#include "particle.h"
//クラス定義
class CItem : public CObject //オブジェクトクラスの継承
{
public:
	CItem();
	~CItem();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nScore);

	void SetID(int nID) { m_nID = nID; }
	bool Collision(D3DXVECTOR3 pos);
private:
	CParticle * m_pParticle;
	int m_nID;
	int m_nScore;
	int m_nLife;
	int m_nLifeCount;
};

#endif // ! _ITEM_H_