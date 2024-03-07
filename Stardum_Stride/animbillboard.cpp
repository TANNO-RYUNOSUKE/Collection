//========================================================================================
//
// �A�j���[�V�����r���{�[�h
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object3D.h"
#include "manager.h"
#include "AnimBillboard.h"
#include "texture.h"

//=============================================
//�R���X�g���N�^
//=============================================

CAnimBillboard::CAnimBillboard(int nPriority) : CBillboard(nPriority)
{
	m_nH_Key = 1;
	m_nW_Key = 1;

	m_nNumKey = 1;
	m_nCurrentKey = 0;
	m_fFlameCount = 0.f;
	m_nFlameRate = 1;
	m_bLoop = false;
}



//=============================================
//�f�X�g���N�^
//=============================================
CAnimBillboard::~CAnimBillboard()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CAnimBillboard::Init(void)
{
	CBillboard::Init();
	SetAnim();
	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CAnimBillboard * CAnimBillboard::Create(float fHeight, float fWidth, int nH_Key, int nW_Key, int nNumKey, int nFlame, bool bLoop, D3DXVECTOR3 pos, char * pName )
{
	CAnimBillboard * pObject3D = NULL;

	pObject3D = DBG_NEW CAnimBillboard;
	if (pName != NULL)
	{
		CTexture * pTex = CManager::GetInstance()->GetTexture();

		pObject3D->m_nIdxTex[0] = pTex->Regist(pName);
	}

	pObject3D->SetHeight(fHeight);
	pObject3D->SetWidth(fWidth);
	pObject3D->m_nH_Key = nH_Key;
	pObject3D->m_nW_Key = nW_Key;
	pObject3D->m_nNumKey = nNumKey;
	pObject3D->m_nFlameRate = nFlame;
	pObject3D->m_bLoop = bLoop;
	pObject3D->SetPos(pos);
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CAnimBillboard::Uninit(void)
{

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CAnimBillboard::Update(void)
{
	SetAnim();
	m_fFlameCount+=1.0f;
	if (60.0f / m_nFlameRate < m_fFlameCount)
	{
		m_fFlameCount -= 60.0f / m_nFlameRate;
		m_nCurrentKey++;
	}
	if (m_nCurrentKey >= m_nNumKey)
	{
		if (m_bLoop)
		{
			m_nCurrentKey = 0;

		}
		else
		{
			Release();
		}
	}
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CAnimBillboard::Draw(void)
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CBillboard::Draw();
	//a�u�����f�B���O��ʏ�ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
void CAnimBillboard::SetAnim()
{
	// �ϐ���錾
	float fWidthRate = 1.0f / m_nW_Key;		// ���̕������̊���
	float fHeightRate = 1.0f / m_nH_Key;		// �c�̕������̊���
	int nWidthCurrent = m_nCurrentKey % m_nW_Key;					// ���݂̉��̃p�^�[��
	int nHeightCurrent = (m_nCurrentKey / m_nW_Key) % m_nH_Key;	// ���݂̏c�̃p�^�[��
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-GetWidth(), +GetHeight(), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+GetWidth(), +GetHeight(), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-GetWidth(), -GetHeight(), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+GetWidth(), -GetHeight(), 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(fWidthRate *  nWidthCurrent, fHeightRate *  nHeightCurrent);
	pVtx[1].tex = D3DXVECTOR2(fWidthRate * (nWidthCurrent + 1), fHeightRate *  nHeightCurrent);
	pVtx[2].tex = D3DXVECTOR2(fWidthRate *  nWidthCurrent, fHeightRate * (nHeightCurrent + 1));
	pVtx[3].tex = D3DXVECTOR2(fWidthRate * (nWidthCurrent + 1), fHeightRate * (nHeightCurrent + 1));

	//���_�J���[�̐ݒ�
	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	m_pVtxBuff->Unlock();
}