//==================
//ライフゲージヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _LIFEGAGE_H_//二重インクルード防止のマクロ
#define _LIFEGAGE_H_
//インクルード
#include "main.h"
#include "object2D.h"
#include "particle.h"
#include "number.h"

#define LIFE_LENGTH (5)
//クラス定義
class CGage : public CObject //オブジェクトクラスの継承
{
public:
	CGage();
	~CGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGage * Create(D3DXVECTOR3 pos, float fWidth,int nMax);

private:
	CNumber * m_apNumber[LIFE_LENGTH];
	CObject2D * m_pGage;
	CObject2D * m_pGageRed;
	float m_fWidth;
	int m_nMax;
	int m_ndata;
};

#endif // ! _LIFEGAGE_H_