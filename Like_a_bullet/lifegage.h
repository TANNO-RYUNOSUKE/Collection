//==================
//���C�t�Q�[�W�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _LIFEGAGE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _LIFEGAGE_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"
#include "particle.h"
#include "number.h"

#define LIFE_LENGTH (5)
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

private:
	CNumber * m_apNumber[LIFE_LENGTH];
	CObject2D * m_pGage;
	CObject2D * m_pGageRed;
	float m_fWidth;
	int m_nMax;
	int m_ndata;
};

#endif // ! _LIFEGAGE_H_