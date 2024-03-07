//============================================================
//
//	�t���C������ [flail.cpp]
//	Author�F������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "flail.h"
#include "flailEntry.h"
#include "frailResult.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "model.h"
#include "useful.h"
#include "retentionManager.h"
#include "stage.h"
#include "liquid.h"
#include "scrollMeshField.h"
#include "collision.h"
#include "obstacle.h"
#include "block.h"
#include "sound.h"
#include "orbitalParticle.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	PRIORITY	= 3;		// �t���C���̗D�揇��

	const float	RADIUS		= 50.0f;	// ���a
	const int	HIT_DAMAGE	= 10;		// �_���[�W��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CFlail::mc_apModelFileFlail[] =	// ���f���萔(�t���C��)
{
	"data\\MODEL\\FLAIL\\ironBall.x",	// �S��
	"data\\MODEL\\FLAIL\\head.x",		// ��
	"data\\MODEL\\FLAIL\\escapekun.x",	// �G�X�P�[�v�N
	"data\\MODEL\\FLAIL\\apple.x",		// �����S
	"data\\MODEL\\FLAIL\\green_apple.x",// �����S
	"data\\MODEL\\FLAIL\\Duck.x",		// �A�q��
	"data\\MODEL\\FLAIL\\bomb.x",		// ���e
	"data\\MODEL\\FLAIL\\tomato.x",		// ���e
};

const char *CFlail::mc_apModelFileChain[] =	// ���f���萔(��)
{
	"data\\MODEL\\PLAYER\\14_chain.x",	// ��
};

//************************************************************
//	�q�N���X [CFlail] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFlail::CFlail() : CObjectModel(CObject::LABEL_NONE, PRIORITY)
{
	memset(&m_chain[0], 0, sizeof(m_chain));	// ���f���̏��
	m_oldPos = VEC3_ZERO;
	m_move = VEC3_ZERO;
	m_typeFlail = FLAIL_NORMAL;
	m_nNumChain = 0;
	m_nfulChainF = 0;
	m_nfulChainP = 0;
	m_nHitCount = 0;
	m_fChainRot = 0.0f;
	m_fLengthChain = 0.0f;
	m_fLengthTarget = 0.0f;
	m_fChainRotTarget = 0.0f;
	m_fChainRotMove = 0.0f;
	m_bHit = false;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFlail::~CFlail()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFlail::Init(void)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	m_nNumChain = flail::FLAIL_NUM_MAX;

	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		// ���f���̐���
		m_chain[nCntChain].multiModel = CMultiModel::Create(VEC3_ZERO, VEC3_ZERO);

		// ���f��������
		m_chain[nCntChain].multiModel->BindModel(mc_apModelFileChain[CFlail::CHAIN_NORMAL]);
	}

	m_pOrbit = CObjectOrbit::Create(GetPtrMtxWorld(), CObjectOrbit::SOffset(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, -50.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)), 60,60);
	m_pOrbit->BindTexture("data\\TEXTURE\\orbitLine.png");

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFlail::Uninit(void)
{
	if (m_pOrbit != NULL)
	{
		m_pOrbit->Uninit();
		m_pOrbit = NULL;
	}
	
	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		// ���f���̏I��
		m_chain[nCntChain].multiModel->Uninit();
	}

	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFlail::Update(void)
{
	m_oldPos = GetVec3Position();
	CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);
	m_fLengthChain = 0.0f;
	
	m_fChainRotOld = m_fChainRot;

	// �p�x�C��
	useful::NormalizeRot(m_fChainRot);
	useful::NormalizeRot(m_fChainRotTarget);

	// �������鎞�̂݊p�x����
	m_fChainRot += m_fChainRotMove;

	if (D3DXVec3Length(&m_move) > 0.0f && D3DXVec3Length(&m_move) < 5.0f)
	{
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}

	else
	{
		m_nDamage = HIT_DAMAGE;
	}
	// �p�x�C��
	useful::NormalizeRot(m_fChainRot);
	useful::NormalizeRot(m_fChainRotTarget);

	if (m_nPlayerID == 0)
	{
		/*CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "���ڕW�p�x %f\n", m_fChainRotTarget);
		CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "���p�x %f\n", m_fChainRot);
		CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "������ %f\n", m_fLengthChain);
		CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�J�E���^�[]�F%d\n", player->GetCounterFlail());*/
		//CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�p���x]�F%f\n", m_fChainRotMove);
		CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�t���C���ʒu]�F%f %f %f\n", GetVec3Position().x, GetVec3Position().y, GetVec3Position().z);
		//CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�t���C���p�x]�F%f\n", m_fChainRot);
	}

	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update();

	// ���̍X�V
	UpdateChain();

	// �t���C�����m�̓����蔻��J�E���g
	if (m_bHit)
	{
		m_nHitCount++;

		if (m_nHitCount > 60)
		{
			m_bHit = false;
		}
	}
	else
	{
		m_nHitCount = 0;
	}

	// ��]���x�̊����y��
	if (player->GetCounterFlail() == flail::FLAIL_DROP)
	{
		m_fChainRotMove += (0.0f - m_fChainRotMove) * 0.1f;
	}
}

//============================================================
//	�t���C���ʒu�̍X�V����
//============================================================
void CFlail::UpdateFlailPos(void)
{
	CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);

	int partsNum = m_nNumChain - 1;
	D3DXMATRIX partsMtx = m_chain[partsNum].multiModel->GetMtxWorld();
	D3DXVECTOR3 partsPos = D3DXVECTOR3(partsMtx._41, partsMtx._42, partsMtx._43);
	SetVec3PosOrg(partsPos);

	// �p�x�ƒ�������S���̈ʒu����
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();

	if (D3DXVec3Length(&m_move) == 0.0f)
	{
		// �t���C���̏�Ԃɂ���č�����ύX
		if (player->GetCounterFlail() == flail::FLAIL_DROP)
		{
			if (pos.y > -64.0f)
			{
				pos.y -= 8.0f;
			}
			else
			{
				if (m_fLengthTarget <= flail::FLAIL_RADIUS * (m_nNumChain - 1))
				{
					pos.y = CManager::GetInstance()->GetScene()->GetStage()->GetLiquid()->GetScrollMeshField(0)->GetPositionHeight(pos);
				}
			}
		}
		else if (player->GetCounterFlail() < flail::FLAIL_DROP)
		{
			D3DXMATRIX chainMtx = m_chain[0].multiModel->GetMtxWorld();
			D3DXVECTOR3 chainPos = D3DXVECTOR3(chainMtx._41, chainMtx._42, chainMtx._43);

			pos.y = chainPos.y;
		}
		else
		{
			pos.y = m_posOrg.y;
		}
	}

	if (player->GetCounterFlail() < flail::FLAIL_DEF)
	{
		// �ړ��ʌ���
		m_move.x += (0.0f - m_move.x) * 0.15f;
		m_move.z += (0.0f - m_move.z) * 0.15f;
	}
	else
	{
		// �ړ��ʌ���
		m_move.x += (0.0f - m_move.x) * 0.15f;
		m_move.z += (0.0f - m_move.z) * 0.15f;
	}

	// ������Ԃ���Ȃ���΃t���C���̐�[�Ƀt���C�����ړ�
	if (player->GetCounterFlail() != flail::FLAIL_DROP)
	{
		pos.x = m_posOrg.x + (sinf(m_fChainRot) * 1.0f);
		pos.z = m_posOrg.z + (cosf(m_fChainRot) * 1.0f);
	}
	else
	{
		if (m_fChainRotMove < -0.01f || m_fChainRotMove > 0.01f)
		{
			pos.x = m_posOrg.x + (sinf(m_fChainRot) * 1.0f);
			pos.z = m_posOrg.z + (cosf(m_fChainRot) * 1.0f);
		}
	}

	if (player->GetCounterFlail() > flail::FLAIL_DEF)
	{
		D3DXVECTOR3 stickPos;

		stickPos.x = player->GetMultiModel(CPlayer::MODEL_STICK)->GetMtxWorld()._41;
		stickPos.y = player->GetMultiModel(CPlayer::MODEL_STICK)->GetMtxWorld()._42;
		stickPos.z = player->GetMultiModel(CPlayer::MODEL_STICK)->GetMtxWorld()._43;

		rot.y = atan2f(stickPos.x - pos.x, stickPos.z - pos.z);
	}
	else if (player->GetCounterFlail() <= flail::FLAIL_DROP)
	{
		D3DXVECTOR3 stickPos;

		stickPos.x = player->GetMultiModel(CPlayer::MODEL_STICK)->GetMtxWorld()._41;
		stickPos.y = player->GetMultiModel(CPlayer::MODEL_STICK)->GetMtxWorld()._42;
		stickPos.z = player->GetMultiModel(CPlayer::MODEL_STICK)->GetMtxWorld()._43;

		rot.y = atan2f(pos.x - stickPos.x, pos.z - stickPos.z);
	}
	else
	{
		D3DXVECTOR3 stickPos;

		stickPos.x = player->GetMtxWorld()._41;
		stickPos.y = player->GetMtxWorld()._42;
		stickPos.z = player->GetMtxWorld()._43;

		rot.y = atan2f(stickPos.x - pos.x, stickPos.z - pos.z);
	}
	// �����蔻��
	Collision(pos);
	
	SetVec3Position(pos);
	SetVec3Rotation(rot);
}

//============================================================
//	�����t���C���ʒu�̍X�V����
//============================================================
void CFlail::UpdateDropFlailPos(float& rRot)
{
	D3DXVECTOR3 vecPtoF = VEC3_ZERO;
	D3DXVECTOR3 vecPtoFTarget = VEC3_ZERO;
	D3DXVECTOR3 flailPos = VEC3_ZERO;
	float lengthPtoF = 0.0f;
	float lengthPtoFTarget = 0.0f;

	// �t���C���ƃv���C���[�Ԃ̃x�N�g�����v�Z
	vecPtoFTarget.x = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_41 - GetVec3Position().x;
	vecPtoFTarget.y = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_42 - GetVec3Position().y;
	vecPtoFTarget.z = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_43 - GetVec3Position().z;

	vecPtoF.x = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_41 - GetVec3Position().x;
	vecPtoF.z = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_43 - GetVec3Position().z;

	// �t���C���ƃv���C���[�Ԃ̃x�N�g������p�x�v�Z
	rRot = atan2f(vecPtoFTarget.x, vecPtoFTarget.z) + D3DX_PI * 0.5f;

	lengthPtoF = D3DXVec3Length(&vecPtoF);
	lengthPtoFTarget = D3DXVec3Length(&vecPtoFTarget);

	// �t���C���ƃv���C���[�Ԃ̋������ő�l�𒴂��Ă���␳
	if (lengthPtoF > flail::FLAIL_RADIUS * (m_nNumChain - 1))
	{
		lengthPtoF = flail::FLAIL_RADIUS * (m_nNumChain - 1);
	}
	else if (lengthPtoF < 0.0f)
	{
		lengthPtoF = 0.0f;
	}

	if (lengthPtoFTarget < 0.0f)
	{
		lengthPtoFTarget = 0.0f;
	}

	m_fLengthTarget = lengthPtoFTarget;

	// �t���C���̈ʒu��ݒ�
	if (lengthPtoFTarget >= flail::FLAIL_RADIUS * (m_nNumChain - m_nfulChainF - 1))
	{
		flailPos = GetVec3Position();

		flailPos.x = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_41 + (sinf(rRot + D3DX_PI * 0.5f) * lengthPtoF);
		flailPos.z = m_chain[m_nfulChainF].multiModel->GetPtrMtxWorld()->_43 + (cosf(rRot + D3DX_PI * 0.5f) * lengthPtoF);

		SetVec3Position(flailPos);
	}
}

//============================================================
//	���̍X�V����
//============================================================
void CFlail::UpdateChain(void)
{
	CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);

	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		D3DXVECTOR3 pos, rot;
		m_chain[nCntChain].rotOld = m_chain[nCntChain].multiModel->GetVec3Rotation();
		pos = m_chain[nCntChain].multiModel->GetVec3Position();
		m_chain[nCntChain].posOld = m_chain[nCntChain].multiModel->GetVec3Position();
		rot = m_chain[nCntChain].multiModel->GetVec3Rotation();

		// ���݂̃t���C���̒[�𒴂��Ă��鍽�̐ݒ�
		if (m_nNumChain < nCntChain)
		{
			rot.x = 0.0f;
			rot.y = 0.0f;
			rot.z = 0.0f;

			pos.x = 0.0f;
			pos.y = 0.0f;
			pos.z = 0.0f;

			m_chain[nCntChain].multiModel->SetVec3Position(pos);
			m_chain[nCntChain].multiModel->SetVec3Rotation(rot);

			// ���f���̍X�V
			m_chain[nCntChain].multiModel->Update();

			continue;
		}

		// ���ɂ���ď�����ς���
		if (nCntChain == 0)
		{
			// ��]������
			rot.x = 0.0f;
			rot.y = m_fChainRot;
			rot.z = 0.0f;

			pos.x = -1.0f;
			pos.y = 0.0f;
			pos.z = 0.0f;
		}
		else
		{
			int IDParent = nCntChain - 1;

			// �O�̍��̊p�x�ɒǏ]������
			if (nCntChain == 1)
			{
				rot.y = m_chain[IDParent].rotOld.y - m_chain[IDParent].multiModel->GetVec3Rotation().y;
			}
			else
			{
				rot.y = m_chain[IDParent].rotOld.y * 0.7f;
			}

			// �`���[�W��
			if (player->GetCounterFlail() <= flail::FLAIL_CHARGE && player->GetCounterFlail() > flail::FLAIL_DEF)
			{
				// �ЂƂO�̍����L�т����Ă�����
				if ((m_chain[IDParent].multiModel->GetVec3Position().x >= flail::FLAIL_RADIUS && m_fLengthChain < m_fLengthTarget) || nCntChain == 1)
				{
					//�t���C����L�΂�
					pos.x += 10.0f;

					// �����␳
					if (pos.x > flail::FLAIL_RADIUS)
					{
						pos.x = flail::FLAIL_RADIUS;
					}
				}
			}

			// ������
			if (player->GetCounterFlail() == flail::FLAIL_THROW)
			{
				// ��]���x�ɂ���ċ����ύX
				if (m_fChainRotMove == 0.0f)
				{
					// ��]���Ă��Ȃ��Ȃ獽�𓯎��ɐL�΂�
					if ((m_fLengthChain < m_fLengthTarget) || nCntChain == 1)
					{
						pos.x += 0.4f + ((m_fLengthTarget - 700.0f) * 0.0006f);

						if (pos.x > flail::FLAIL_RADIUS)
						{
							pos.x = flail::FLAIL_RADIUS;
						}
					}
				}
				else
				{
					// ��]���Ă�Ȃ珇�ԂɐL�΂�
					if ((m_chain[IDParent].multiModel->GetVec3Position().x >= flail::FLAIL_RADIUS && m_fLengthChain < m_fLengthTarget) || nCntChain == 1)
					{
						pos.x += 10.0f;

						if (pos.x > flail::FLAIL_RADIUS)
						{
							pos.x = flail::FLAIL_RADIUS;
						}
					}
				}
			}

			// �������
			if (player->GetCounterFlail() == flail::FLAIL_DROP)
			{
				// �ꎞ�I�ɂЂ����߂�
				pos.x = 0.0f;

				// �ڕW�����ɓ͂��Ă��Ȃ���΂����܂ŐL�΂�
				if ((m_chain[IDParent].multiModel->GetVec3Position().x >= flail::FLAIL_RADIUS && m_fLengthChain < m_fLengthTarget) || nCntChain == 1)
				{
					pos.x = 20.0f;

					if (pos.x > flail::FLAIL_RADIUS)
					{
						pos.x = flail::FLAIL_RADIUS;
					}
				}
			}

			// �����߂���
			if (player->GetCounterFlail() < flail::FLAIL_DROP)
			{
				// ��[��������߂�
				if (nCntChain < flail::FLAIL_NUM_MAX - 2)
				{
					if (m_chain[nCntChain + 1].multiModel->GetVec3Position().x <= 0.0f || m_chain[nCntChain + 2].multiModel->GetVec3Position().x <= 0.0f)
					{
						float speed = 10.0f;

						if (speed > 20.0f)
						{
							speed = 20.0f;
						}

						pos.x -= speed;

						if (pos.x < 0.0f)
						{
							pos.x = 0.0f;
						}
					}
				}
				else
				{
					if (m_chain[0].multiModel->GetVec3Position().x <= 0.0f)
					{
						float speed = 10.0f;

						if (speed > 20.0f)
						{
							speed = 20.0f;
						}

						pos.x -= speed;

						if (pos.x < 0.0f)
						{
							pos.x = 0.0f;
						}
					}
				}
			}

			if (m_nPlayerID == 0)
			{
				//CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "���ʒu[%d] %f %f %f\n", nCntChain, rot.x, rot.y, rot.z);
			}
		}

		m_chain[nCntChain].multiModel->SetVec3Position(pos);
		m_chain[nCntChain].multiModel->SetVec3Rotation(rot);

		if (nCntChain != 0)
		{
			m_fLengthChain += pos.x;
		}

		// ���f���̍X�V
		m_chain[nCntChain].multiModel->Update();
	}

	D3DXVECTOR3 posCol = VEC3_ZERO;

	CollisionChain(posCol);
}

//============================================================
//	�`�揈��
//============================================================
void CFlail::Draw(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^

	CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);

	D3DXMATRIX mtx, mtxChain;

	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans, *mtxOrg;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX   mtxParent;	// �e�̃}�g���b�N�X
	D3DXVECTOR3 pos, rot, scale;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	mtx._41 = player->GetMultiModel(CPlayer::MODEL_STICK)->GetPtrMtxWorld()->_41;
	mtx._42 = player->GetMultiModel(CPlayer::MODEL_STICK)->GetPtrMtxWorld()->_42;
	mtx._43 = player->GetMultiModel(CPlayer::MODEL_STICK)->GetPtrMtxWorld()->_43;

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

#ifdef ON_STENCIL_PLAYER

	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	
	// ��r�Q�ƒl��ݒ肷��
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	
	// �X�e���V���}�X�N���w�肷�� 
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);

	// �X�e���V����r�֐����w�肷��
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	// �X�e���V�����ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS,	D3DSTENCILOP_REPLACE);	// Z�e�X�g�E�X�e���V���e�X�g����
	pDevice->SetRenderState(D3DRS_STENCILFAIL,	D3DSTENCILOP_KEEP);		// Z�e�X�g�E�X�e���V���e�X�g���s
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,	D3DSTENCILOP_KEEP);		// Z�e�X�g���s�E�X�e���V���e�X�g����

#endif	// ON_STENCIL_PLAYER

	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		int IDParent = nCntChain - 1;
		D3DXVECTOR3 rotOld = m_chain[nCntChain].multiModel->GetVec3Rotation();
		D3DXVECTOR3 rotNow = m_chain[nCntChain].multiModel->GetVec3Rotation();

		if (nCntChain != 0)
		{
			// �����݂��Ⴂ�ɂ���
			if (nCntChain % 2 == 0)
			{
				rotNow.x = -D3DX_PI * 0.5f;
				rotNow.y = 0.0f;
				rotNow.z = 0.0f;
			}
			else if (nCntChain % 2 == 1)
			{
				rotNow.x = D3DX_PI * 0.5f;
				rotNow.y = rotOld.y;
				rotNow.z = 0.0f;
			}

			m_chain[nCntChain].multiModel->SetVec3Rotation(rotNow);
		}
		else
		{
			if (m_fLengthChain != 0)
			{
				// �t���C���̍����ɍ��킹�č��̐�[��������
				float cosRot1, cosRot2, acosRot;

				cosRot1 = m_chain[nCntChain].multiModel->GetMtxWorld()._42 - GetVec3Position().y;
				rotNow.z = 0.0f;

				if (cosRot1 < m_fLengthChain)
				{
					cosRot2 = cosRot1 / m_fLengthChain;
					acosRot = acosf(cosRot2);

					rotNow.z = -(D3DX_PI * 0.5f) + acosRot;
				}
			}

			m_chain[nCntChain].multiModel->SetVec3Rotation(rotNow);
		}

		// �����k�݂����Ă���Ȃ�`�悵�Ȃ�
		if (m_chain[nCntChain].multiModel->GetVec3Position().x == 0.0f)
		{
			pos = m_chain[nCntChain].multiModel->GetVec3Position();
			rot = m_chain[nCntChain].multiModel->GetVec3Rotation();
			scale = m_chain[nCntChain].multiModel->GetVec3Scaling();
			mtxOrg = m_chain[nCntChain].multiModel->GetPtrMtxWorld();

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(mtxOrg);

			// �g�嗦�𔽉f
			D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
			D3DXMatrixMultiply(mtxOrg, mtxOrg, &mtxScale);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(mtxOrg, mtxOrg, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(mtxOrg, mtxOrg, &mtxTrans);

			// �e�}�g���b�N�X��ݒ�
			if (nCntChain == 0)
			{ // �e�����݂��Ȃ��ꍇ

				// ���݂̃}�g���b�N�X���擾
				pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	// �ݒ肳�ꂽ�ŐV�̃}�g���b�N�X (���̂̃}�g���b�N�X)
			}
			else
			{ // �e�����݂���ꍇ

				// �e�̃}�g���b�N�X��ݒ�
				mtxParent = m_chain[IDParent].multiModel->GetMtxWorld();
			}

			// ���[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(mtxOrg, mtxOrg, &mtxParent);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, mtxOrg);
		}
		else
		{
			// ���f���̕`��
			m_chain[nCntChain].multiModel->Draw();
		}

		m_chain[nCntChain].multiModel->SetVec3Rotation(rotOld);
	}

	// ������ԃt���C���̈ʒu�X�V
	if (player->GetCounterFlail() == flail::FLAIL_DROP && m_fChainRotMove > -0.01f && m_fChainRotMove < 0.01f)
	{
		UpdateDropFlailPos(m_fChainRot);
	}

	// �t���C���̈ʒu�X�V
	UpdateFlailPos();

	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw();

#ifdef ON_STENCIL_PLAYER

	// �X�e���V���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

#endif	// ON_STENCIL_PLAYER
}

//============================================================
//	��ނ̐ݒ菈��
//============================================================
void CFlail::SetType(const int nType)
{
	if (nType > NONE_IDX && nType < FLAIL_MAX)
	{
		// ��ނ�ݒ�
		m_typeFlail = (EModelFlail)nType;

		// ���f��������
		BindModel(mc_apModelFileFlail[m_typeFlail]);
	}
	else { assert(false); }
}

//============================================================
//	��ގ擾����
//============================================================
int CFlail::GetType(void) const
{
	return (int)m_typeFlail;
}

//============================================================
//	��������
//============================================================
CFlail *CFlail::Create
( // ����
	CScene::EMode mode,			// ���[�h
	const CPlayer& rPlayer,		// �v���C���[
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXVECTOR3& rScale	// �傫��
)
{
	// �|�C���^��錾
	CFlail *pModelUI = NULL;	// ���f��UI�����p

	if (pModelUI == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// ���[�h�I�[�o�[
		assert(mode > NONE_IDX && mode < CScene::MODE_MAX);

		switch (mode)
		{ // ���[�h���Ƃ̏���
		case CScene::MODE_ENTRY:

			// �������m��
			pModelUI = new CFlailEntry;	// �t���C���G���g���[

			break;

		case CScene::MODE_GAME:

			// �������m��
			pModelUI = new CFlail;	// �t���C��

			break;

		case CScene::MODE_RESULT:

			// �������m��
			pModelUI = new CFlailResult;	// �t���C��

			break;
		}
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pModelUI != NULL)
	{ // �g�p����Ă���ꍇ
		
		// ���f��UI�̏�����
		if (FAILED(pModelUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pModelUI;
			pModelUI = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pModelUI->SetVec3Position(rPos);

		// ������ݒ�
		pModelUI->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pModelUI->SetVec3Scaling(rScale);

		// ���̐e��ݒ�
		pModelUI->BindParent(rPlayer);

		// �t���C���̎�ނ�ݒ�
		pModelUI->SetType(CManager::GetInstance()->GetRetentionManager()->GetFlail(rPlayer.GetPadID()));

		// �m�ۂ����A�h���X��Ԃ�
		return pModelUI;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�����蔻�菈��(�n�ʁA�u���b�N�A��Q��)
//============================================================
void CFlail::Collision(D3DXVECTOR3& rPos)
{
	CPlayer *playerthis = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);
	
	if (playerthis->GetCounterFlail() < flail::FLAIL_DEF || playerthis->GetCounterFlail() == flail::FLAIL_THROW)
	{
		for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
		{
			CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(nCntPlayer);

			if (player != NULL && nCntPlayer != m_nPlayerID && player->GetState() != CPlayer::STATE_DEATH)
			{
				D3DXVECTOR3 vec;
				float length, colLength;

				// �v���C���[�ƃt���C���̃x�N�g�������߂�
				vec = player->GetVec3Position() - GetVec3Position();
				vec.y = 0.0f;	// Y�͖���

				// ���������߂�
				length = D3DXVec3Length(&vec);

				//�t���C���̓����蔻��p���a
				if (playerthis->GetCounterFlail() == flail::FLAIL_DROP)
				{
					colLength = 40.0f + RADIUS + player->GetRadius();
				}
				else
				{
					colLength = 40.0f + (RADIUS + player->GetRadius()) * 0.0015f * m_fLengthChain;
				}

				// ������уx�N�g���𐳋K��
				D3DXVec3Normalize(&vec, &vec);

				// �����Ŕ���
				if (length < colLength)
				{
					float length = D3DXVec3Length(&(rPos - m_oldPos)) + 1.0f;
					int nAddDamage;
					float bonus = 1.0f;
					if (length > 80.0f)
					{
						nAddDamage = 30;
					}
					else if (length > 10.0f)
					{
						nAddDamage = (int)(length * 0.1f) * 3;
					}
					else
					{
						nAddDamage = 0;
					}

					if (playerthis->GetTemporaryItem().type == CPlayer::ITEM_BOOST_KNOCKBACK)
					{
						vec *= 2.0f;
						// �|�C���^��錾
						CRetentionManager *pRetention = CManager::GetInstance()->GetRetentionManager();	// �f�[�^�ۑ����

						if (pRetention->GetKillState() == CRetentionManager::KILL_LIFE)
						{
							vec *= 2.0f;
						}
						else
						{
							vec *= 1.5f;
						}
						
					}

					if (playerthis->GetTemporaryItem().type == CPlayer::ITEM_BOOST_ATTACK)
					{
						bonus = 2.0f;
					}

					// �_���[�W�q�b�g����
					player->HitKnockBack((m_nDamage + nAddDamage) * bonus, vec, playerthis);
				}

				D3DXVECTOR3 posFlail;
				float flailLength;
				posFlail = GetVec3Position() - player->GetFlail()->GetVec3Position();
				posFlail.y = 0;

				flailLength = D3DXVec3Length(&posFlail);

				//�t���C�����m�̓����蔻��
				if (flailLength < RADIUS * 3.0f && (player->GetCounterFlail() < flail::FLAIL_DROP || player->GetCounterFlail() == flail::FLAIL_THROW))
				{
					if (m_bHit == false)
					{
						CorbitalParticle::Create(GetVec3Position(), D3DXVECTOR3(2.5f, 0.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, 6, 600, 20, 20, 300, 1.0f, 0.99f);
					}

					// ��]���ڂ��ւ���
					float rotMove1, rotMove2;
					rotMove1 = GetChainRotMove();
					rotMove2 = player->GetFlail()->GetChainRotMove();

					SetChainRotMove(rotMove2 * 0.8f);
					player->GetFlail()->SetChainRotMove(rotMove1 * 0.8f);

					// ������ԂȂ痎����Ԃɂ���
					if (player->GetCounterFlail() == flail::FLAIL_THROW)
					{
						player->SetCounterFlail(flail::FLAIL_DROP);
						player->SetMotion(CPlayer::MOTION_IDOL);
					}

					m_bHit = true;
				}
			}
		}
	}

	if (playerthis->GetCounterFlail() < flail::FLAIL_DEF || playerthis->GetCounterFlail() == flail::FLAIL_THROW)
	{
		// ��Q���Ƃ̓����蔻��
		if (CollisionObstacle(rPos) ||
			CollisionBlock(CPlayer::AXIS_X, rPos) ||
			CollisionBlock(CPlayer::AXIS_Z, rPos))
		{
			int nParticle = 30;
			
			CorbitalParticle::Create(GetVec3Position(), D3DXVECTOR3(2.5f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f), VEC3_ZERO, VEC3_ZERO, VEC3_ZERO, 6, 300, 20, 20, nParticle, 1.0f, 0.99f);

			for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
			{
				int IDParent = nCntChain - 1;
				D3DXVECTOR3 rot = m_chain[nCntChain].multiModel->GetVec3Rotation();

				// �Փ˂�����p�x���܂������ɒ���
				if (nCntChain == 0)
				{
					
				}
				else if (nCntChain == 1)
				{
					rot.y = m_chain[IDParent].rotOld.y - m_chain[IDParent].multiModel->GetVec3Rotation().y;
				}
				else
				{
					rot.y = m_chain[IDParent].rotOld.y * 0.0f;
				}

				m_chain[nCntChain].multiModel->SetVec3Rotation(rot);
			}

			// �u���b�N�Ɉ����|�����Ă���Ȃ班����������������
			if (m_fLengthTarget > flail::FLAIL_RADIUS * (m_nNumChain - 1) && m_fLengthChain == flail::FLAIL_RADIUS * (m_nNumChain - 1))
			{
				rPos.y += 10.0f;
			}
		}

		// �n�ʂ�Y�ł̓����蔻��
		if (CollisionGround(CPlayer::AXIS_Y, rPos))
		{
			
		}

		// �n�ʂ̑��ʂƂ̓����蔻��
		if (CollisionGround(CPlayer::AXIS_X, rPos) ||
			CollisionGround(CPlayer::AXIS_Z, rPos))
		{
			// �u���b�N�Ɉ����|�����Ă���Ȃ班����������������
			if (m_fLengthTarget > flail::FLAIL_RADIUS * (m_nNumChain - 1) && m_fLengthChain == flail::FLAIL_RADIUS * (m_nNumChain - 1))
			{
				rPos.y += 10.0f;
			}

			// ��]���~�߂�
			m_fChainRotMove *= 0.0f;

			for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
			{
				int IDParent = nCntChain - 1;
				D3DXVECTOR3 rot = m_chain[nCntChain].multiModel->GetVec3Rotation();

				// �Փ˂�����p�x���܂������ɒ���
				if (nCntChain == 0)
				{

				}
				else if (nCntChain == 1)
				{
					rot.y = m_chain[IDParent].rotOld.y - m_chain[IDParent].multiModel->GetVec3Rotation().y;
				}
				else
				{
					rot.y = m_chain[IDParent].rotOld.y * 0.0f;
				}
				m_chain[nCntChain].multiModel->SetVec3Rotation(rot);
			}
		}
	}
}
bool CFlail::CollisionChain(D3DXVECTOR3& rPos)
{
	CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);
	bool bCol = false;

	while (bCol)
	{
		for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
		{ // �D�揇�ʂ̑������J��Ԃ�

		  // �|�C���^��錾
			CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

			if (pObjectTop != NULL)
			{ // �擪�����݂���ꍇ

			  // �|�C���^��錾
				CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

				while (pObjCheck != NULL)
				{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				  // �ϐ���錾
					D3DXVECTOR3 pos = VEC3_ZERO;		// �n�Ոʒu
					D3DXVECTOR3 rot = VEC3_ZERO;		// �n�Ռ���
					D3DXVECTOR3 sizeMin = VEC3_ZERO;	// �n�Սŏ��傫��
					D3DXVECTOR3 sizeMax = VEC3_ZERO;	// �n�Սő�傫��

					// �|�C���^��錾
					CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

					if (pObjCheck->GetLabel() == CObject::LABEL_BLOCK)
					{
						// �ϐ���錾
						pos = pObjCheck->GetVec3Position();

						// �n�Ղ̌�����ݒ�
						rot = pObjCheck->GetVec3Rotation();

						// �n�Ղ̍ŏ��̑傫����ݒ�
						sizeMin = pObjCheck->GetVec3Sizing();
						sizeMin.y *= 2.0f;	// �c�̑傫����{�ɂ���

											// �n�Ղ̍ő�̑傫����ݒ�
						sizeMax = pObjCheck->GetVec3Sizing();
						sizeMax.y = 0.0f;		// �c�̑傫����������
					}
					else if (pObjCheck->GetLabel() == CObject::LABEL_OBSTACLE)
					{
						// �ϐ���錾
						CObstacle::SStatusInfo status;		// ��Q���X�e�[�^�X

															// ��Q���̃X�e�[�^�X��ݒ�
						status = CObstacle::GetStatusInfo(pObjCheck->GetType());

						// ��Q���̌�����ݒ�
						rot = pObjCheck->GetVec3Rotation();

						// ��Q���̈ʒu��ݒ�
						pos = pObjCheck->GetVec3Position();
						pos.x += sinf(rot.y + status.fAngleCenter) * status.fLengthCenter;
						pos.y = 0.0f;
						pos.z += cosf(rot.y + status.fAngleCenter) * status.fLengthCenter;

						// ��Q���̑傫����ݒ�
						sizeMax = status.sizeColl;
						sizeMin = sizeMax * -1.0f;
					}
					else
					{
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;

						continue;
					}

					D3DXVECTOR3 posCorner[4] = {};									//���̊p
					D3DXVECTOR3 posStick = VEC3_ZERO;

					posCorner[0] = collision::PosRelativeMtx(pos, rot, D3DXVECTOR3(sizeMax.x, 0.0f, sizeMax.z));
					posCorner[1] = collision::PosRelativeMtx(pos, rot, D3DXVECTOR3(sizeMin.x, 0.0f, sizeMax.z));
					posCorner[2] = collision::PosRelativeMtx(pos, rot, D3DXVECTOR3(sizeMax.x, 0.0f, sizeMin.z));
					posCorner[3] = collision::PosRelativeMtx(pos, rot, D3DXVECTOR3(sizeMin.x, 0.0f, sizeMin.z));

					posStick.x = player->GetMultiModel(CPlayer::MODEL_STICK)->GetPtrMtxWorld()->_41;
					posStick.y = player->GetMultiModel(CPlayer::MODEL_STICK)->GetPtrMtxWorld()->_42;
					posStick.z = player->GetMultiModel(CPlayer::MODEL_STICK)->GetPtrMtxWorld()->_43;

					for (int nCntCorner = 0; nCntCorner < 4; nCntCorner++)
					{
						D3DXVECTOR3 posDef;
						posDef = posCorner[nCntCorner] - posStick;
						posDef.y = 0.0f;

						if (D3DXVec3Length(&posDef) < m_fLengthChain)
						{
							D3DXVECTOR3 vecFlail, vecFlailOld;
							float rotPoint, rotFlail, rotFlailOld, rotFlailDef;

							vecFlail = GetVec3Position() - posStick;
							vecFlailOld = m_oldPos - posStick;

							rotPoint = atan2f(posDef.x, posDef.z);
							rotFlail = atan2f(vecFlail.x, vecFlail.z);
							rotFlailOld = atan2f(vecFlailOld.x, vecFlailOld.z);

							if (rotFlail > rotFlailOld)
							{
								if (rotFlail < rotPoint && rotFlail >rotFlailOld)
								{

								}
							}
							else
							{
								if (rotFlail < rotPoint && rotFlail >rotFlailOld)
								{

								}
							}

							bCol = true;
						}
					}

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}
	}

	return false;
}
bool CFlail::CollisionGround(const CPlayer::EAxis axis, D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(40.0f, 40.0f, 40.0f);		// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(40.0f, 40.0f, 40.0f);		// �v���C���[�ő�傫��
	bool bMin = false;	// �s�̕����̔����
	bool bMax = false;	// ���̕����̔����
	bool bHit = false;	// ���n�̔�����
	bool bHitBox = false;	// �ڐG�̔�����
	bool bHitBoxCheck = false;	// �ڐG�̔�����

	for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�

	  // �|�C���^��錾
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

		  // �|�C���^��錾
			CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

			  // �ϐ���錾
				D3DXVECTOR3 posGround = VEC3_ZERO;		// �n�Ոʒu
				D3DXVECTOR3 rotGround = VEC3_ZERO;		// �n�Ռ���
				D3DXVECTOR3 sizeMinGround = VEC3_ZERO;	// �n�Սŏ��傫��
				D3DXVECTOR3 sizeMaxGround = VEC3_ZERO;	// �n�Սő�傫��

														// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_GROUND)
				{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

				  // ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �n�Ղ̈ʒu��ݒ�
				posGround = pObjCheck->GetVec3Position();

				// �n�Ղ̌�����ݒ�
				rotGround = pObjCheck->GetVec3Rotation();

				// �n�Ղ̍ŏ��̑傫����ݒ�
				sizeMinGround = pObjCheck->GetVec3Sizing();
				sizeMinGround.y *= 2.0f;	// �c�̑傫����{�ɂ���

											// �n�Ղ̍ő�̑傫����ݒ�
				sizeMaxGround = pObjCheck->GetVec3Sizing();
				sizeMaxGround.y = 0.0f;		// �c�̑傫����������

				switch (axis)
				{ // ���莲���Ƃ̏���
				case CPlayer::AXIS_X:	// X��

								// X���̏Փ˔���
					bHitBox = collision::ResponseSingleX
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posGround,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeMaxGround,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinGround,	// ����ڕW�T�C�Y(���E���E�O)
						&m_move			// �ړ���
					);

					break;

				case CPlayer::AXIS_Y:	// Y��

								// Y���̏Փ˔���
					bHitBox = collision::ResponseSingleY
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posGround,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeMaxGround,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinGround,	// ����ڕW�T�C�Y(���E���E�O)
						&m_move,		// �ړ���
						true,			// X����
						true,			// Z����
						&bMin,			// ������̔���
						&bMax			// �ォ��̔���
					);

					if (bMax)
					{ // �ォ�瓖�����Ă����ꍇ

					  // ���n���Ă���󋵂ɂ���
						bHit = true;
					}

					break;

				case CPlayer::AXIS_Z:	// Z��

								// Z���̏Փ˔���
					bHitBox = collision::ResponseSingleZ
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posGround,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeMaxGround,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinGround,	// ����ڕW�T�C�Y(���E���E�O)
						&m_move			// �ړ���
					);

					break;

				default:	// ��O����
					assert(false);
					break;
				}

				if (bHitBox)
				{
					bHitBoxCheck = true;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	return bHitBoxCheck;
}
bool CFlail::CollisionBlock(const CPlayer::EAxis axis, D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(RADIUS, 0.0f, RADIUS);		// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(RADIUS, 100.0f, RADIUS);	// �v���C���[�ő�傫��
	bool bHit = false;	// ���n�̔�����
	bool bHitCheck = false;	// ���n�̔�����

	for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�

	  // �|�C���^��錾
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

		  // �|�C���^��錾
			CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

			  // �ϐ���錾
				D3DXVECTOR3 posBlock = VEC3_ZERO;	// �u���b�N�ʒu
				D3DXVECTOR3 rotBlock = VEC3_ZERO;	// �u���b�N����
				D3DXVECTOR3 sizeBlock = VEC3_ZERO;	// �u���b�N�傫��

													// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_BLOCK)
				{ // �I�u�W�F�N�g���x�����u���b�N�ł͂Ȃ��ꍇ

				  // ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �u���b�N�̈ʒu��ݒ�
				posBlock = pObjCheck->GetVec3Position();

				// �u���b�N�̌�����ݒ�
				rotBlock = pObjCheck->GetVec3Rotation();

				// �u���b�N�̑傫����ݒ�
				sizeBlock = pObjCheck->GetVec3Sizing();

				switch (axis)
				{ // ���莲���Ƃ̏���
				case CPlayer::AXIS_X:	// X��

								// X���̏Փ˔���
					bHit = collision::ResponseSingleX
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posBlock,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeBlock,		// ����ڕW�T�C�Y(�E�E��E��)
						sizeBlock,		// ����ڕW�T�C�Y(���E���E�O)
						&m_move,		// �ړ���
						false			// Y����
					);

					break;

				case CPlayer::AXIS_Z:	// Z��

								// Z���̏Փ˔���
					bHit = collision::ResponseSingleZ
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posBlock,		// ����ڕW�ʒu
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
						sizeBlock,		// ����ڕW�T�C�Y(�E�E��E��)
						sizeBlock,		// ����ڕW�T�C�Y(���E���E�O)
						&m_move,		// �ړ���
						true,			// X����
						false			// Y����
					);

					break;

				default:	// ��O����
					assert(false);
					break;
				}

				// ��Q���Ƃ̔�������s
				if (bHit)
				{
					// Hit����
					pObjCheck->Hit();

					if (pObjCheck->GetState() == CBlock::BREAK_TRUE)
					{
						m_fChainRotMove *= 0.7f;
					}
					else
					{
						CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);

						m_fChainRotMove *= 0.0f;

						if (player->GetCounterFlail() == flail::FLAIL_THROW)
						{
							player->SetCounterFlail(flail::FLAIL_DROP);
							player->SetMotion(CPlayer::MOTION_IDOL);
						}
					}

					bHitCheck = true;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	// �e���̔������Ԃ�
	return bHitCheck;
}
bool CFlail::CollisionObstacle(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bHit = false;	// ���n�̔�����
	bool bHitBoxCheck = false;	// �ڐG�̔�����

	for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�

	  // �|�C���^��錾
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

		  // �|�C���^��錾
			CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

			  // �ϐ���錾
				CObstacle::SStatusInfo status;		// ��Q���X�e�[�^�X
				D3DXVECTOR3 posObs = VEC3_ZERO;		// ��Q���ʒu
				D3DXVECTOR3 rotObs = VEC3_ZERO;		// ��Q������
				D3DXVECTOR3 sizeObsMin = VEC3_ZERO;	// ��Q���傫��
				D3DXVECTOR3 sizeObsMax = VEC3_ZERO;	// ��Q���傫��

													// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_OBSTACLE)
				{ // �I�u�W�F�N�g���x������Q���ł͂Ȃ��ꍇ

				  // ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// ��Q���̃X�e�[�^�X��ݒ�
				status = CObstacle::GetStatusInfo(pObjCheck->GetType());

				// ��Q���̌�����ݒ�
				rotObs = pObjCheck->GetVec3Rotation();

				// ��Q���̈ʒu��ݒ�
				posObs = pObjCheck->GetVec3Position();
				posObs.x += sinf(rotObs.y + status.fAngleCenter) * status.fLengthCenter;
				posObs.y = 0.0f;
				posObs.z += cosf(rotObs.y + status.fAngleCenter) * status.fLengthCenter;

				// ��Q���̑傫����ݒ�
				sizeObsMax = status.sizeColl;
				sizeObsMin = sizeObsMax * -1.0f;

				// ��Q���Ƃ̔�������s
				if (collision::Square(posObs, &rPos, m_oldPos, rotObs, sizeObsMax, sizeObsMin))
				{
					// HIT����
					pObjCheck->Hit();

					if (pObjCheck->GetState() == CObstacle::BREAK_TRUE)
					{
						m_fChainRotMove *= 0.7f;
					}
					else
					{
						CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);

						m_fChainRotMove *= 0.0f;

						if (player->GetCounterFlail() == flail::FLAIL_THROW)
						{
							player->SetCounterFlail(flail::FLAIL_DROP);
							player->SetMotion(CPlayer::MOTION_IDOL);
						}
					}

					bHitBoxCheck = true;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	// �������Ԃ�
	return bHitBoxCheck;
}

//============================================================
//	�e�q�t���̐ݒ菈��
//============================================================
void CFlail::BindParent(const CPlayer& rPlayer)
{
	int parentID = 0;

	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		if (nCntChain == 0)
		{
			// �e��ݒ�
			m_chain[nCntChain].multiModel->SetParentModel(NULL);
		}
		else
		{
			parentID = nCntChain - 1;

			// �e��ݒ�
			m_chain[nCntChain].multiModel->SetParentModel(m_chain[parentID].multiModel);
		}
	}
	
	parentID = flail::FLAIL_NUM_MAX - 1;
}

//============================================================
//	�ړ��ʂ̐ݒ菈��
//============================================================
void CFlail::SetVec3PosOrg(const D3DXVECTOR3& rPosOrg)
{
	// �����̈ʒu��ݒ�
	m_posOrg = rPosOrg;
}

//============================================================
//	�ړ��ʂ̐ݒ菈��
//============================================================
D3DXVECTOR3 CFlail::GetVec3PosOrg(void)
{
	// �ʒu��Ԃ�
	return m_posOrg;
}

//============================================================
//	�v���C���[�ԍ��̐ݒ菈��
//============================================================
void CFlail::SetPlayerID(const int& rPlayerID)
{
	// �����̃v���C���[�ԍ���ݒ�
	m_nPlayerID = rPlayerID;
}

//============================================================
//	�v���C���[�ԍ��̐ݒ菈��
//============================================================
int CFlail::GetPlayerID(void)
{
	// �v���C���[�ԍ���Ԃ�
	return m_nPlayerID;
}

//============================================================
//	���̐��̐ݒ菈��
//============================================================
void CFlail::SetNumChain(const int& rNumChain)
{
	// �����̍��̐���ݒ�
	m_nNumChain = rNumChain;

	if (m_nNumChain > flail::FLAIL_NUM_MAX)
	{
		m_nNumChain = flail::FLAIL_NUM_MAX;
	}
	else if (m_nNumChain < flail::FLAIL_NUM_MIN)
	{
		m_nNumChain = flail::FLAIL_NUM_MIN;
	}
}

//============================================================
//	���̐��̎擾����
//============================================================
int CFlail::GetNumChain(void)
{
	// ���̐���Ԃ�
	return m_nNumChain;
}

//============================================================
//	�ړ��ʂ̐ݒ菈��
//============================================================
void CFlail::SetMove(const D3DXVECTOR3& rMove)
{
	// �����̈ʒu��ݒ�
	m_move = rMove;
}

//============================================================
//	�ړ��ʂ̎擾����
//============================================================
D3DXVECTOR3 CFlail::GetMove(void)
{
	// �ʒu��Ԃ�
	return m_move;
}

//============================================================
//	�p�x�̐ݒ菈��
//============================================================
void CFlail::SetChainRot(const float& rChainRot)
{
	// �����̊p�x��ݒ�
	m_fChainRot = rChainRot;
}

//============================================================
//	�p�x�̎擾����
//============================================================
float CFlail::GetChainRot(void)
{
	// �p�x��Ԃ�
	return m_fChainRot;
}

//============================================================
//	�ڕW�p�x�̐ݒ菈��
//============================================================
void CFlail::SetChainRotTarget(const float& rChainRotTarget)
{
	// �����̖ڕW�p�x��ݒ�
	m_fChainRotTarget = rChainRotTarget;
}

//============================================================
//	�ڕW�p�x�̎擾����
//============================================================
float CFlail::GetChainRotTarget(void)
{
	// �ڕW�p�x��Ԃ�
	return m_fChainRotTarget;
}

//============================================================
//	�p���x�̐ݒ菈��
//============================================================
void CFlail::SetChainRotMove(const float& rChainRotMove)
{
	// �����̖ڕW�p�x��ݒ�
	m_fChainRotMove = rChainRotMove;
}

//============================================================
//	�p���x�̎擾����
//============================================================
float CFlail::GetChainRotMove(void)
{
	// �ڕW�p�x��Ԃ�
	return m_fChainRotMove;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CFlail::SetLengthChain(const float& rLengthChain)
{
	// �����̒�����ݒ�
	m_fLengthChain = rLengthChain;
}

//============================================================
//	�����̎擾����
//============================================================
float CFlail::GetLengthChain(void)
{
	// ������Ԃ�
	return m_fLengthChain;
}

//============================================================
//	�ڕW�����̐ݒ菈��
//============================================================
void CFlail::SetLengthTarget(const float& rLengthTarget)
{
	// �����̒�����ݒ�
	m_fLengthTarget = rLengthTarget;
}

//============================================================
//	�ڕW�����̎擾����
//============================================================
float CFlail::GetLengthTarget(void)
{
	// ������Ԃ�
	return m_fLengthTarget;
}

//============================================================
//	�����蔻��󋵂̐ݒ菈��
//============================================================
void CFlail::SetHit(const bool& Hit)
{
	// �����̏󋵂�ݒ�
	m_bHit = Hit;
}

//============================================================
//	�����蔻��󋵂̎擾����
//============================================================
bool CFlail::GetHit(void)
{
	// �󋵂�Ԃ�
	return m_bHit;
}

//============================================================
//	�t���C�������擾����
//============================================================
void CFlail::CatchFlail()
{
	CPlayer *player = CManager::GetInstance()->GetScene()->GetPlayer(m_nPlayerID);

	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		D3DXVECTOR3 pos, rot;
		pos = m_chain[nCntChain].multiModel->GetVec3Position();
		rot = m_chain[nCntChain].multiModel->GetVec3Rotation();
		m_chain[nCntChain].rotOld = m_chain[nCntChain].multiModel->GetVec3Rotation();
		m_chain[nCntChain].posOld = m_chain[nCntChain].multiModel->GetVec3Position();

		pos = VEC3_ZERO;

		if (nCntChain == 0)
		{
			rot = VEC3_ZERO;
		}
		else
		{
			int IDParent = nCntChain - 1;

			if (nCntChain == 1)
			{
				rot.y = m_chain[IDParent].rotOld.y - m_chain[IDParent].multiModel->GetVec3Rotation().y;
			}
			else
			{
				rot.y = m_chain[IDParent].rotOld.y * 1.0f;
			}
		}

		m_chain[nCntChain].multiModel->SetVec3Position(pos);
		m_chain[nCntChain].multiModel->SetVec3Rotation(rot);

		// ���f���̍X�V
		m_chain[nCntChain].multiModel->Update();
	}

	m_fChainRot = 0.0f;
	//m_fLengthChain = 0.0f;
	//m_fLengthTarget = 0.0f;
	//m_fChainRotTarget = 0.0f;
	m_fChainRotMove = 0.0f;

	//player->SetCounterFlail(flail::FLAIL_DEF);
}

//============================================================
//	�t���C�������o������
//============================================================
void CFlail::ShotFlail(const float rot)
{
	m_fChainRot = rot;
	m_fChainRotMove = 0.0f;

	for (int nCntChain = 0; nCntChain < flail::FLAIL_NUM_MAX; nCntChain++)
	{
		D3DXVECTOR3 pos, rotChain;
		pos = m_chain[nCntChain].multiModel->GetVec3Position();
		rotChain = m_chain[nCntChain].multiModel->GetVec3Rotation();
		m_chain[nCntChain].rotOld = m_chain[nCntChain].multiModel->GetVec3Rotation();
		m_chain[nCntChain].posOld = m_chain[nCntChain].multiModel->GetVec3Position();

		if (nCntChain == 0)
		{
			pos = VEC3_ZERO;
			rotChain = VEC3_ZERO;

			rotChain.y = m_fChainRot;
		}
		else
		{
			int IDParent = nCntChain - 1;

			if (nCntChain == 1)
			{
				rotChain.y = 0.0f;
			}
			else
			{
				rotChain.y = 0.0f;
			}
		}

		m_chain[nCntChain].multiModel->SetVec3Position(pos);
		m_chain[nCntChain].multiModel->SetVec3Rotation(rotChain);

		// ���f���̍X�V
		m_chain[nCntChain].multiModel->Update();
	}
}

//============================================================
//	�O�Ղ̏�����
//============================================================
void CFlail::InitOrbit(void)
{
	// �O�Ղ�ʏ��Ԃɂ���
	m_pOrbit->SetState(CObjectOrbit::STATE_NORMAL);
}

//============================================================
//	�O�Ղ̏����ݒ�
//============================================================
void CFlail::VanishOrbit(void)
{
	// �O�Ղ�������Ԃɂ���
	m_pOrbit->SetState(CObjectOrbit::STATE_VANISH);
}