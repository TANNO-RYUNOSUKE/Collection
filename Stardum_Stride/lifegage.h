//==================
//���C�t�Q�[�W�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _LIFEGAGE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _LIFEGAGE_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"

//�N���X��`
class CGage : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CGage();
	~CGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGage * Create(D3DXVECTOR3 pos, float fWidth,int nMax);
	void SetData(int data) { m_ndata = data; }
private:

	CObject2D * m_pGage;
	CObject2D * m_pGageRed;
	float m_fWidth;
	int m_nMax;
	int m_ndata;
};

#endif // ! _LIFEGAGE_H_