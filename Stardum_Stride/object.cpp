//========================================================================================
//
// �I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"
#include "debugproc.h"
#include "ZTexture.h"
#include "DepthShadow.h"
#include "effekseerControl.h"
//�ÓI�����o�ϐ��̏�����
CObject *CObject::m_apTop[NUM_PRIORITY] = {};
CObject *CObject::m_apCur[NUM_PRIORITY] = {}; 
CObject *CObject::m_pStaticNext = NULL;
int CObject::m_nNumALL = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CObject::CObject(int nPriority)
{
	m_pNext = NULL;
	m_pPrev = NULL;
	if (nPriority >= 0 && nPriority < NUM_PRIORITY)
	{
		m_nPriority = nPriority;
		if (m_apTop[nPriority] == NULL)
		{
			m_apTop[nPriority] = this;
		}
		if (m_apCur[nPriority] == NULL)
		{
			m_apCur[nPriority] = this;
		}
		else
		{
			m_apCur[nPriority]->m_pNext = this;
			this->m_pPrev = m_apCur[nPriority];
			m_apCur[nPriority] = this;
		}
	}
	m_nNumALL++;
	/*m_nID = -1;
	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apObject[nPriority][nCnt] == NULL)
		{
			m_apObject[nPriority][nCnt] = this;
			m_nID = nCnt;
			m_nPriority = nPriority;
			m_nNumALL++;
			break;
		}
	}*/
	m_bDraw = true;
	m_bShadow = false;
	m_bAutoRelease = true;
	m_bZ = false;
	m_Type = TYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 8; i++)
	{
		m_nIdxTex[i] = -1;
	}
	m_bUI = false;
	
}
//=============================================
//�f�X�g���N�^
//=============================================
CObject::~CObject()
{
}
//=============================================
//���������
//=============================================
void CObject::Release(void)
{
	if (m_pNext != NULL)
	{
		m_pNext->SetPrev(m_pPrev);
	}
	if (m_pPrev != NULL)
	{
		m_pPrev->SetNext(m_pNext);
	}
	if (m_apTop[m_nPriority] == this)
	{
		m_apTop[m_nPriority] = m_pNext;
	}
	if (m_apCur[m_nPriority] == this)
	{
		m_apCur[m_nPriority] = m_pPrev;
	}
	if (m_pStaticNext == this)
	{
		m_pStaticNext = m_pNext;
	}
	this->Uninit();
	delete this;

	m_nNumALL--;

}
//=============================================
//�S���������
//=============================================
void CObject::ReleaseAll(void)
{
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			if (pObject->m_bAutoRelease)
			{
				pObject->Release();
			}
			pObject = m_pStaticNext;
		}
	}
	m_nNumALL = 0;
}
//=============================================
//�X�V
//=============================================
void CObject::UpDateAll(void)
{
	CObject * pObject;
	CManager::GetInstance()->GetDeb()->Print("���݂̃I�u�W�F�N�g��:%d\n", m_nNumALL);
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			pObject->Update();
			pObject = m_pStaticNext;
		}
		/*for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
		{
			if (m_apObject[nPriority][nCnt] != NULL)
			{
				m_apObject[nPriority][nCnt]->Update();
			}
		}*/
	}
}
//=============================================
//�`��
//=============================================
void CObject::DrawAll(void)
{
	Draw3D();
	DrawUI();
}
void CObject::Draw3D(void)
{
	CCamera * pCamera = CManager::GetInstance()->GetScene()->GetCamera();
	if (pCamera != NULL)
	{
		pCamera->Set();
	}
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		if (nPriority == 1)
		{
			if (!CManager::GetInstance()->GetRenderer()->GetZShader()->GetbPass()&&!CManager::GetInstance()->GetRenderer()->GetDepthShader()->GetbPass())
			{
				CEffekseer::GetInstance()->Processing();
			}
			
		}
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			if (pObject->m_bDraw && !pObject->m_bUI)
			{
				if (CManager::GetInstance()->GetRenderer()->GetZShader()->GetbPass())
				{// �I�u�W�F�N�g�̕`��
					if (pObject->m_bZ)
						pObject->Draw();
				}
				else if (CManager::GetInstance()->GetRenderer()->GetDepthShader()->GetbPass())
				{// �I�u�W�F�N�g�̕`��
					if (pObject->m_bShadow)
						pObject->Draw();
				}
				else
				{
					if (!pObject->m_bShadow)
						pObject->Draw();
				}
			}
			pObject = m_pStaticNext;
		}
	}
}
void CObject::DrawUI(void)
{
	CObject * pObject;
	for (int nPriority = 0; nPriority < NUM_PRIORITY; nPriority++)
	{
		pObject = m_apTop[nPriority];
		while (pObject != NULL)
		{
			m_pStaticNext = pObject->m_pNext;
			if (pObject->m_bDraw && pObject->m_bUI)
			{		
				pObject->Draw();
			}
			pObject = m_pStaticNext;
		}
	}
}
D3DXVECTOR3 CObject::GetPos() 
{ 
	return m_pos; 
}//���W�擾
