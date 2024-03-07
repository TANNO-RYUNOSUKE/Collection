//============================================================
//
//	�f�[�^�ۑ��}�l�[�W���[�w�b�_�[ [retentionManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "input.h"

//************************************************************
//	�}�N����`
//************************************************************
#define MAX_WINPOINT	(8)	// �ő叟���|�C���g
#define MIN_WINPOINT	(1)	// �ŏ������|�C���g

//************************************************************
//	�N���X��`
//************************************************************
// �f�[�^�ۑ��}�l�[�W���[�N���X
class CRetentionManager
{
public:
	// ����������
	enum EKill
	{
		KILL_LIFE = 0,	// �̗͐�
		KILL_KNOCK,		// ������΂���
		KILL_MAX		// ���̗񋓌^�̑���
	};

	// ����������
	enum EWin
	{
		WIN_SURVIVE = 0,	// ������
		WIN_KILL,			// �L����
		WIN_MAX				// ���̗񋓌^�̑���
	};

	// �����L���O��
	enum ERank
	{
		RANK_1ST = 0,	// �����L���O�F���
		RANK_2ND,		// �����L���O�F���
		RANK_3RD,		// �����L���O�F�O��
		RANK_4TH,		// �����L���O�F�l��
		RANK_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CRetentionManager();

	// �f�X�g���N�^
	~CRetentionManager();

	// �\�[�g�\����
	struct SSortData
	{
		int nWinPoint;	// �����|�C���g�ێ���
		int nPlayerID;	// �v���C���[�ԍ�
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��

	void SetKillState(const EKill kill);	// ���������ݒ�
	EKill GetKillState(void) const;			// ���������擾
	void SetWinState(const EWin win);		// ���������ݒ�
	EWin GetWinState(void) const;			// ���������擾
	void SetNumPlayer(const int nNum);		// �v���C�l���ݒ�
	int GetNumPlayer(void) const;			// �v���C�l���擾
	void InitNumSurvival(void);				// �����l��������
	int GetNumSurvival(void) const;			// �����l���擾
	void SetWinPoint(const int nWinPoint);	// �����|�C���g�ݒ�
	int GetWinPoint(void) const;			// �����|�C���g�擾
	void SetWinPlayerID(const int nWinID);	// �����v���C���[ID�ݒ�
	int GetWinPlayerID(void) const;			// �����v���C���[ID�擾
	void InitGame(void);					// �Q�[���J�n���̏�����

	void AllSetEnableEntry(const bool bEntry, const bool bAI);			// �S�G���g���[�󋵐ݒ�
	void SetEntry(const int nID, const bool bEntry, const bool bAI);	// �G���g���[�ݒ�
	bool IsEntry(const int nID) const;	// �G���g���[�󋵎擾
	bool IsAI(const int nID) const;		// AI�󋵎擾
	void EndTutorial(void);				// �`���[�g���A���̏I���ݒ�
	bool IsEndTutorial(void) const;		// �`���[�g���A���̏I���󋵎擾
	void SetFlail(const int nID, const int nFlail);	// �t���C���̎�ސݒ�
	int GetFlail(const int nID) const;				// �t���C���̎�ގ擾

	void InitWinRank(void);						// ���������L���O������
	void SetWinRank(void);						// ���������L���O�ݒ�
	ERank GetWinRank(const int nID);			// ���������L���O�擾
	int GetWinRank1st(void) const;				// ���������L���O��ʃv���C���[�擾
	void InitSurvivalRank(void);				// ���������L���O������
	void SetSurvivalRank(const int nPlayerID);	// ���������L���O�ݒ�
	int CRetentionManager::GetSurvivalRank(const int nRank) const;	// ���������L���O�擾
	int GetPlayerWin(const int nID) const;		// �v���C���[�|�C���g���擾
	int GetPlayerWinOld(const int nID) const;	// �ߋ��v���C���[�|�C���g���擾
	void SetPlayerWinOld(const int nID);		// �ߋ��v���C���[�|�C���g���ݒ�

	// �ÓI�����o�֐�
	static CRetentionManager *Create(void);	// ����
	static HRESULT Release(CRetentionManager *&prRetentionManager);	// �j��

private:
	// �����o�ϐ�
	EKill	m_stateKill;	// ��������
	EWin	m_stateWin;		// ��������
	int		m_nNumPlayer;	// �v���C���[��
	int		m_nNumSurvival;	// �����v���C���[��
	int		m_nWinPoint;	// �����|�C���g��
	int		m_nWinPlayerID;	// �����v���C���[ID
	bool	m_bEndTutorial;	// �`���[�g���A���I����

	int		m_aSurvivalRank[MAX_PLAYER];	// �~���̐��������L���O
	int		m_aWinRank[MAX_PLAYER];			// �~���̏��������L���O
	int		m_aPlayerWin[MAX_PLAYER];		// �v���C���[�|�C���g��
	int		m_aPlayerWinOld[MAX_PLAYER];	// �ߋ��v���C���[�|�C���g��
	int		m_aFlail[MAX_PLAYER];			// �t���C���̎��
	bool	m_aEntry[MAX_PLAYER];			// �G���g���[��
	bool	m_aAI[MAX_PLAYER];				// AI��
};

#endif	// _RETENTION_MANAGER_H_