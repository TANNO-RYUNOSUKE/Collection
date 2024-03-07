//========================================================================================
//
// �w�i
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "bg.h"

//=============================================
//�R���X�g���N�^
//=============================================
CBg::CBg()
{
	 m_pVtxBuff = NULL;		
	 for (int nCnt = 0; nCnt < NUM_BG; nCnt++)
	 {
		 m_apTexture[nCnt] = NULL;
		 m_aTexUV[nCnt] = D3DXVECTOR2(0.0f, 0.0f);
	 }
	 

}
//=============================================
//�f�X�g���N�^
//=============================================
CBg::~CBg()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CBg::Init()
{
	

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	int nCntBG;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\moon1.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\moon2.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\moon3.png", &m_apTexture[2]);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_2D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		m_aTexUV[nCntBG] = D3DXVECTOR2(0.0f,0.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

		pVtx += 4;
	}
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CBg::Uninit()
{
	int nCntBG;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{

		if (m_apTexture[nCntBG] != NULL)
		{
			m_apTexture[nCntBG]->Release();
			m_apTexture[nCntBG] = NULL;
		}
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CBg::Update()
{
	int nCntBG;
	VERTEX_2D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		m_aTexUV[nCntBG].x += 0.0005f * nCntBG;

		if (m_aTexUV[nCntBG].x >= 1.0f)
		{
			m_aTexUV[nCntBG].x = 0.0f;
		}
		if (m_aTexUV[nCntBG].x < -1.0f)
		{
			m_aTexUV[nCntBG].x = 0.0f;
		}

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(m_aTexUV[nCntBG].x, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_aTexUV[nCntBG].x + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_aTexUV[nCntBG].x, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_aTexUV[nCntBG].x + 1.0f, 1.0f);

		pVtx += 4;
	}

	m_pVtxBuff->Unlock();
}
//=============================================
//�`��֐�
//=============================================
void CBg::Draw()
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_apTexture[nCntBG]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}

}
//=============================================
//�����֐�
//=============================================
CBg * CBg::Create(void)
{
	CBg * pBG = NULL;
	pBG = DBG_NEW CBg;
	pBG->Init();
	return pBG;
}