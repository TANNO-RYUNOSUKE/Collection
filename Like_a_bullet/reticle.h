//==================
//�G�N�X�v���[�W�����w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _RETICLE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _RETICLE_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"

//�N���X��`
class CReticle : public CObject2D //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CReticle();
	~CReticle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CReticle * Create(D3DXVECTOR3 pos);

private:
	int * nIdx;//�e�N�X�`���ւ̃C���f�b�N�X
};

#endif // ! _RETICLE_H_
