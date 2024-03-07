//========================================================================================
//
// 3D�I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "Line.h"
#include "manager.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================

CLine::CLine(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_fHeight = 10.0f;
	m_fWidth = 10.0f;
}



//=============================================
//�f�X�g���N�^
//=============================================
CLine::~CLine()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CLine::Init(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX rotationMatrix;
	// 3�����x�N�g���̒�`
	D3DXVECTOR3 vector = m_end - m_start; // ��: X���Ɍ������x�N�g��

	// �x�N�g����P�ʃx�N�g���ɐ��K��
	D3DXVec3Normalize(&vector, &vector);

	// �x�N�g������p�x���v�Z
	float angleX = atan2f(vector.y, vector.z); // X������̊p�x (���W�A��)
	float angleY = atan2f(vector.z, vector.x); // Y������̊p�x (���W�A��)
	float angleZ = atan2f(vector.x, vector.y); // Z������̊p�x (���W�A��)
	SetRot(D3DXVECTOR3(angleX, angleY, angleZ));

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, GetRot().y, GetRot().x, GetRot().z);



	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 3,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;


	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff->Unlock();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 3,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff2,
		NULL);

	m_pVtxBuff2->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, -m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff2->Unlock();

	return S_OK;;
}
//=============================================
//�����֐�
//=============================================
CLine * CLine::Create(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col, int nPriority)
{
	CLine * pLine = NULL;

	pLine = DBG_NEW CLine;
	pLine->m_start = start;
	pLine->m_end = start;
	pLine->m_endDest = start;
	pLine->col = col;
	pLine->Init();
	return pLine;
}



//=============================================
//�|���S���̏I������
//=============================================
void CLine::Uninit(void)
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
void CLine::Update(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX rotationMatrix;
	// 3�����x�N�g���̒�`
	D3DXVECTOR3 vector = m_end - m_start; // ��: X���Ɍ������x�N�g��

	m_end += (m_endDest - m_end) / 6;

	// �x�N�g����P�ʃx�N�g���ɐ��K��
	D3DXVec3Normalize(&vector, &vector);

	// �x�N�g������p�x���v�Z
	float angleX = atan2f(vector.y, vector.z); // X������̊p�x (���W�A��)
	float angleY = atan2f(vector.z, vector.x); // Y������̊p�x (���W�A��)
	float angleZ = atan2f(vector.x, vector.y); // Z������̊p�x (���W�A��)
	SetRot(D3DXVECTOR3(angleX, angleY, angleZ));

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, GetRot().y, GetRot().x, GetRot().z);


	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;
	//�@���̐ݒ�
	pVtx[0].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);


	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff->Unlock();
	

	m_pVtxBuff2->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, -m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff2->Unlock();
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CLine::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//�J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);


														 //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff2, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//�J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
}

