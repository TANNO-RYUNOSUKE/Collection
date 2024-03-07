//========================================================================================
//
// �u���b�N
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Block.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"

LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CBlock::CBlock(int nPriority):CObject2D(nPriority)
{
	
}
//=============================================
//�f�X�g���N�^
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CBlock::Init()
{
	CObject2D::Init();
	SetType(CObject::TYPE_BLOCK);

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CBlock::Uninit()
{
	CObject2D::Uninit();
}
//=============================================
//�X�V�֐�
//=============================================
void CBlock::Update()
{
	
	Collision();
}
//=============================================
//�`��֐�
//=============================================
void CBlock::Draw()
{
	CObject2D::Draw();
}
//=============================================
//�����֐�
//=============================================
CBlock * CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock * pBlock = NULL;
	pBlock = DBG_NEW CBlock;
	CBlock::Load();
	pBlock->BindTexture(m_pTexture);
	pBlock->SetPos(pos);
	pBlock->SetWidth(100.0f);
	pBlock->SetHeight(100.0f);

	pBlock->Init();
	return pBlock;
}
//=============================================
//���[�h�֐�
//=============================================
HRESULT CBlock::Load(void)
{
	if (m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
		pDevice = CManager::GetRenderer()->GetDevice();

		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Block000.jpg",
			&m_pTexture);
	}
	else
	{
		return E_FAIL;
	}
	return S_OK;
}
//=============================================
//�A�����[�h�֐�
//=============================================
void CBlock::Unload(void)
{
	//�e�N�X�`���|�C���^�̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================
//�o�C���h�֐�
//=============================================
void CBlock::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	CObject2D::m_pTexture = m_pTexture;
}
//=============================================
//�R���W����
//=============================================
bool CBlock::Collision()
{
	//bool bLand = false;
	//D3DXVECTOR3 BlockPos = GetPos();
	//for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	//{
	//	for (int nCntObj = 0; nCntObj < NUM_OBJECT; nCntObj++)
	//	{
	//		CObject * pObj;
	//		pObj = CObject::GetObject(nCnt, nCntObj);
	//		if (pObj != NULL)
	//		{
	//			if (pObj->GetType() == CObject::TYPE_PLAYER || pObj->GetType() == CObject::TYPE_BULLET)
	//			{
	//				float Height = (GetHeight() / 2) + (pObj->GetHeight() / 2);
	//				float Width = (GetWidth() / 2) + (pObj->GetWidth() / 2);

	//				if (pObj->GetPos().x < BlockPos.x + Width && pObj->GetPos().x > BlockPos.x - Width && pObj->GetPos().y < BlockPos.y + Height && pObj->GetPos().y > BlockPos.y - Height)
	//				{
	//					if (pObj->GetType() == CObject::TYPE_BULLET)
	//					{
	//						pObj->SetLife(0);
	//					}

	//					if (pObj->GetPosOld().y <= BlockPos.y - Height && pObj->GetPos().y > BlockPos.y - Height)
	//					{//�����蔻��A���
	//						pObj->SetMove(D3DXVECTOR3(pObj->GetMove().x, 0.0f, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(pObj->GetPos().x, BlockPos.y - Height, pObj->GetPos().z));
	//						bLand = true;
	//						pObj->SetLand(bLand);
	//					}
	//					else if (pObj->GetPosOld().x >= BlockPos.x + Width && pObj->GetPos().x < BlockPos.x + Width)
	//					{//�����蔻��A�E��
	//						pObj->SetMove(D3DXVECTOR3(0.0f, pObj->GetMove().y, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(BlockPos.x + Width, pObj->GetPos().y, pObj->GetPos().z));
	//					}
	//					else if (pObj->GetPosOld().x <= BlockPos.x - Width && pObj->GetPos().x > BlockPos.y - Width)
	//					{//�����蔻��A����
	//						pObj->SetMove(D3DXVECTOR3(0.0f, pObj->GetMove().y, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(BlockPos.x - Width, pObj->GetPos().y, pObj->GetPos().z));
	//					}
	//					else if (pObj->GetPosOld().y >= BlockPos.y + Height && pObj->GetPos().y < BlockPos.y + Height)
	//					{//�����蔻��A���

	//						pObj->SetMove(D3DXVECTOR3(pObj->GetMove().x, 0.0f, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(pObj->GetPos().x, BlockPos.y + Height, pObj->GetPos().z));

	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//return bLand;
	return true;
}