//========================================================================================
//
// 多重背景
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "MultiBg.h"

CObject2D * CMultiBg::m_apObject2D[NUM_MULTIBG] = {};
LPDIRECT3DTEXTURE9 CMultiBg::m_paTexture[NUM_MULTIBG] = {};

const char *c_apBg[] =					//テクスチャ
{
	"data\\TEXTURE\\moon1.png",
	"data\\TEXTURE\\moon2.png",
	"data\\TEXTURE\\moon3.png",
};
//=============================================
//コンストラクタ
//=============================================
CMultiBg::CMultiBg()
{
	m_aTexUV = D3DXVECTOR2(0.0f, 0.0f);
}
//=============================================
//デストラクタ
//=============================================
CMultiBg::~CMultiBg()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CMultiBg::Init()
{

	//for (int nCnt = 0; nCnt < NUM_MULTIBG; nCnt++)
	//{
	//	m_apObject2D[nCnt] = CObject2D::Create(0);

	//	VERTEX_2D * pVtx;
	//	LPDIRECT3DVERTEXBUFFER9 *pVtxBuff = m_apObject2D[nCnt]->GetBuff();
	//	(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

	//	//頂点座標の設定
	//	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//
	//	(*pVtxBuff)->Unlock();
	//}
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CMultiBg::Uninit()
{
	
}
//=============================================
//更新関数
//=============================================
void CMultiBg::Update()
{
	for (int nCnt = 0; nCnt < NUM_MULTIBG; nCnt++)
	{
	
		m_aTexUV.x += 0.0002f;
		VERTEX_2D * pVtx;
		LPDIRECT3DVERTEXBUFFER9 *pVtxBuff = m_apObject2D[nCnt]->GetBuff();
		(*pVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);

		if (m_aTexUV.x >= 1.0f)
		{
			m_aTexUV.x = 0.0f;
		}
		if (m_aTexUV.x < -1.0f)
		{
			m_aTexUV.x = 0.0f;
		}
		//頂点座標の設定
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((m_aTexUV.x * nCnt), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((m_aTexUV.x * nCnt) + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((m_aTexUV.x * nCnt), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((m_aTexUV.x * nCnt) + 1.0f, 1.0f);

		(*pVtxBuff)->Unlock();
	}
}
//=============================================
//描画関数
//=============================================
void CMultiBg::Draw()
{
	
}
//=============================================
//生成関数
//=============================================
CMultiBg * CMultiBg::Create(void)
{

	CMultiBg * pMultiBg = NULL;
	pMultiBg = DBG_NEW CMultiBg;
	pMultiBg->Init();
	pMultiBg->Load();
	pMultiBg->BindTexture();
	
	return pMultiBg;
}
//=============================================
//ロード関数
//=============================================
HRESULT CMultiBg::Load(void)
{
	
		LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();
	for (int nCntBg = 0;  nCntBg < NUM_MULTIBG;  nCntBg++)
	{
		
		if (m_paTexture[nCntBg] == NULL)
		{
			//テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice,
				c_apBg[nCntBg],
				&m_paTexture[nCntBg]);
		}
		else
		{
			return E_FAIL;
		}
	}
	
	return S_OK;
}
//=============================================
//アンロード関数
//=============================================
void CMultiBg::Unload(void)
{
	for (int nCnt = 0; nCnt < NUM_MULTIBG; nCnt++)
	{
		if (m_paTexture[nCnt] != NULL)
		{
			m_paTexture[nCnt]->Release();
			m_paTexture[nCnt] = NULL;
		}
	}
 }

void CMultiBg::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth)
{

}
//=============================================
//バインド関数
//=============================================
void CMultiBg::BindTexture()
{
	for (int nCnt = 0; nCnt < NUM_MULTIBG; nCnt++)
	{
		LPDIRECT3DTEXTURE9 * pTexture = m_apObject2D[nCnt]->GetTex();
		*pTexture = m_paTexture[nCnt];
	}

}