//==================
//ロックオンマーカーヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _LOCKONMARKER_H_//二重インクルード防止のマクロ
#define _LOCKONMARKER_H_
//インクルード
#include "main.h"
#include "billboard.h"

//クラス定義
class CMarker : public CBillboard //オブジェクトクラスの継承
{
public:
	CMarker(int nPriority = 7);
	~CMarker();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPosdest(D3DXVECTOR3 pos) { m_posDest = pos; }
	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	bool GetDisp(void) { return m_bDisp; }
private:
	
	bool m_bDisp;
	D3DXVECTOR3 m_posDest;
};

//クラス定義
class CLockonmarker : public CMarker //オブジェクトクラスの継承
{
public:
	CLockonmarker();
	~CLockonmarker();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

//クラス定義
class CJumpmarker : public CMarker //オブジェクトクラスの継承
{
public:
	CJumpmarker();
	~CJumpmarker();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif // ! _LOCKONMARKER_H_