//==================
//�}�l�[�W���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _ItemMANAGER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _ItemMANAGER_H_
//�C���N���[�h
#include "main.h"
#include "Item.h"

#define NUM_Item (256)//�A�C�e���̍ő吔
//�N���X��`
class CItemManager //�}�l�[�W���N���X
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
	static CItem * m_apItem[NUM_Item];//�A�C�e���̔z��
	int m_nNumALL;//���v��
};

#endif // ! _ItemMANAGER_H_
