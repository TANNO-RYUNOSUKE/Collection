//==================
//マネージャヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _ItemMANAGER_H_//二重インクルード防止のマクロ
#define _ItemMANAGER_H_
//インクルード
#include "main.h"
#include "Item.h"

#define NUM_Item (256)//アイテムの最大数
//クラス定義
class CItemManager //マネージャクラス
{
public:
	CItemManager();
	~CItemManager();

	void Init(void);
	void Regist(CItem * pItem);
	void Release(int nID);
	CItem ** GetItem(void) { return &m_apItem[0]; }
	int GetNum(void) { return m_nNumALL; }
private:
	static CItem * m_apItem[NUM_Item];//アイテムの配列
	int m_nNumALL;//合計数
};

#endif // ! _ItemMANAGER_H_
