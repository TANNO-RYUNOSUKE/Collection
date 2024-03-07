#include "ModelParticle.h"
#include "ModelEffect.h"
#include "texture.h"
#include "manager.h"

//<**************************************************************
//���O�錾
//<**************************************************************
namespace
{
	const int			NUM_PARTICLE	= 1;											//�g���p�[�e�B�N���̐�
	const D3DXVECTOR3	MOVE_VALUE		= D3DXVECTOR3(5.0f, 45.0f, 5.0f);				//�ړ��l
	const int			NUM_LIFE		= 100;											//����
	const float			FLOAT_VALUE		= 100.0f;										//�ړ��l���o�����߂̒l
}
//<=============================================================
//���f���p�[�e�B�N���̃R���X�g���N�^
//<=============================================================
CModParticle::CModParticle() : CObject(CObject::LABEL_PARTICLE, 1)
{
	// �����o�ϐ����N���A
	m_pos = VEC3_ZERO;	// �ʒu
	m_col = XCOL_WHITE;	// �F
	m_nLife = 0;		// ����
}

//<=============================================================
//���f���p�[�e�B�N���̐�������
//<=============================================================
CModParticle *CModParticle::Create(const D3DXVECTOR3 rPos, const D3DXCOLOR col, int texID)
{
	//�ŏ��ɐ�������
	CModParticle *pModParticle = new CModParticle;

	//���g�`�F�b�N
	if (pModParticle != nullptr)
	{
		//�����������s���Ă��Ȃ�����Assert
		assert(pModParticle->Init() == S_OK);

		//�l�̑��
		pModParticle->m_pos = rPos;
		pModParticle->m_col = col;
		pModParticle->m_pTexID = texID;

		//�|�C���^��Ԃ�
		return pModParticle;
	}
	//�ł��Ȃ�������
	else
	{
		//nullptr��Ԃ�
		return nullptr;
	}

	//nullptr��Ԃ�
	return nullptr;
}
//<=============================================================
//���f���p�[�e�B�N���̏���������
//<=============================================================
HRESULT CModParticle::Init(void)
{
	// �����o�ϐ����N���A
	m_pos = VEC3_ZERO;	// �ʒu
	m_col = XCOL_WHITE;	// �F
	m_move = VEC3_ZERO;	// �ړ��l
	m_rot = VEC3_ZERO;	// ����
	m_nLife = 5;		// ����
	m_pTexID = -1;		// �e�N�X�`��ID

	return S_OK;
}
//<=============================================================
//���f���p�[�e�B�N���̍X�V����
//<=============================================================
void CModParticle::Update(void)
{
	//�������܂������
	if (m_nLife > 0)
	{
		//���������炷
		m_nLife--;
	}
	else
	{//�Ȃ����
		//�I��������
		Uninit();

		return;
	}

	//�ݒ���s��
	Set();
}
//<=============================================================
//���f���p�[�e�B�N���̐ݒ菈��
//<=============================================================
void CModParticle::Set(void)
{
	// ���������G�t�F�N�g�����J��Ԃ�
	for (int nCntPart = 0; nCntPart < NUM_PARTICLE; nCntPart++)
	{ 

	  // �x�N�g���������_���ɐݒ�
		m_move.x = sinf((rand() % 629 - 314) / FLOAT_VALUE) * 1.0f;
		m_move.y = cosf((rand() % 629 - 314) / FLOAT_VALUE) * 1.0f;
		m_move.z = cosf((rand() % 629 - 314) / FLOAT_VALUE) * 1.0f;

		// �x�N�g���������_���ɐݒ�
		m_rot.x = sinf((rand() % 629 - 314) / FLOAT_VALUE) * 1.0f;
		m_rot.y = cosf((rand() % 629 - 314) / FLOAT_VALUE) * 1.0f;
		m_rot.z = cosf((rand() % 629 - 314) / FLOAT_VALUE) * 1.0f;

		// �x�N�g���𐳋K��
		D3DXVec3Normalize(&m_move, &m_move);

		// �ړ��ʂ�ݒ�
		m_move.x *= MOVE_VALUE.x;
		m_move.y *= MOVE_VALUE.y;
		m_move.z *= MOVE_VALUE.z;

		//���f���G�t�F�N�g�𐶐�����
		CModEffect::Create(m_pos, m_rot, m_move, NUM_LIFE,true, m_col, &m_pTexID);
	}
}