//========================================================================================
//
// ブロック
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Block.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"

LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;
//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObject2D(nPriority)
{
	
}
//=============================================
//デストラクタ
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CBlock::Init()
{
	CObject2D::Init();
	SetType(CObject::TYPE_BLOCK);

	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CBlock::Uninit()
{
	CObject2D::Uninit();
}
//=============================================
//更新関数
//=============================================
void CBlock::Update()
{
	
	Collision();
}
//=============================================
//描画関数
//=============================================
void CBlock::Draw()
{
	CObject2D::Draw();
}
//=============================================
//生成関数
//=============================================
CBlock * CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock * pBlock = NULL;
	pBlock = DBG_NEW CBlock;
	CBlock::Load();
	pBlock->BindTexture(m_pTexture);
	pBlock->SetPos(pos);
	pBlock->SetWidth(100.0f);
	pBlock->SetHeight(100.0f);

	pBlock->Init();
	return pBlock;
}
//=============================================
//ロード関数
//=============================================
HRESULT CBlock::Load(void)
{
	if (m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
		pDevice = CManager::GetRenderer()->GetDevice();

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Block000.jpg",
			&m_pTexture);
	}
	else
	{
		return E_FAIL;
	}
	return S_OK;
}
//=============================================
//アンロード関数
//=============================================
void CBlock::Unload(void)
{
	//テクスチャポインタの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================
//バインド関数
//=============================================
void CBlock::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	CObject2D::m_pTexture = m_pTexture;
}
//=============================================
//コリジョン
//=============================================
bool CBlock::Collision()
{
	//bool bLand = false;
	//D3DXVECTOR3 BlockPos = GetPos();
	//for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	//{
	//	for (int nCntObj = 0; nCntObj < NUM_OBJECT; nCntObj++)
	//	{
	//		CObject * pObj;
	//		pObj = CObject::GetObject(nCnt, nCntObj);
	//		if (pObj != NULL)
	//		{
	//			if (pObj->GetType() == CObject::TYPE_PLAYER || pObj->GetType() == CObject::TYPE_BULLET)
	//			{
	//				float Height = (GetHeight() / 2) + (pObj->GetHeight() / 2);
	//				float Width = (GetWidth() / 2) + (pObj->GetWidth() / 2);

	//				if (pObj->GetPos().x < BlockPos.x + Width && pObj->GetPos().x > BlockPos.x - Width && pObj->GetPos().y < BlockPos.y + Height && pObj->GetPos().y > BlockPos.y - Height)
	//				{
	//					if (pObj->GetType() == CObject::TYPE_BULLET)
	//					{
	//						pObj->SetLife(0);
	//					}

	//					if (pObj->GetPosOld().y <= BlockPos.y - Height && pObj->GetPos().y > BlockPos.y - Height)
	//					{//当たり判定、上面
	//						pObj->SetMove(D3DXVECTOR3(pObj->GetMove().x, 0.0f, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(pObj->GetPos().x, BlockPos.y - Height, pObj->GetPos().z));
	//						bLand = true;
	//						pObj->SetLand(bLand);
	//					}
	//					else if (pObj->GetPosOld().x >= BlockPos.x + Width && pObj->GetPos().x < BlockPos.x + Width)
	//					{//当たり判定、右面
	//						pObj->SetMove(D3DXVECTOR3(0.0f, pObj->GetMove().y, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(BlockPos.x + Width, pObj->GetPos().y, pObj->GetPos().z));
	//					}
	//					else if (pObj->GetPosOld().x <= BlockPos.x - Width && pObj->GetPos().x > BlockPos.y - Width)
	//					{//当たり判定、左面
	//						pObj->SetMove(D3DXVECTOR3(0.0f, pObj->GetMove().y, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(BlockPos.x - Width, pObj->GetPos().y, pObj->GetPos().z));
	//					}
	//					else if (pObj->GetPosOld().y >= BlockPos.y + Height && pObj->GetPos().y < BlockPos.y + Height)
	//					{//当たり判定、底面

	//						pObj->SetMove(D3DXVECTOR3(pObj->GetMove().x, 0.0f, pObj->GetMove().z));
	//						pObj->SetPos(D3DXVECTOR3(pObj->GetPos().x, BlockPos.y + Height, pObj->GetPos().z));

	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//return bLand;
	return true;
}