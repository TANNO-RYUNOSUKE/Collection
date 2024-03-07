//========================================================================================
//
// 3D�I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "meshfield.h"
#include "manager.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include <stdio.h>
#include "ZTexture.h"
#include "DepthShadow.h"

//=============================================
//�R���X�g���N�^
//=============================================

CMeshfield::CMeshfield(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_bShadow = true;
}



//=============================================
//�f�X�g���N�^
//=============================================
CMeshfield::~CMeshfield()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CMeshfield::Init(void)
{

	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\asphalt.jpg",
		&m_pTexture);


	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nSplit_U * m_nSplit_V),
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nSplit_V * 2 * (m_nSplit_U - 1)) + ((m_nSplit_U - 2) * 2)), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);

	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nU = 0; nU < m_nSplit_U; nU++)
	{
		for (int nV = 0; nV < m_nSplit_V; nV++)
		{
			pVtx[(nV + (nU * m_nSplit_V))].pos = D3DXVECTOR3((-m_fWidth * (m_nSplit_V - 1) / 2) + m_fWidth * nV, 0.0f, (m_fHeight * (m_nSplit_U - 1) / 2) + -m_fHeight * nU) + GetPos();
			pVtx[(nV + (nU * m_nSplit_V))].tex = -D3DXVECTOR2
			(
				nU * (float)(m_nSplit_U) *0.05f,
				nV * (float)(m_nSplit_V) *0.05f
			);
		}
	}
	Load();
	//�@���x�N�g���̐ݒ�
	for (int nCnt = 0; nCnt < (m_nSplit_U * m_nSplit_V); nCnt++)
	{
		D3DXVECTOR3 vecU, vecD, vecL, vecR, vecUL,vecDR,closs1, closs2, closs3, closs4;//�x�N�g���v�Z�p
		bool bUP, bDawn, bLeft, bRight,bUpLeft,bDownRight;//�����`�F�b�N�p
		bUP = false;
		bDawn = false;
		bLeft = false;
		bRight = false;
		bUpLeft = false;
		bDownRight = false;
		closs1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		closs2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		closs3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		closs4 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecDR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecUL = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		int nCheck = 0;
		if ((nCnt - m_nSplit_U - 1) >= 0)
		{//����ɗאڂ��钸�_������ꍇ
			if ((nCnt - m_nSplit_U - 1) % m_nSplit_U != (m_nSplit_U - 1))
			{
				bUpLeft = true;
				vecUL = pVtx[nCnt - m_nSplit_U - 1].pos - pVtx[nCnt].pos;
			}
		}
		if ((nCnt + m_nSplit_U + 1) <= (m_nSplit_U * m_nSplit_V))
		{//�E���ɗאڂ��钸�_������ꍇ
			if ((nCnt + m_nSplit_U + 1) % m_nSplit_U != 0)
			{
				bDownRight = true;
				vecDR = pVtx[nCnt + m_nSplit_U + 1].pos - pVtx[nCnt].pos;
			}
		}
		if ((nCnt - m_nSplit_U) >= 0)
		{//��ɗאڂ��钸�_������ꍇ
			bUP = true;
			vecU = pVtx[nCnt - m_nSplit_U].pos - pVtx[nCnt].pos;
		}
		if ((nCnt + m_nSplit_U) <= (m_nSplit_U * m_nSplit_V))
		{//���ɗאڂ��钸�_������ꍇ
			bDawn = true;
			vecD = pVtx[nCnt + m_nSplit_U].pos - pVtx[nCnt].pos;
		}
		if ((nCnt - 1) >= 0  )
		{//���ɗאڂ��钸�_������ꍇ
			if ((nCnt - 1) % m_nSplit_U != (m_nSplit_U - 1) )
			{
				bLeft = true;
				vecL = pVtx[nCnt - 1].pos - pVtx[nCnt].pos;
			}
		}
		if ((nCnt + 1) <= (m_nSplit_U * m_nSplit_V))
		{//�E�ɗאڂ��钸�_������ꍇ
			if ((nCnt + 1) % m_nSplit_U != 0)
			{
				bRight = true;
				vecR = pVtx[nCnt + 1].pos - pVtx[nCnt].pos;
			}
		}
		//�ݒ�J�n
		if (bUP == true && bUpLeft == true)
		{
			D3DXVec3Cross(&closs1, &vecUL, &vecU);
			D3DXVec3Normalize(&closs1, &closs1);
			nCheck++;
		}
	
		//�ݒ�J�n
		if (bLeft == true && bUpLeft == true)
		{
			D3DXVec3Cross(&closs2, &vecL, &vecUL);
			D3DXVec3Normalize(&closs2, &closs2);
			nCheck++;
		}
		//�ݒ�J�n
		if (bDawn == true && bDownRight == true)
		{
			D3DXVec3Cross(&closs3, &vecDR, &vecD);
			D3DXVec3Normalize(&closs3, &closs3);
			nCheck++;
		}
		if (bRight == true && bDownRight == true)
		{
			D3DXVec3Cross(&closs4, &vecR, &vecDR);
			D3DXVec3Normalize(&closs4, &closs4);
			nCheck++;
		}
		if (nCheck!=4)
		{
			pVtx[nCnt].pos.y = 0.0f;
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		else
		{
			pVtx[nCnt].nor = (closs1 + closs2 + closs3 + closs4) / (float)nCheck;
		}
		
	}

	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�

	for (int nCnt = 0; nCnt < (m_nSplit_U * m_nSplit_V); nCnt++)
	{
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}


	m_pVtxBuff->Unlock();

	WORD*pIdx; //�C���f�b�N�X���ւ̃|�C���^
			   //�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	int nCnt1;
	int nCnt2;
	int nPlus = 0;

	for (nCnt1 = 0; nCnt1 < m_nSplit_U - 1; nCnt1++)
	{
		for (nCnt2 = 0; nCnt2 < m_nSplit_V; nCnt2++)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * m_nSplit_V * 2) + nPlus] = nCnt2 + ((nCnt1 + 1)*m_nSplit_V);
			pIdx[(nCnt2 * 2) + (nCnt1 * m_nSplit_V * 2) + 1 + nPlus] = nCnt2 + ((nCnt1)*m_nSplit_V);
		}
		if (nCnt1 < m_nSplit_U - 2)
		{
			pIdx[(nCnt2 * 2) + (nCnt1 * m_nSplit_V * 2) + nPlus] = (nCnt2 - 1) + ((nCnt1)*m_nSplit_V);
			pIdx[(nCnt2 * 2) + (nCnt1 * m_nSplit_V * 2) + 1 + nPlus] = nCnt2 + ((nCnt1 + 1)*m_nSplit_V);
			nPlus += 2;
		}
	}
	m_pIdxBuff->Unlock();

	return S_OK;;
}
//=============================================
//���C�֐�
//=============================================
bool CMeshfield::MeshRay(const D3DXVECTOR3 & Start, const D3DXVECTOR3 & End)
{
	int nPlus = 0;
	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt + nPlus < (m_nSplit_U * (m_nSplit_V - 1));)
	{
		if (true == CManager::GetInstance()->RayTri(Start, End, pVtx[m_nSplit_V + nPlus].pos, pVtx[0 + nPlus].pos, pVtx[m_nSplit_V + 1 + nPlus].pos))
		{

			m_pVtxBuff->Unlock();
			return true;
		}

		
		if (true == CManager::GetInstance()->RayTri(Start, End, pVtx[1 + nPlus].pos, pVtx[m_nSplit_V + 1 + nPlus].pos, pVtx[0 + nPlus].pos))
		{

			m_pVtxBuff->Unlock();
			return true;
		}
		
		nCnt += 1;
		pVtx += 1;
		if (nCnt % (m_nSplit_U - 1) == 0)
		{
			nCnt += 1;
			nPlus += 2;
		}
	}

	m_pVtxBuff->Unlock();
	return false;
}
//=============================================
//�����֐�
//=============================================
CMeshfield * CMeshfield::Create(float fHeight, float fWidth, int nU, int nV, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CMeshfield * pObject3D = NULL;

	pObject3D = DBG_NEW CMeshfield(0);
	pObject3D->SetHeight(fHeight);
	pObject3D->SetWidth(fWidth);
	pObject3D->SetPos(pos);
	pObject3D->SetRot(rot);
	pObject3D->m_nSplit_U = nU;
	pObject3D->m_nSplit_V = nV;
	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CMeshfield::Uninit(void)
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
void CMeshfield::Update(void)
{
#if _DEBUG

	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();
	CInputKeyboard * pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	VERTEX_3D * pVtx;
	pDeb->Print("����:���͂̒��_���㉺\n");
	pDeb->Print("F9:�ۑ�\n");
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (pPlayer != NULL)
	{
		if (pInputKeyboard->GetTrigger(DIK_F9))
		{
			Save();
		}
		if (pInputKeyboard->GetTrigger(DIK_B))
		{
			for (int nCnt = 0; nCnt < (m_nSplit_U * m_nSplit_V); nCnt++)
			{
				pVtx[nCnt].pos.y = 0.0f;
			}
		}
		if (pInputKeyboard->GetTrigger(DIK_N))
		{
			for (int nCnt = 0; nCnt < (m_nSplit_U * m_nSplit_V); nCnt++)
			{
				pVtx[nCnt].pos.y += (float)(rand() % 200 - 100);
			}
		}
		for (int nCnt = 0; nCnt < (m_nSplit_U * m_nSplit_V); nCnt++)
		{
			if (std::fabs(pVtx[nCnt].pos.x - pPlayer->GetPos().x) <= 1000.0f &&std::fabs(pVtx[nCnt].pos.z - pPlayer->GetPos().z) <= 1000.0f )
			{
				if (pInputKeyboard->GetPress(DIK_RIGHT))
				{
					pVtx[nCnt].pos.y += 10.0f;
				}
				if (pInputKeyboard->GetPress(DIK_LEFT))
				{
					pVtx[nCnt].pos.y -= 10.0f;
				}
			}
			D3DXVECTOR3 dis = pVtx[nCnt].pos - pPlayer->GetPos();
			if (dis.x < 0.0f)
			{
				dis.x *= -1.0f;
			}

			if (dis.z < 0.0f)
			{
				dis.z *= -1.0f;
			}
			float fDis = dis.x + dis.z;
			if (fDis <= 10000.0f)
			{
				if (pInputKeyboard->GetPress(DIK_UP))
				{
					pVtx[nCnt].pos.y += 10.0f * (10000.0f - fDis) * 0.0001f;
				}
				if (pInputKeyboard->GetPress(DIK_DOWN))
				{
					pVtx[nCnt].pos.y -= 10.0f * (10000.0f - fDis) * 0.0001f;
				}
			}
		}
	}
	m_pVtxBuff->Unlock();
#endif // _DEBUG
}

//=============================================
//�|���S���̕`�揈��
//=============================================
void CMeshfield::Draw(void)
{
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���N�X

	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();
	
								 //���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	if (CManager::GetInstance()->GetRenderer()->GetZShader()->GetbPass())
	{
		CManager::GetInstance()->GetRenderer()->GetZShader()->SetWorldMatrix(&m_mtxWorld);
		CManager::GetInstance()->GetRenderer()->GetZShader()->SetParamToEffect();
		CManager::GetInstance()->GetRenderer()->GetZShader()->BeginPass();
	}
	else if (CManager::GetInstance()->GetRenderer()->GetDepthShader()->GetbPass())
	{
		CManager::GetInstance()->GetRenderer()->GetDepthShader()->SetWorldMatrix(&m_mtxWorld);
		CManager::GetInstance()->GetRenderer()->GetDepthShader()->SetAmbient(&(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));
		CManager::GetInstance()->GetRenderer()->GetDepthShader()->SetParamToEffect();
		CManager::GetInstance()->GetRenderer()->GetDepthShader()->BeginPass();
	}
		//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (m_nSplit_U * m_nSplit_V), 0, (m_nSplit_V * 2 * (m_nSplit_U - 1) + ((m_nSplit_U - 3) * 2)));
	if (CManager::GetInstance()->GetRenderer()->GetZShader()->GetbPass())
	{
		CManager::GetInstance()->GetRenderer()->GetZShader()->EndPass();
	}
	else if (CManager::GetInstance()->GetRenderer()->GetDepthShader()->GetbPass())
	{
		CManager::GetInstance()->GetRenderer()->GetDepthShader()->EndPass();
	}


}
//=============================================
//�Z�[�u
//=============================================
void CMeshfield::Save(void)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

				 //�t�@�C�����J��
	pFile = fopen("data\\TEXT\\mesh.txt", "w");
	if (pFile != NULL)
	{
		VERTEX_3D * pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < m_nSplit_U * m_nSplit_V; nCnt++)
		{
			fprintf(pFile, "%f\n", pVtx[nCnt].pos.y);
		}
		m_pVtxBuff->Unlock();
		fclose(pFile);
	}
}
//=============================================
//���[�h
//=============================================
void CMeshfield::Load(void)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

				 //�t�@�C�����J��
	pFile = fopen("data\\TEXT\\mesh.txt", "r");
	if (pFile != NULL)
	{
		VERTEX_3D * pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < m_nSplit_U * m_nSplit_V; nCnt++)
		{
			fscanf(pFile, "%f", &pVtx[nCnt].pos.y);					//�������ǂݍ���
		}
		m_pVtxBuff->Unlock();
		fclose(pFile);
	}

}
//=============================================
//�����蔻��
//=============================================
bool CMeshfield::Collision(D3DXVECTOR3 * ppos)
{
	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();
	CRenderer * pRenderer = CManager::GetInstance()->GetRenderer();
	D3DXVECTOR3 pos = *ppos;
	float dot = 0.0f;
	int nPlus = 0;
	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	int nCnt = 0;
	int nU = (pos.x + m_fWidth * (m_nSplit_U -1) / 2) / (m_fWidth);
	int nV = (-pos.z + m_fHeight * (m_nSplit_V - 1) / 2) / (m_fHeight);
		nCnt += nU + (m_nSplit_U -2)  * nV ;
		if (nU < m_nSplit_U && nU >= 0 &&nV < m_nSplit_V&& nV >= 0)
		{

			pVtx += nCnt;
			nCnt += nCnt / (m_nSplit_U - 1);
			nPlus += nCnt / (m_nSplit_U - 1) * 2;
			if (nPlus + nCnt < (m_nSplit_U * (m_nSplit_V)))
			{

				D3DXVECTOR3 nor, vec1, vec2;
				vec1 = (pVtx[0 + nPlus].pos - pVtx[m_nSplit_V + nPlus].pos);
				vec2 = (pVtx[m_nSplit_V + 1 + nPlus].pos - pVtx[m_nSplit_V + nPlus].pos);
				D3DXVec3Cross(&nor, &vec1, &vec2);

				D3DXVec3Normalize(&nor, &nor);
				D3DXVECTOR3 vecP1, vecP2, vecP3, vec01, vec02, vec03;
				vecP1 = pos - pVtx[m_nSplit_V + nPlus].pos - GetPos();
				vecP2 = pos - pVtx[0 + nPlus].pos - GetPos();
				vecP3 = pos - pVtx[m_nSplit_V + 1 + nPlus].pos - GetPos();
				vec01 = pVtx[0 + nPlus].pos - pVtx[m_nSplit_V + nPlus].pos;
				vec02 = pVtx[m_nSplit_V + 1 + nPlus].pos - pVtx[0 + nPlus].pos;
				vec03 = pVtx[m_nSplit_V + nPlus].pos - pVtx[m_nSplit_V + 1 + nPlus].pos;
				if ((vec01.z * vecP1.x) - (vec01.x * vecP1.z) > 0)
				{
					if ((vec02.z * vecP2.x) - (vec02.x * vecP2.z) > 0)
					{
						if ((vec03.z * vecP3.x) - (vec03.x * vecP3.z) > 0)
						{
							if (nor.y != 0.0f)
							{
								dot = ((pos.x - pVtx[m_nSplit_V + nPlus].pos.x - GetPos().x)*nor.x + (pos.z - pVtx[m_nSplit_V + nPlus].pos.z - GetPos().z)*nor.z - (pVtx[m_nSplit_V + nPlus].pos.y * nor.y)) / -nor.y;



								if (dot > pos.y)
								{
								
									pos += nor * 20.0f;
									*ppos = D3DXVECTOR3(pos.x, dot, pos.z);
								
									m_pVtxBuff->Unlock();
									return true;
								}
							}
						}
					}
				}

				vec1 = (pVtx[0 + nPlus].pos - pVtx[1 + nPlus].pos);
				vec2 = (pVtx[m_nSplit_V + 1 + nPlus].pos - pVtx[1 + nPlus].pos);
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);

				vecP1 = pos - pVtx[1 + nPlus].pos - GetPos();
				vecP2 = pos - pVtx[m_nSplit_V + 1 + nPlus].pos - GetPos();
				vecP3 = pos - pVtx[0 + nPlus].pos - GetPos();
				vec01 = pVtx[m_nSplit_V + 1 + nPlus].pos - pVtx[1 + nPlus].pos;
				vec02 = pVtx[0 + nPlus].pos - pVtx[m_nSplit_V + 1 + nPlus].pos;
				vec03 = pVtx[1 + nPlus].pos - pVtx[0 + nPlus].pos;
				if ((vec01.z * vecP1.x) - (vec01.x * vecP1.z) >= 0)
				{
					if ((vec02.z * vecP2.x) - (vec02.x * vecP2.z) >= 0)
					{
						if ((vec03.z * vecP3.x) - (vec03.x * vecP3.z) >= 0)
						{
							if (nor.y != 0.0f)
							{
								dot = ((pos.x - pVtx[1 + nPlus].pos.x - GetPos().x)*nor.x + (pos.z - pVtx[1 + nPlus].pos.z - GetPos().z)*nor.z - (pVtx[1 + nPlus].pos.y * nor.y)) / -nor.y;

								if (dot > pos.y)
								{
							
									*ppos = D3DXVECTOR3(pos.x, dot, pos.z);
									m_pVtxBuff->Unlock();
									return true;
								}
							}
						}
					}
				}
			}
		}
	
	

	m_pVtxBuff->Unlock();
	return false;
}