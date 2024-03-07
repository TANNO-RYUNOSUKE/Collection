//========================================================================================
//
// エクスプロージョン
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "object2D.h"
#include "Reticle.h"
#include "input.h"
#include "bullet.h"
#include "Reticle.h"
#include "texture.h"

//=============================================
//コンストラクタ
//=============================================
CReticle::CReticle():CObject2D(7)
{

}
//=============================================
//デストラクタ
//=============================================
CReticle::~CReticle()
{
}

//=============================================
//初期化関数
//=============================================
HRESULT CReticle::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();



	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_2D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	CTexture * pTex = CManager::GetTexture();
	m_pIdxTex = DBG_NEW int;
	*m_pIdxTex = pTex->Regist("data\\TEXTURE\\reticle.png");
	VERTEX_2D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点座標の設定
	SetVtx(pVtx);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

	m_pVtxBuff->Unlock();
	return S_OK;
}
//=============================================
//終了関数
//=============================================
void CReticle::Uninit()
{
	CObject2D::Uninit();
}
//=============================================
//更新関数
//=============================================
void CReticle::Update()
{
	CObject2D::Update();
	SetRot(D3DXVECTOR3(0.0f, 0.0f, GetRot().z + 0.001f));
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_2D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	SetVtx(pVtx);
	m_pVtxBuff->Unlock();
}
//=============================================
//描画関数
//=============================================
void CReticle::Draw()
{

	CTexture * pTex = CManager::GetTexture();
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	//aブレンディングを通常に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	//テクスチャの設定
	pDevice->SetTexture(0, pTex->Getaddress(*(m_pIdxTex)));
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================
//生成関数
//=============================================
CReticle * CReticle::Create(D3DXVECTOR3 pos)
{
	CReticle * pReticle = NULL;
	pReticle = DBG_NEW CReticle;
	pReticle->SetPos(pos);
	pReticle->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pReticle->SetWidth(300.0f);
	pReticle->SetHeight(300.0f);
	pReticle->Init();
	return pReticle;
}
