//========================================================================================
//
// 3D���f��(�K�w�\��)
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "model.h"
#include "manager.h"
#include "texture.h"
#include "xfile.h"
#include "ZTexture.h"
#include "DepthShadow.h"
//=============================================
//�R���X�g���N�^
//=============================================

CModel::CModel() 
{
	m_pIdxTex = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	m_dwNumMat = 0;
	
	m_pModelName = {};
	m_pBuffMat = NULL;
	m_pParent = NULL;
	m_pMesh = NULL;
}



//=============================================
//�f�X�g���N�^
//=============================================
CModel::~CModel()
{

}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CModel::Init(void)
{
	m_Col = {};
	int nNumVtx = 0; //���_��
	DWORD dwSizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff = NULL; //���_�o�b�t�@�ւ̃|�C���^
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();


	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CXFile * pXFile = CManager::GetInstance()->GetXFiles();
	m_nIdxXFile = pXFile->Regist(m_pModelName);
	//x�t�@�C���̓ǂݍ���
	/*if (D3DXLoadMeshFromX(m_pModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh) != D3D_OK)
	{
		return E_FAIL;
	}*/

	//���_�����擾
	nNumVtx = pXFile->GetAddress(m_nIdxXFile)->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(pXFile->GetAddress(m_nIdxXFile)->GetFVF());

	//���_�o�b�t�@�����b�N
	pXFile->GetAddress(m_nIdxXFile)->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_vtxMinModel.x > vtx.x)
		{
			m_vtxMinModel.x = vtx.x;
		}
		if (m_vtxMinModel.y > vtx.y)
		{
			m_vtxMinModel.y = vtx.y;
		}
		if (m_vtxMinModel.z > vtx.z)
		{
			m_vtxMinModel.z = vtx.z;
		}
		if (m_vtxMaxModel.x < vtx.x)
		{
			m_vtxMaxModel.x = vtx.x;
		}
		if (m_vtxMaxModel.y < vtx.y)
		{
			m_vtxMaxModel.y = vtx.y;
		}
		if (m_vtxMaxModel.z < vtx.z)
		{
			m_vtxMaxModel.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;
	}
	//���_�o�b�t�@���A�����b�N
	pXFile->GetAddress(m_nIdxXFile)->UnlockVertexBuffer();

	//�e�N�X�`���̓ǂݍ���

	m_pIdxTex = DBG_NEW  int[(int)pXFile->GetNumMaterial(m_nIdxXFile)];
	
	D3DXMATERIAL *pMat; //�}�e���A���f�[�^�ւ̃|�C���^
	pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		m_pIdxTex[nCntMat] = -1;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂��鎞
			m_pIdxTex[nCntMat] = pTex->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CModel * CModel::Create( char * pModelName)
{
	CModel * pObject3D = NULL;
	pObject3D = DBG_NEW  CModel();
	pObject3D->m_pModelName = pModelName;
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CModel::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�e�N�X�`���̔j��
	if (m_pIdxTex != NULL)
	{
		delete[] m_pIdxTex;
		m_pIdxTex = NULL;
	}

}

//=============================================
//�|���S���̍X�V����
//=============================================
void CModel::Update(void)
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CModel::Draw(void)
{

	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CXFile * pXFile = CManager::GetInstance()->GetXFiles();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DXMATRIX mtxParent;
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat = NULL; //�}�e���A���f�[�^�ւ̃|�C���^

	
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
	//���[���h�}�g���N�X�̐ݒ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�Z�o�����}�g���N�X���������킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	if (pXFile->GetMaterial(m_nIdxXFile) != NULL)
	{
		pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();

	}

	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		//if (nCntMat == 1)
		//{
		//	D3DMATERIAL9 mat;
		//	ZeroMemory(&mat, sizeof(D3DMATERIAL9));
		//	mat.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̊g�U�F�i���F�j
		//	mat.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̊��F�i���F�j
		//	mat.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̋��ʔ��ːF�i���F�j
		//	mat.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); // �}�e���A���̎��Ȕ����F�i���F�j
		//	mat.Power = 32.0f; // �}�e���A���̋��ʔ��˂̋���

		//	pDevice->SetMaterial(&mat);
		//}
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		D3DCOLORVALUE Color = pMat[nCntMat].MatD3D.Diffuse;
	
			
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTex->Getaddress(m_pIdxTex[nCntMat]));

		if (CManager::GetInstance()->GetRenderer()->GetZShader()->GetbPass())
		{
			CManager::GetInstance()->GetRenderer()->GetZShader()->SetWorldMatrix(&m_mtxWorld);
			CManager::GetInstance()->GetRenderer()->GetZShader()->SetParamToEffect();
			CManager::GetInstance()->GetRenderer()->GetZShader()->BeginPass();
		}
		else if (CManager::GetInstance()->GetRenderer()->GetDepthShader()->GetbPass())
		{
			CManager::GetInstance()->GetRenderer()->GetDepthShader()->SetWorldMatrix(&m_mtxWorld);
			CManager::GetInstance()->GetRenderer()->GetDepthShader()->SetAmbient(&(D3DXCOLOR)Color);
			CManager::GetInstance()->GetRenderer()->GetDepthShader()->SetParamToEffect();
			CManager::GetInstance()->GetRenderer()->GetDepthShader()->BeginPass();
		}

		//���f��(�p�[�c)�̕`��
		pXFile->GetAddress(m_nIdxXFile)->DrawSubset(nCntMat);

		if (CManager::GetInstance()->GetRenderer()->GetZShader()->GetbPass())
		{
			CManager::GetInstance()->GetRenderer()->GetZShader()->EndPass();
		}
		else if (CManager::GetInstance()->GetRenderer()->GetDepthShader()->GetbPass())
		{
			CManager::GetInstance()->GetRenderer()->GetDepthShader()->EndPass();
		}

		//m_pMesh->DrawSubset(nCntMat);
		
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);


}



CAfterImage::CAfterImage()
{

}



//=============================================
//�f�X�g���N�^
//=============================================
CAfterImage::~CAfterImage()
{

}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CAfterImage::Init(void) 
{
	CModel::Init();

	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CAfterImage * CAfterImage::Create(char * pModelName, D3DXMATRIX mtx, D3DXCOLOR col, int nLife)
{
	CAfterImage * pObject3D = NULL;
	pObject3D = DBG_NEW  CAfterImage();
	pObject3D->m_nLife = nLife;
	pObject3D->m_pModelName = pModelName;
	pObject3D->m_Mtx = mtx;
	
	pObject3D->Init();
	pObject3D->m_Col = col;
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CAfterImage::Uninit(void)
{
	CModel::Uninit();
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CAfterImage::Update(void)
{
	m_nLife--;
	m_Col.a -= m_Col.a / m_nLife;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CAfterImage::Draw(void)
{


	CTexture * pTex = CManager::GetInstance()->GetTexture();
	CXFile * pXFile = CManager::GetInstance()->GetXFiles();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X
	D3DXMATRIX mtxParent;
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat = NULL; //�}�e���A���f�[�^�ւ̃|�C���^


	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Mtx);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	if (pXFile->GetMaterial(m_nIdxXFile) != NULL)
	{
		pMat = (D3DXMATERIAL*)pXFile->GetMaterial(m_nIdxXFile)->GetBufferPointer();

	}

	for (int nCntMat = 0; nCntMat < (int)pXFile->GetNumMaterial(m_nIdxXFile); nCntMat++)
	{
		
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		D3DCOLORVALUE Color = pMat[nCntMat].MatD3D.Diffuse;
		D3DCOLORVALUE Emissive = pMat[nCntMat].MatD3D.Emissive;
		//�}�e���A���̐ݒ�
		if (m_Col.a > 0.0f)
		{
			pMat[nCntMat].MatD3D.Diffuse = m_Col;
			pMat[nCntMat].MatD3D.Emissive = m_Col * 0.5f;

			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			
		}
		else
		{
			m_nLife = 0;
			break;
		}

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
		//a�u�����f�B���O�����Z�����ɐݒ�

		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//���f��(�p�[�c)�̕`��
		pXFile->GetAddress(m_nIdxXFile)->DrawSubset(nCntMat);
		//a�u�����f�B���O��ʏ�ɐݒ�
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
		//m_pMesh->DrawSubset(nCntMat);
		
			pMat[nCntMat].MatD3D.Emissive = Emissive;
			pMat[nCntMat].MatD3D.Diffuse = Color;
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);



}



CAfterImageObject::CAfterImageObject() :CObject(5)
{

}



//=============================================
//�f�X�g���N�^
//=============================================
CAfterImageObject::~CAfterImageObject()
{

}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CAfterImageObject::Init(void)
{

	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CAfterImageObject * CAfterImageObject::Create(char * pModelName, D3DXMATRIX mtx, D3DXCOLOR col, int nLife)
{
	CAfterImageObject * pObject3D = NULL;
	pObject3D = DBG_NEW  CAfterImageObject();
	
	pObject3D->Init();
	pObject3D->m_pAfterImage = CAfterImage::Create(pModelName, mtx, col, nLife);
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CAfterImageObject::Uninit(void)
{
	m_pAfterImage->Uninit();
	delete m_pAfterImage;
	m_pAfterImage = NULL;
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CAfterImageObject::Update(void)
{
	m_pAfterImage->Update();
	if (m_pAfterImage->GetLife() <= 0)
	{
		CObject::Release();
	}

}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CAfterImageObject::Draw(void)
{
	m_pAfterImage->Draw();
}
