//========================================================================================
//
// 3D�I�u�W�F�N�g
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "Map_Editer.h"
#include "manager.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include <stdio.h>
#include<vector>

char *c_apModelName[] =					//���f���f�[�^�ǂݍ���
{
	"Data\\MODEL\\AbandonedBuilding.x",

};
//=============================================
//�R���X�g���N�^
//=============================================

CMap_Editer::CMap_Editer() 
{
	m_pObject = NULL;
	for (int i = 0; i < MAX_MAPOBJECT; i++)
	{
		m_Map[i] = {};
	}
}



//=============================================
//�f�X�g���N�^
//=============================================
CMap_Editer::~CMap_Editer()
{
}


//=============================================
//�|���S���������֐�
//=============================================
HRESULT CMap_Editer::Init(void)
{
	Load();
	for (int i = 0; i < MAX_MAPOBJECT; i++)
	{
		if (m_Map[i].name != "")
		{
			CObjectX::Create((char *)m_Map[i].name.c_str(), m_Map[i].pos, m_Map[i].rot,0);
		}
	
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//=============================================
//�����֐�
//=============================================
CMap_Editer * CMap_Editer::Create()
{
	CMap_Editer * pObject3D = NULL;

	pObject3D = DBG_NEW CMap_Editer();

	pObject3D->Init();
	return pObject3D;
}



//=============================================
//�|���S���̏I������
//=============================================
void CMap_Editer::Uninit(void)
{
	
}

//=============================================
//�|���S���̍X�V����
//=============================================
void CMap_Editer::Update(void)
{
	CInputKeyboard * pInputKeyboard = CManager::GetInputKeyboard();
	m_pos.x = CGame::GetPlayer()->GetPos().x;
	m_pos.z = CGame::GetPlayer()->GetPos().z;
	
	if (pInputKeyboard->GetPress(DIK_Y))
	{
		m_pos.y += 50.0f;
	}
	if (pInputKeyboard->GetPress(DIK_H))
	{
		m_pos.y -= 50.0f;
	}
	if (pInputKeyboard->GetPress(DIK_U))
	{
		m_rot.x += 0.1f;
	}
	if (pInputKeyboard->GetPress(DIK_J))
	{
		m_rot.x -= 0.1f;
	}
	if (pInputKeyboard->GetPress(DIK_I))
	{
		m_rot.y += 0.1f;
	}
	if (pInputKeyboard->GetPress(DIK_K))
	{
		m_rot.y -= 0.1f;
	}
	if (pInputKeyboard->GetPress(DIK_O))
	{
		m_rot.z += 0.1f;
	}
	if (pInputKeyboard->GetPress(DIK_L))
	{
		m_rot.z -= 0.1f;
	}

	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x += D3DX_PI * 2;
	}
	else if (m_rot.x > D3DX_PI)
	{
		m_rot.x += -D3DX_PI * 2;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2;
	}
	else if (m_rot.z > D3DX_PI)
	{
		m_rot.z += -D3DX_PI * 2;
	}
	if (m_pObject == NULL)
	{
		m_pObject = m_pObject->Create(c_apModelName[0], m_pos);
	}
	m_pObject->SetPos(m_pos);
	m_pObject->SetRot(m_rot);
	if (pInputKeyboard->GetTrigger(DIK_C))
	{
		CObjectX::Create((char *)m_pObject->GetName().c_str(), m_pObject->GetPos(), m_pObject->GetRot(),0);
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			if (m_Map[i].name == "")
			{
				m_Map[i].name = m_pObject->GetName();
				m_Map[i].pos = m_pObject->GetPos();
				m_Map[i].rot = m_pObject->GetRot();
				break;
			}
		
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_F8))
	{
		Save();
	}
}

//=============================================
//�Z�[�u
//=============================================
void CMap_Editer::Save(void)
{
	FILE *pFile;

	pFile = fopen("data\\TEXT\\map.bin", "wb");
	if (pFile != NULL)
	{
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			// ���O�̒�����ۑ�
			int nameLength = m_Map[i].name.size();
			fwrite(&nameLength, sizeof(int), 1, pFile);

			// ���O�̓��e��ۑ�
			fwrite(m_Map[i].name.c_str(), sizeof(char), nameLength, pFile);

			// �ʒu�Ɖ�]����ۑ�
			fwrite(&m_Map[i].pos, sizeof(D3DXVECTOR3), 1, pFile);
			fwrite(&m_Map[i].rot, sizeof(D3DXVECTOR3), 1, pFile);

			// �f�[�^�̋�؂���������߂ɃZ�p���[�^��}��
			char separator = '\0';
			fwrite(&separator, sizeof(char), 1, pFile);
		}
		fclose(pFile);
	}
}
void CMap_Editer::SaveText(void)
{
	FILE* pFile;

	pFile = fopen("data\\TEXT\\map.txt", "w");
	if (pFile != NULL)
	{
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			// ���O���e�L�X�g�Ƃ��ĕۑ�
			fprintf(pFile, "%s\n", m_Map[i].name.c_str());

			// �ʒu�Ɖ�]�����e�L�X�g�Ƃ��ĕۑ�
			fprintf(pFile, "%f %f %f\n", m_Map[i].pos.x, m_Map[i].pos.y, m_Map[i].pos.z);
			fprintf(pFile, "%f %f %f\n", m_Map[i].rot.x, m_Map[i].rot.y, m_Map[i].rot.z);

			// �f�[�^�̋�؂���������߂ɋ�s��}��
			fprintf(pFile, "\n");
		}
		fclose(pFile);
	}
}
//=============================================
//���[�h
//=============================================
void CMap_Editer::Load(void)
{
	FILE *pFile;

	pFile = fopen("data\\TEXT\\map.bin", "rb");
	if (pFile != NULL)
	{
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			// ���O�̒�����ǂݍ���
			int nameLength;
			fread(&nameLength, sizeof(int), 1, pFile);

			// ���O�̓��e��ǂݍ���
			char nameBuffer[256]; // �K�؂Ȓ����̃o�b�t�@���m��
			fread(nameBuffer, sizeof(char), nameLength, pFile);
			nameBuffer[nameLength] = '\0'; // ������̏I�[��ǉ�
			m_Map[i].name = nameBuffer;

			// �ʒu�Ɖ�]����ǂݍ���
			fread(&m_Map[i].pos, sizeof(D3DXVECTOR3), 1, pFile);
			fread(&m_Map[i].rot, sizeof(D3DXVECTOR3), 1, pFile);

			// �Z�p���[�^��ǂݎ̂Ă�
			char separator;
			fread(&separator, sizeof(char), 1, pFile);
		}
		fclose(pFile);
	}
}
void CMap_Editer::LoadText(void)
{
	FILE* pFile;

	pFile = fopen("data\\TEXT\\map.txt", "r");
	if (pFile != NULL)
	{
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			// ���O���e�L�X�g����ǂݍ���
			char nameBuffer[256];
			if (fgets(nameBuffer, sizeof(nameBuffer), pFile) != NULL)
			{
				// ���s�������폜
				size_t nameLength = strlen(nameBuffer);
				if (nameLength > 0 && nameBuffer[nameLength - 1] == '\n')
				{
					nameBuffer[nameLength - 1] = '\0';
				}
				m_Map[i].name = nameBuffer;
			}

			// �ʒu�Ɖ�]�����e�L�X�g����ǂݍ���
			if (fscanf(pFile, "%f %f %f\n", &m_Map[i].pos.x, &m_Map[i].pos.y, &m_Map[i].pos.z) == 3 &&
				fscanf(pFile, "%f %f %f\n", &m_Map[i].rot.x, &m_Map[i].rot.y, &m_Map[i].rot.z) == 3)
			{
				// �f�[�^�̋�؂�̋�s��ǂݎ̂Ă�
				char buffer[256];
				if (fgets(buffer, sizeof(buffer), pFile) == NULL)
				{
					break; // �t�@�C���̏I�[�ɒB������I��
				}
			}
		}
		fclose(pFile);
	}
}