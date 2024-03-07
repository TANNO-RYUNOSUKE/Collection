//========================================================================================
//
// 3Dオブジェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "Map_Editer.h"
#include "manager.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include <stdio.h>
#include<vector>

char *c_apModelName[] =					//モデルデータ読み込み
{
	"Data\\MODEL\\AbandonedBuilding.x",

};
//=============================================
//コンストラクタ
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
//デストラクタ
//=============================================
CMap_Editer::~CMap_Editer()
{
}


//=============================================
//ポリゴン初期化関数
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
//生成関数
//=============================================
CMap_Editer * CMap_Editer::Create()
{
	CMap_Editer * pObject3D = NULL;

	pObject3D = DBG_NEW CMap_Editer();

	pObject3D->Init();
	return pObject3D;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CMap_Editer::Uninit(void)
{
	
}

//=============================================
//ポリゴンの更新処理
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
//セーブ
//=============================================
void CMap_Editer::Save(void)
{
	FILE *pFile;

	pFile = fopen("data\\TEXT\\map.bin", "wb");
	if (pFile != NULL)
	{
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			// 名前の長さを保存
			int nameLength = m_Map[i].name.size();
			fwrite(&nameLength, sizeof(int), 1, pFile);

			// 名前の内容を保存
			fwrite(m_Map[i].name.c_str(), sizeof(char), nameLength, pFile);

			// 位置と回転情報を保存
			fwrite(&m_Map[i].pos, sizeof(D3DXVECTOR3), 1, pFile);
			fwrite(&m_Map[i].rot, sizeof(D3DXVECTOR3), 1, pFile);

			// データの区切りを示すためにセパレータを挿入
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
			// 名前をテキストとして保存
			fprintf(pFile, "%s\n", m_Map[i].name.c_str());

			// 位置と回転情報をテキストとして保存
			fprintf(pFile, "%f %f %f\n", m_Map[i].pos.x, m_Map[i].pos.y, m_Map[i].pos.z);
			fprintf(pFile, "%f %f %f\n", m_Map[i].rot.x, m_Map[i].rot.y, m_Map[i].rot.z);

			// データの区切りを示すために空行を挿入
			fprintf(pFile, "\n");
		}
		fclose(pFile);
	}
}
//=============================================
//ロード
//=============================================
void CMap_Editer::Load(void)
{
	FILE *pFile;

	pFile = fopen("data\\TEXT\\map.bin", "rb");
	if (pFile != NULL)
	{
		for (int i = 0; i < MAX_MAPOBJECT; i++)
		{
			// 名前の長さを読み込む
			int nameLength;
			fread(&nameLength, sizeof(int), 1, pFile);

			// 名前の内容を読み込む
			char nameBuffer[256]; // 適切な長さのバッファを確保
			fread(nameBuffer, sizeof(char), nameLength, pFile);
			nameBuffer[nameLength] = '\0'; // 文字列の終端を追加
			m_Map[i].name = nameBuffer;

			// 位置と回転情報を読み込む
			fread(&m_Map[i].pos, sizeof(D3DXVECTOR3), 1, pFile);
			fread(&m_Map[i].rot, sizeof(D3DXVECTOR3), 1, pFile);

			// セパレータを読み捨てる
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
			// 名前をテキストから読み込む
			char nameBuffer[256];
			if (fgets(nameBuffer, sizeof(nameBuffer), pFile) != NULL)
			{
				// 改行文字を削除
				size_t nameLength = strlen(nameBuffer);
				if (nameLength > 0 && nameBuffer[nameLength - 1] == '\n')
				{
					nameBuffer[nameLength - 1] = '\0';
				}
				m_Map[i].name = nameBuffer;
			}

			// 位置と回転情報をテキストから読み込む
			if (fscanf(pFile, "%f %f %f\n", &m_Map[i].pos.x, &m_Map[i].pos.y, &m_Map[i].pos.z) == 3 &&
				fscanf(pFile, "%f %f %f\n", &m_Map[i].rot.x, &m_Map[i].rot.y, &m_Map[i].rot.z) == 3)
			{
				// データの区切りの空行を読み捨てる
				char buffer[256];
				if (fgets(buffer, sizeof(buffer), pFile) == NULL)
				{
					break; // ファイルの終端に達したら終了
				}
			}
		}
		fclose(pFile);
	}
}