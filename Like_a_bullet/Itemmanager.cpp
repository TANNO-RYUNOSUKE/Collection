#include "Itemmanager.h"
CItem *CItemManager::m_apItem[NUM_Item] = {};

//==============================
//コンストラクタ,デストラクタ
//==============================
CItemManager::CItemManager()
{

}
CItemManager::~CItemManager()
{

}
void CItemManager::Init(void)
{
	m_nNumALL = 0;
	for (int nCnt = 0; nCnt < NUM_Item; nCnt++)
	{
		m_apItem[nCnt] = NULL;
	}

}
//==============================
//登録処理
//==============================
void CItemManager::Regist(CItem * pItem)
{
	for (int nCnt = 0; nCnt < NUM_Item; nCnt++)
	{
		if (m_apItem[nCnt] == NULL)
		{
			m_apItem[nCnt] = pItem;
			m_apItem[nCnt]->SetID(nCnt);
			m_nNumALL++;
			break;
		}
	}
}
//==============================
//解放処理
//==============================
void CItemManager::Release(int nID)
{
	if (m_apItem[nID] != NULL)
	{
		m_apItem[nID] = NULL;
		m_nNumALL--;
	}
}
