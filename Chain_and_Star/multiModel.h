//============================================================
//
//	�}���`���f���w�b�_�[ [multiModel.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MULTIMODEL_H_
#define _MULTIMODEL_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "model.h"
#include "object.h"

//************************************************************
//	�N���X��`
//************************************************************
// �}���`���f���N���X
class CMultiModel : CObject
{
public:
	// �R���X�g���N�^
	CMultiModel();
	explicit CMultiModel(const CObject::ELabel label, const int nPriority = DEFAULT_PRIO);

	// �f�X�g���N�^
	~CMultiModel();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	void BindModel(const int nModelID) override;				// ���f������ (�C���f�b�N�X)
	void BindModel(const char *pModelPass) override;			// ���f������ (�p�X)
	void SetVec3Position(const D3DXVECTOR3& rPos) override;		// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override;			// �ʒu�擾
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;		// �����ݒ�
	D3DXVECTOR3 GetVec3Rotation(void) const override;			// �����擾
	void SetVec3Scaling(const D3DXVECTOR3& rScale) override;	// �g�嗦�ݒ�
	D3DXVECTOR3 GetVec3Scaling(void) const override;			// �g�嗦�擾
	void SetAllMaterial(const D3DXMATERIAL& rMat) override;		// �}�e���A���S�ݒ�
	void ResetMaterial(void) override;							// �}�e���A���Đݒ�
	D3DXMATRIX *GetPtrMtxWorld(void) override;					// �}�g���b�N�X�|�C���^�擾
	D3DXMATRIX GetMtxWorld(void) const override;				// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CMultiModel *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,				// �ʒu
		const D3DXVECTOR3& rRot,				// ����
		const D3DXVECTOR3& rScale = VEC3_ONE	// �傫��
	);

	// �����o�֐�
	void SetMaterial(const D3DXMATERIAL& rMat, const int nID);	// �}�e���A���ݒ�
	D3DXMATERIAL GetMaterial(const int nID) const;		// �}�e���A���擾
	void SetAlpha(const float fAlpha);					// �����x�ݒ�
	float GetAlpha(void) const;							// �����x�擾
	float GetMaxAlpha(void) const;						// �ő哧���x�擾
	void SetMtxWorld(const D3DXMATRIX& rMtxWorld);		// �}�g���b�N�X�ݒ�
	void SetParentObject(CObject *pObject);				// �e�I�u�W�F�N�g�ݒ�
	void SetParentModel(CMultiModel *pModel);			// �e�I�u�W�F�N�g�ݒ�
	void DeleteParentObject(void);						// �e�I�u�W�F�N�g�폜
	void SetModelData(const CModel::SModel& rModel);	// ���f�����ݒ�
	CModel::SModel GetModelData(void) const;			// ���f�����擾

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override;	// �j��

	// �����o�֐�
	HRESULT SetOriginMaterial(const LPD3DXBUFFER pBuffMat, const int nNumMat);	// ���}�e���A���ݒ�

	// �����o�ϐ�
	CModel::SModel	m_modelData;	// ���f�����
	CObject			*m_pParent;		// �e�I�u�W�F�N�g�ւ̃|�C���^
	D3DXMATERIAL	*m_pMat;		// �}�e���A���ւ̃|�C���^
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;			// �ʒu
	D3DXVECTOR3		m_rot;			// ����
	D3DXVECTOR3		m_scale;		// �g�嗦
	int				m_nModelID;		// ���f���C���f�b�N�X
};

#endif	// _MULTIMODEL_H_