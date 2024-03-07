//============================================================
//
//	�K�C�h�w�b�_�[ [guide.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GUIDE_H_
#define _GUIDE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object3D.h"

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
class CObjectGauge3D;	// �I�u�W�F�N�g�Q�[�W3D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �K�C�h�N���X
class CGuide : public CObject3D
{
public:
	// �R���X�g���N�^
	CGuide();

	// �f�X�g���N�^
	~CGuide();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	// �ÓI�����o�֐�
	static CGuide *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rSize	// �傫��
	);
};

#endif	// _GUIDE_H_