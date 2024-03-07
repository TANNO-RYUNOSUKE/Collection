//========================================================================================
//
// 3Dオブジェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "Drone.h"
#include "manager.h"
#include "texture.h"
#include "xfile.h"
#include "Xmanager.h"
#include<vector>
#include "effect.h"
#include "enemymanager.h"
#include "player.h"
#include "item.h"
#include "itemmanager.h"
#include "scene.h"
#include "meshfield.h"
//=============================================
//コンストラクタ
//=============================================

CDrone::CDrone(int nPriority) : CObject(nPriority)
{



}



//=============================================
//デストラクタ
//=============================================
CDrone::~CDrone()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CDrone::Init()
{
	m_pLine = CLine::Create(GetPos(), GetPos(), D3DXCOLOR(0.2f, 0.9f, 1.0f, 1.0f));
	m_pObjectX = CObjectX::Create("data\\MODEL\\drone.x", GetPos());
	CXManager * pManger = CManager::GetXManager();
	pManger->Release(m_pObjectX->GetID());

	return S_OK;
}
//=============================================
//生成関数
//=============================================
CDrone * CDrone::Create( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority)
{
	CDrone * pDrone = NULL;

	pDrone = DBG_NEW  CDrone(nPriority);
	pDrone->SetPos(pos);
	pDrone->SetRot(rot);
	pDrone->rotDest = rot;
	pDrone->Init();
	return pDrone;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CDrone::Uninit(void)
{
	
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CDrone::Update(void)
{
	CItemManager * pItemmanager = CManager::GetItemManager();
	CItem ** pItem = pItemmanager->GetItem();
	CPlayer * pPlayer = NULL;
		pPlayer = CGame::GetPlayer();
		int nItemCount = 0;
		float fDis = FLT_MAX;
		bool bItem = false;
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < NUM_Item; i++)
		{
			if (pItem[i] != NULL)
			{
				if (fDis > CManager::GetDistance(pItem[i]->GetPos() - GetPos()))
				{
					fDis = CManager::GetDistance(pItem[i]->GetPos() - GetPos());
					pos = pItem[i]->GetPos();
					bItem = true;
				}
				nItemCount++;
			}
		}
		if (bItem)
		{
			D3DXVECTOR3 vec = pos - GetPos();
			D3DXVec3Normalize(&vec, &vec);
			SetMove(GetMove() + vec * 20.0f);
			//レーダーの表示;
			m_pLine->SetStart(GetPos());

		
				rotDest = (GetRot() + D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				m_pLine->SetEndDest(GetPos());
				m_pLine->SetEnd(GetPos());
			
		}
		else
		{
			if (pPlayer != NULL)
			{
				D3DXVECTOR3 offset(-100.0f, 300.0f, 0.0f);
				D3DXMATRIX rotationMatrix;

				D3DXMatrixRotationYawPitchRoll(&rotationMatrix, pPlayer->GetRot().y, pPlayer->GetRot().x, pPlayer->GetRot().z);

				D3DXVec3TransformCoord(&offset, &offset, &rotationMatrix);
				offset += pPlayer->GetPos();
				posDest = offset;
			}

			SetPos(GetPos() + (posDest - GetPos()) / 3);
			SetRot(GetRot() + (rotDest - GetRot()) / 30);
			m_pLine->SetEnd(m_pLine->GetEnd() + (posDest - GetPos()) / 2);
			m_pLine->SetStart(m_pLine->GetStart() + (posDest - GetPos()) / 2);

			float fDis = FLT_MAX;
			float fDisCheck = 0.0f;
			bool bEnemy = false;
			CEnemy ** pEnemy = CManager::GetEnemyManager()->GetEnemy();
			D3DXVECTOR3 EnemyPos = GetPos();
			int nNum = 0;
			for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
			{
				if (nNum >= CManager::GetEnemyManager()->GetNum())
				{
					break;
				}
				if (pEnemy[nCnt] != NULL)
				{
					nNum++;
					fDisCheck = CManager::GetDistance( pEnemy[nCnt]->GetPos() -GetPos());

					if (fDisCheck < fDis)
					{
						fDis = fDisCheck;
						EnemyPos = (pEnemy[nCnt]->GetModel()->GetPos() + pEnemy[nCnt]->GetPos());

						D3DXVECTOR3 vector = (pEnemy[nCnt]->GetModel()->GetPos() + pEnemy[nCnt]->GetPos()) - GetPos();
						D3DXVec3Normalize(&vector, &vector);
						vector *= 150.0f;
						m_pLine->SetEndDest(vector + GetPos());
						bEnemy = true;
					}
				}
			}

		
			D3DXMATRIX rotationMatrix;
			D3DXVECTOR3 offset(0.0f, 0.0f, 0.0f);

			// 3次元ベクトルの定義
			D3DXVECTOR3 vector = GetPos() - EnemyPos;

			// ベクトルを単位ベクトルに正規化
			D3DXVec3Normalize(&vector, &vector);

			// ベクトルから角度を計算
			float angleX = atan2f(vector.y, vector.z); // X軸周りの角度 (ラジアン)
			float angleY = atan2f(vector.z, vector.x); // Y軸周りの角度 (ラジアン)
			float angleZ = atan2f(vector.x, vector.y); // Z軸周りの角度 (ラジアン) 
			rotDest = D3DXVECTOR3(angleX, angleY, angleZ);

			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, GetRot().y, GetRot().x, GetRot().z);

			D3DXVec3TransformCoord(&offset, &offset, &rotationMatrix);
			offset += GetPos();

			
			//レーダーの表示;
			m_pLine->SetStart(offset);

			if (!bEnemy)
			{
				rotDest = (GetRot() + D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				m_pLine->SetEndDest(offset);
				m_pLine->SetEnd(offset);
			}
		}

		SetPos(GetPos() + GetMove());
		SetMove(GetMove() * 0.9f);
		m_pObjectX->SetPos(GetPos());
		m_pObjectX->SetRot(GetRot());



		if (CGame::GetMeshfield()->Collision(GetPosAddress()) == true)
		{
			SetMove(D3DXVECTOR3(GetMove().x, -GetMove().y, GetMove().z));
		}
	for (int i = 0; i < NUM_Item; i++)
	{
		if (pItem[i] != NULL)
		{
			pItem[i]->Collision(GetPos());
		}
	}

}

//=============================================
//ポリゴンの描画処理
//=============================================
void CDrone::Draw(void)
{
	

}
