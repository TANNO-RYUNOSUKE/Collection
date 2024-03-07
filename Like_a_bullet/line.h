//==================
//3Dオブジェクトヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _Line_H_//二重インクルード防止のマクロ
#define _Line_H_
//インクルード
#include "main.h"
#include "object.h"

//クラス定義
class CLine : public CObject //オブジェクトクラスの継承
{
public:

	CLine(int nPriority = 5);

	~CLine();

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CLine * Create(D3DXVECTOR3 start, D3DXVECTOR3 end,D3DXCOLOR col, int nPriority = 5);

	CLine * GetLine(void) { return this; }
	void SetStart(D3DXVECTOR3 pos) { m_start = pos; }
	void SetEnd(D3DXVECTOR3 pos) { m_end = pos; }
	void SetEndDest(D3DXVECTOR3 pos) { m_endDest = pos; }
	D3DXVECTOR3 GetEnd(void) { return m_end; }
	D3DXVECTOR3 GetStart(void) { return m_start; }
protected:
	//ポリゴン表示用

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff2;		//頂点バッファ
private:
	float m_fHeight;	//高さ
	float m_fWidth;		//
	D3DXVECTOR3 m_start;
	D3DXVECTOR3 m_end;
	D3DXVECTOR3 m_endDest;
	D3DXCOLOR col;
};

#endif // ! _Line_H_
