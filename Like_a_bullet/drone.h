//==================
//3Dオブジェクトヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Drone_H_//二重インクルード防止のマクロ
#define _Drone_H_
//インクルード
#include "main.h"
#include "object.h"
#include "objectX.h"
#include "line.h"
#include "orbit.h"
//クラス定義
class CDrone : public CObject //オブジェクトクラスの継承
{
public:

	CDrone(int nPriority = 0);

	~CDrone();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CDrone * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 3);
private:
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rotDest;
	CObjectX * m_pObjectX;
	CLine * m_pLine;
	COrbit * m_pOrbit;//軌跡
	COrbit * m_pOrbit2;//軌跡2
};

#endif // ! _Drone_H_
