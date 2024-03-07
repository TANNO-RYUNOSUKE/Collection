//========================================================================================
//
// �i���o�[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "number.h"
#include "object2D.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//=============================================
//�R���X�g���N�^
//=============================================
CNumber::CNumber()
{
	m_pObbject = NULL;
	m_ndata = 0;
	m_nType = 0;
}



//=============================================
//�f�X�g���N�^
//=============================================
CNumber::~CNumber()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CNumber::Init(void)
{
	m_bDisp = true;
	switch (m_nType)
	{
	case 1:
		m_pObbject = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 6, "data\\TEXTURE\\number003.png");
		break;
	default:
		m_pObbject = CObject2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 6, "data\\TEXTURE\\number002.png");
		break;
	}

	BindTexture(m_pTexture);
	return S_OK;
}
//=============================================
//�����֐�
//=============================================
CNumber * CNumber::Create(int nType)
{
	CNumber * pNumber = NULL;
 	pNumber = DBG_NEW CNumber;
	pNumber->m_nType = nType;
	pNumber->Init();
	return pNumber;
}



//=============================================
//�|���S���̏I������
//=============================================
void CNumber::Uninit(void)
{
	
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CNumber::Update(void)
{
	m_pObbject->SetDisp(m_bDisp);
	LPDIRECT3DVERTEXBUFFER9 * pVtxBuff = m_pObbject->GetBuff();
	VERTEX_2D * pVtx;
	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((0.1f * m_ndata), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((0.1f * m_ndata) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((0.1f * m_ndata), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((0.1f * m_ndata) + 0.1f, 1.0f);	
	m_pObbject->SetVtx(pVtx);

	(*pVtxBuff)->Unlock();
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CNumber::Draw(void)
{
	m_pObbject->Draw();

}
//=============================================
//�ݒ�
//=============================================
void CNumber::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{
	m_pObbject->SetPos(pos);
	m_pObbject->SetRot(rot);
	m_pObbject->SetHeight(fHeight);
	m_pObbject->SetWidth(fWidth);
}
//=============================================
//���[�h�֐�
//=============================================
HRESULT CNumber::Load(void)
{
	if (m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
		pDevice = CManager::GetRenderer()->GetDevice();

		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\number002.png",
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
void CNumber::Unload(void)
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
void CNumber::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	LPDIRECT3DTEXTURE9 * ppTex = m_pObbject->GetTex();
	(*ppTex) = pTex;
}


