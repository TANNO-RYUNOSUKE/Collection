//==================
//���C�t�Q�[�W�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _explosion_H_//��d�C���N���[�h�h�~�̃}�N��
#define _explosion_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"
#include "animbillboard.h"
#include "collision.h"
//�N���X��`
class CExplosion : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion * Create(D3DXVECTOR3 pos,int nLife);
	void SetLife(int n) { m_nLife = n; }
private:
	CSphereCollision * pCol;
	int m_nLife;
};

#endif // ! _explosion_H_