//==================
//�A�C�e���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _ITEM_H_//��d�C���N���[�h�h�~�̃}�N��
#define _ITEM_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"
#include "particle.h"
//�N���X��`
class CItem : public CObject //�I�u�W�F�N�g�N���X�̌p��
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