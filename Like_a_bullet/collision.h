//==================
//バレットヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Collision_H_//二重インクルード防止のマクロ
#define _Collision_H_
//インクルード
#include "main.h"
#include "billboard.h"
#include "orbit.h"

//クラス定義
class CCollision : public CObject //オブジェクトクラスの継承
{
public:
	CCollision(int nPriority = 2);
	~CCollision();
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCollision * Create(D3DXVECTOR3 pos,int nDamage, TYPE type);

	bool CollisionEnemy(D3DXVECTOR3 pos);
	bool CollisionPlayer(D3DXVECTOR3 pos);
private:
	TYPE m_Type;
	int m_nDamage;
	bool  m_bactive;
};

#endif // ! _Collision_H_