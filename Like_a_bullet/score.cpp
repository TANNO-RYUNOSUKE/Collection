//========================================================================================
//
// �i���o�[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "Score.h"
#include "object2D.h"


//=============================================
//�R���X�g���N�^
//=============================================
CScore::CScore()
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}
	
	m_ndata = 0;
	m_pos = D3DXVECTOR3(1050.0f, 680.0f, 0.0f);
}



//=============================================
//�f�X�g���N�^
//=============================================
CScore::~CScore()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create();
		m_apNumber[nCnt]->Set(D3DXVECTOR3(m_pos.x + 25.0f * nCnt, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f);
	}
	return S_OK;
}
//=============================================
//�����֐�
//=============================================
CScore * CScore::Create(void)
{
	CScore * pScore = NULL;
	pScore = DBG_NEW CScore;
	pScore->Init();
	return pScore;
}



//=============================================
//�|���S���̏I������
//=============================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = NULL;
	}
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CScore::Update(void)
{
	if (m_ndata > 99999999)
	{
		m_ndata = 99999999;
	}

	m_apNumber[0]->Setdata(m_ndata % 100000000 / 10000000);
	m_apNumber[1]->Setdata(m_ndata % 10000000 / 1000000);
	m_apNumber[2]->Setdata(m_ndata % 1000000 / 100000);
	m_apNumber[3]->Setdata(m_ndata % 100000 / 10000);
	m_apNumber[4]->Setdata(m_ndata % 10000 / 1000);
	m_apNumber[5]->Setdata(m_ndata % 1000 / 100);
	m_apNumber[6]->Setdata(m_ndata % 100 / 10);
	m_apNumber[7]->Setdata(m_ndata % 10 / 1);
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}

}
