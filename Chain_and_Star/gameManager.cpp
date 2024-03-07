//============================================================
//
//	�Q�[���}�l�[�W���[���� [gameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "sound.h"
#include "scene.h"
#include "sceneGame.h"
#include "camera.h"
#include "player.h"
#include "retentionManager.h"
#include "middleResultManager.h"
#include "pause.h"

#include "editStageManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	WAIT_RESULT_FRAME = 210;	// �Q�[����ʂ���Q�[�������U���g��ʂɈړ�����ۂ̗]�C�t���[��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CMiddleResultManager	*CGameManager::m_pMiddleResult	= NULL;	// ���ԃ��U���g�̏��
CEditStageManager		*CGameManager::m_pEditStage		= NULL;	// �G�f�B�b�g�X�e�[�W�̏��

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager()
{
	// �����o�ϐ����N���A
	m_state = STATE_NONE;	// ���
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[
}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameManager::Init(void)
{
	// �����o�ϐ���������
	m_state = STATE_READY;	// ���
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[

	// �����l����������
	CManager::GetInstance()->GetRetentionManager()->InitNumSurvival();

	// ���������L���O��������
	CManager::GetInstance()->GetRetentionManager()->InitSurvivalRank();

	if (CManager::GetInstance()->GetRetentionManager()->IsEndTutorial())
	{
		// �J�n��Ԃɂ���
		m_state = STATE_READY;

		// �J�n���o�̐���
		m_pReady = CReady::Create();
	}
	else
	{
		// �J�n���o���΂�
		m_state = STATE_NORMAL;

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{ // �v���C���[�����J��Ԃ�

			CPlayer *pPlayer = CScene::GetPlayer(nCntPlayer);	// �v���C���[���

			if (pPlayer != NULL)
			{ // �v���C���[�����݂���ꍇ

				// �v���C���[���o��
				pPlayer->SetSpawn();
			}
		}
	}

	if (m_pMiddleResult == NULL)
	{ // ���ԃ��U���g���g�p����Ă��Ȃ��ꍇ

		// ���ԃ��U���g�̐���
		m_pMiddleResult = CMiddleResultManager::Create();
		if (m_pMiddleResult == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else { assert(false); }	// �g�p�ς�

#if _DEBUG

	if (m_pEditStage == NULL)
	{ // �G�f�B�b�g�X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �G�f�B�b�g�X�e�[�W�̐���
		m_pEditStage = CEditStageManager::Create();
		if (m_pEditStage == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else { assert(false); }	// �g�p�ς�

#endif	// _DEBUG

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit(void)
{
	if (m_pMiddleResult != NULL)
	{ // ���ԃ��U���g���g�p����Ă���ꍇ

		// ���ԃ��U���g�̔j��
		CMiddleResultManager::Release(m_pMiddleResult);
	}

	if (m_pEditStage != NULL)
	{ // �G�f�B�b�g�X�e�[�W���g�p����Ă���ꍇ

		// �G�f�B�b�g�X�e�[�W�̔j��
		CEditStageManager::Release(m_pEditStage);
	}
}

//============================================================
//	�X�V����
//============================================================
void CGameManager::Update(void)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_READY:
		break;

	case STATE_NORMAL:

		if (!CSceneGame::GetPause()->IsPause())
		{ // �|�[�Y���ł͂Ȃ��ꍇ

			if (CManager::GetInstance()->GetRetentionManager()->GetNumSurvival() <= 0)
			{ // �����c�肪���Ȃ��ꍇ

				// �J�E���^�[�����Z
				m_nCounterState++;

				if (m_nCounterState >= WAIT_RESULT_FRAME)
				{ // �]�C���o�߂����ꍇ

					if (CManager::GetInstance()->GetRetentionManager()->GetWinState() == CRetentionManager::WIN_SURVIVE)
					{
						// ������ID��ݒ�
						CManager::GetInstance()->GetRetentionManager()->SetWinPlayerID(CManager::GetInstance()->GetRetentionManager()->GetSurvivalRank(CRetentionManager::RANK_1ST));
					}
					else if (CManager::GetInstance()->GetRetentionManager()->GetWinState() == CRetentionManager::WIN_KILL)
					{
						// ��r�p�ϐ��ǉ�
						int winPlayer = -1;
						int playerpoint = 0;
						int MaxPoint = 0;

						for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
						{
							playerpoint = CManager::GetInstance()->GetRetentionManager()->GetPlayerWin(nCntPlayer) - CManager::GetInstance()->GetRetentionManager()->GetPlayerWinOld(nCntPlayer);

							if (playerpoint > MaxPoint)
							{
								winPlayer = nCntPlayer;
								MaxPoint = playerpoint;
							}

							CManager::GetInstance()->GetRetentionManager()->SetPlayerWinOld(nCntPlayer);
						}

						// ������ID��ݒ�
						CManager::GetInstance()->GetRetentionManager()->SetWinPlayerID(winPlayer);
					}

					// ���U���g����ݒ�
					m_pMiddleResult->SetResultData();

					// �J�E���^�[��������
					m_nCounterState = 0;

					// ���U���g�Ɉڍs
					m_state = STATE_RESULT;

					// �T�E���h�̍Đ�
					CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_WIND_001);	// ����01
				}
			}
		}

		break;

	case STATE_RESULT:

		if (m_pMiddleResult != NULL)
		{ // ���ԃ��U���g���g�p����Ă���ꍇ

			// ���ԃ��U���g�̍X�V
			m_pMiddleResult->Update();
		}

		break;

	case STATE_END:
		break;

	default:	// ��O����
		assert(false);
		break;
	}

	if (m_pEditStage != NULL)
	{ // �G�f�B�b�g�X�e�[�W���g�p����Ă���ꍇ

		// �G�f�B�b�g�X�e�[�W�̍X�V
		m_pEditStage->Update();
	}
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CGameManager::SetState(const EState state)
{
	if (state > NONE_IDX && state < STATE_MAX)
	{ // �͈͓��̏ꍇ

		// ��Ԃ�ݒ�
		m_state = state;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	��Ԏ擾����
//============================================================
CGameManager::EState CGameManager::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	��������
//============================================================
CGameManager *CGameManager::Create(void)
{
	// �|�C���^��錾
	CGameManager *pGameManager = NULL;	// �Q�[���}�l�[�W���[�����p

	if (pGameManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pGameManager = new CGameManager;	// �Q�[���}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pGameManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �Q�[���}�l�[�W���[�̏�����
		if (FAILED(pGameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pGameManager;
			pGameManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pGameManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CGameManager::Release(CGameManager *&prGameManager)
{
	if (prGameManager != NULL)
	{ // �g�p���̏ꍇ

		// �Q�[���}�l�[�W���[�̏I��
		prGameManager->Uninit();

		// �������J��
		delete prGameManager;
		prGameManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	���ԃ��U���g�擾����
//============================================================
CMiddleResultManager * CGameManager::GetMiddleResult(void)
{
	// ���ԃ��U���g��Ԃ�
	return m_pMiddleResult;
}

//============================================================
//	�G�f�B�b�g�X�e�[�W�擾����
//============================================================
CEditStageManager *CGameManager::GetEditStage(void)
{
	// �G�f�B�b�g�X�e�[�W�̏���Ԃ�
	return m_pEditStage;
}