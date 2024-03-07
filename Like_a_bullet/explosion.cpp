//========================================================================================
//
// �G�N�X�v���[�W����
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Explosion.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CExplosion::CExplosion()
{
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
}
//=============================================
//�f�X�g���N�^
//=============================================
CExplosion::~CExplosion()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CExplosion::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();

	//�J�E���^�[�̏�����
	m_nCountAnim = 0;
	m_nPatternAnim = 0;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_2D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	//���_���W�̐ݒ�
	SetVtx(pVtx);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();
	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}
//=============================================
//�X�V�֐�
//=============================================
void CExplosion::Update()
{
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	m_nCountAnim++;

	m_nPatternAnim = (m_nCountAnim / 4);
	m_nPatternAnim %= 8;

	
	VERTEX_2D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	SetVtx(pVtx);

	pVtx[0].tex = D3DXVECTOR2(((m_nPatternAnim) * 0.125f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((m_nPatternAnim + 1) * 0.125f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(((m_nPatternAnim) * 0.125f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(((m_nPatternAnim + 1) * 0.125f), 1.0f);

	m_pVtxBuff->Unlock();

	if (m_nPatternAnim >= 7)
	{
		CObject::Release();
	}
}
//=============================================
//�`��֐�
//=============================================
void CExplosion::Draw()
{
	CObject2D::Draw();
}
//=============================================
//�����֐�
//=============================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion * pExplosion = NULL;
	pExplosion = DBG_NEW CExplosion;
	pExplosion->Init();
	CExplosion::Load();
	pExplosion->SetPos(pos);
	pExplosion->SetWidth(50.0f);
	pExplosion->SetHeight(50.0f);
	pExplosion->BindTexture(m_pTexture);
	return pExplosion;
}
//=============================================
//���[�h�֐�
//=============================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();
	if (m_pTexture == NULL)
	{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\explosion000.png",
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
void CExplosion::Unload(void)
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
void CExplosion::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	CObject2D::m_pTexture = m_pTexture;
}