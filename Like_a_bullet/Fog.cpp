//==========================================================
//
// �t�H�O���� [fog.cpp]
// Author : �O�� ���V��
//
//==========================================================
#include "fog.h"
#include "debugproc.h"
#include"manager.h"
#include "renderer.h"

CFog::CFog()
{
}

CFog::~CFog()
{
}
//======================================
//����������
//======================================
void CFog::Init()
{
	//���l�̃��Z�b�g
	m_FogMode = D3DFOG_NONE;
	m_FogStart = 0.0f;
	m_FogEnd = 0.0f;
	m_FogDensity = 0.0f;
	m_FogColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//======================================
//�I������
//======================================
void CFog::Uninit()
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�̖�����wwwwwww
}

//======================================
//�X�V����
//======================================
void CFog::Update()
{
	CDebugProc * pDeb = CManager::GetDeb();
	if (m_FogMode != D3DFOG_NONE)
	{//�t�H�O��NONE�ł͂Ȃ���
		//�f�o�b�O�\��
		switch (m_FogMode)
		{
		case  D3DFOG_EXP:
			pDeb->Print("���݂̃t�H�O���[�h�FEXP\n");
			break;
		case  D3DFOG_EXP2:
			pDeb->Print("���݂̃t�H�O���[�h�FEXP2\n");
			break;
		case  D3DFOG_LINEAR:
			pDeb->Print("���݂̃t�H�O���[�h�FLINEAR\n");
			break;

		default:
			break;
		}

		pDeb->Print("�t�H�O�̐F�FR:%f G:%f B:%f A:%f\n", m_FogColor.r, m_FogColor.g, m_FogColor.b, m_FogColor.a);

		if (m_FogMode == D3DFOG_LINEAR)
		{
			pDeb->Print("�t�H�O�̊J�n�n�_�F%f\n",m_FogStart);
			pDeb->Print("�t�H�O�̏I���n�_�F%f\n", m_FogEnd);
		}
		else
		{
			pDeb->Print("�t�H�O�̖��x�F%f\n", m_FogDensity);
		}
	}
	else
	{
		pDeb->Print("���݂̃t�H�O���[�h�FNONE");
	}
}

//======================================
//�`�揈��
//======================================
void CFog::Draw()
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	
	
		if (m_FogMode != D3DFOG_NONE)
		{//�t�H�O���[�h���L���Ȏ�
			pDevice->SetRenderState(D3DRS_FOGCOLOR, m_FogColor);					//�F�̐ݒ�
			pDevice->SetRenderState(D3DRS_FOGTABLEMODE, m_FogMode);					//���[�h�̐ݒ�
			pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&m_FogStart)));		//�J�n�n�_�̐ݒ�
			pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&m_FogEnd)));			//�I���n�_�̐ݒ�
			pDevice->SetRenderState(D3DRS_FOGDENSITY, *((LPDWORD)(&m_FogDensity)));	//�t�H�O���x�̐ݒ�
			pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);								//�t�H�O�̗L����
		}
}

//======================================
//�ݒ菈��
//======================================
void CFog::Set(D3DFOGMODE FogMode, D3DXCOLOR FogColor, float FogStart, float FogEnd, float FogDensity)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	m_FogMode = FogMode;        //���[�h�̐ݒ�
	m_FogColor = FogColor;		//�F�̐ݒ�
	m_FogStart = FogStart;		//�J�n�n�_�̐ݒ�		*�t�H�O���[�h��D3DFOG_LINEAR�̎��ɎQ�Ƃ����*
	m_FogEnd = FogEnd;			//�I���n�_�̐ݒ�		*�t�H�O���[�h��D3DFOG_LINEAR�̎��ɎQ�Ƃ����*
	m_FogDensity = FogDensity;	//�t�H�O���x�̐ݒ�		0.0f�`1.0f�̊Ԃ̐��l�����	*�t�H�O���[�h��D3DFOG_LINEAR�ł͖������ɎQ�Ƃ����*
	pDevice->SetRenderState(D3DRS_FOGCOLOR, m_FogColor);					//�F�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, m_FogMode);					//���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&m_FogStart)));		//�J�n�n�_�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&m_FogEnd)));			//�I���n�_�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *((LPDWORD)(&m_FogDensity)));	//�t�H�O���x�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);								//�t�H�O�̗L����
}