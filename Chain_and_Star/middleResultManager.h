//============================================================
//
//	���ԃ��U���g�}�l�[�W���[�w�b�_�[ [middleResultManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MIDDLE_RESULT_MANAGER_H_
#define _MIDDLE_RESULT_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "input.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CValueUI;		// ����UI�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���ԃ��U���g�}�l�[�W���[�N���X
class CMiddleResultManager
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_FADE = 0,		// �t�F�[�h�e�N�X�`��
		TEXTURE_TITLE,			// �����L���O�^�C�g���e�N�X�`��
		TEXTURE_WIN,			// �����|�C���g�^�C�g���e�N�X�`��
		TEXTURE_PLAYER,			// �v���C���[�e�N�X�`��
		TEXTURE_PLAYER_POINT,	// �����|�C���g�e�N�X�`��
		TEXTURE_FRAME,			// �t���[���e�N�X�`��
		TEXTURE_CONTROL,		// ������@�e�N�X�`��
		TEXTURE_MAX				// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_FADEIN = 0,		// �t�F�[�h�C�����
		STATE_FADEIN_WAIT,		// �t�F�[�h�C���ҋ@���
		STATE_FADEIN_ACCEL,		// �t�F�[�h�C���������
		STATE_SCALELINE_WAIT,	// �����̊g��ҋ@���
		STATE_SCALELINE,		// �����̊g��\�����
		STATE_RANK_TITLE_WAIT,	// �����L���O�^�C�g���ҋ@���
		STATE_RANK_TITLE,		// �����L���O�^�C�g���\�����
		STATE_FRAME_WAIT,		// �v���C���[�t���[���ҋ@���
		STATE_FRAME,			// �v���C���[�t���[���\�����
		STATE_PLAYERPOINT_WAIT,	// �v���C���[�����|�C���g�ҋ@���
		STATE_PLAYERPOINT,		// �v���C���[�����|�C���g�\�����
		STATE_WAIT,				// �ҋ@���
		STATE_FADEOUT,			// �t�F�[�h�A�E�g���
		STATE_FADEOUT_WAIT,		// �t�F�[�h�A�E�g�ҋ@���
		STATE_FADEOUT_ACCEL,	// �t�F�[�h�A�E�g�������
		STATE_END,				// �I�����
		STATE_MAX				// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CMiddleResultManager();

	// �f�X�g���N�^
	~CMiddleResultManager();

	// �����o�֐�
	HRESULT Init(void);			// ������
	HRESULT Uninit(void);		// �I��
	void Update(void);			// �X�V
	void SetResultData(void);	// ���U���g���ݒ�

	// �ÓI�����o�֐�
	static CMiddleResultManager *Create(void);	// ����
	static HRESULT Release(CMiddleResultManager *&prMiddleResultManager);	// �j��

private:
	// �����o�ϐ�
	void UpdateFadeIn(void);			// �t�F�[�h�C���X�V
	void UpdateFadeInWait(void);		// �t�F�[�h�C���ҋ@�X�V
	void UpdateFadeInAccel(void);		// �t�F�[�h�C�������X�V

	void UpdateScaleLineWait(void);		// �����̊g��ҋ@�X�V
	void UpdateScaleLine(void);			// �����̊g��\���X�V
	void UpdateRankTitleWait(void);		// �����L���O�^�C�g���ҋ@�X�V
	void UpdateRankTitle(void);			// �����L���O�^�C�g���\���X�V

	void UpdateFrameWait(void);			// �v���C���[�t���[���ҋ@�X�V
	void UpdateFrame(void);				// �v���C���[�t���[���\���X�V
	void UpdatePlayerPointWait(void);	// �v���C���[�����|�C���g�ҋ@�X�V
	void UpdatePlayerPoint(void);		// �v���C���[�����|�C���g�\���X�V
	void UpdateWait(void);				// �ҋ@�X�V
	void UpdateFadeOut(void);			// �t�F�[�h�A�E�g�X�V
	void UpdateFadeOutWait(void);		// �t�F�[�h�A�E�g�ҋ@�X�V
	void UpdateFadeOutAccel(void);		// �t�F�[�h�A�E�g�����X�V

	void UpdateTransition(void);	// �J�ڌ���
	void SkipStaging(void);			// ���o�X�L�b�v
	void MovePositionAll(const D3DXVECTOR3& rAddMove);	// �S�ʒu�̈ړ�

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];	// �e�N�X�`���萔

	// �����o�ϐ�
	CObject2D	*m_pFade;		// �t�F�[�h�̏��
	CObject2D	*m_pControl;	// ����̏��
	CObject2D	*m_pTitle;		// �^�C�g���̏��
	CObject2D	*m_pWinPointBG;	// �����|�C���g�̔w�i���
	CValueUI	*m_pWinPoint;	// �����|�C���g�̏��
	CValueUI	*m_apNumber[MAX_PLAYER];			// �v���C���[�i���o�[�̏��
	CValueUI	*m_apPlayerWinPoint[MAX_PLAYER];	// �v���C���[�����|�C���g�̏��
	CObject2D	*m_apFrame[MAX_PLAYER];				// �v���C���[�t���[���̏��

	EState	m_state;			// ���
	int		m_nCounterState;	// ��ԊǗ��J�E���^�[
	float	m_fMoveY;			// �c�ړ���
	float	m_fScale;			// �g�嗦
	float	m_fSinAlpha;		// ��������
};

#endif	// _MIDDLE_RESULT_MANAGER_H_