//========================================================================================
//
// 3Dオブジェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "renderer.h"
#include "Line.h"
#include "manager.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================

CLine::CLine(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_fHeight = 10.0f;
	m_fWidth = 10.0f;
}



//=============================================
//デストラクタ
//=============================================
CLine::~CLine()
{
}


//=============================================
//ポリゴン初期化関数
//=============================================
HRESULT CLine::Init(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX rotationMatrix;
	// 3次元ベクトルの定義
	D3DXVECTOR3 vector = m_end - m_start; // 例: X軸に向いたベクトル

	// ベクトルを単位ベクトルに正規化
	D3DXVec3Normalize(&vector, &vector);

	// ベクトルから角度を計算
	float angleX = atan2f(vector.y, vector.z); // X軸周りの角度 (ラジアン)
	float angleY = atan2f(vector.z, vector.x); // Y軸周りの角度 (ラジアン)
	float angleZ = atan2f(vector.x, vector.y); // Z軸周りの角度 (ラジアン)
	SetRot(D3DXVECTOR3(angleX, angleY, angleZ));

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, GetRot().y, GetRot().x, GetRot().z);



	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 3,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;


	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff->Unlock();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 3,
		D3DUSAGE_WRITEONLY,
		{ FVF_VERTEX_3D },
		D3DPOOL_MANAGED,
		&m_pVtxBuff2,
		NULL);

	m_pVtxBuff2->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, -m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff2->Unlock();

	return S_OK;;
}
//=============================================
//生成関数
//=============================================
CLine * CLine::Create(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR col, int nPriority)
{
	CLine * pLine = NULL;

	pLine = DBG_NEW CLine;
	pLine->m_start = start;
	pLine->m_end = start;
	pLine->m_endDest = start;
	pLine->col = col;
	pLine->Init();
	return pLine;
}



//=============================================
//ポリゴンの終了処理
//=============================================
void CLine::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================
//ポリゴンの更新処理
//=============================================
void CLine::Update(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();

	D3DXMATRIX rotationMatrix;
	// 3次元ベクトルの定義
	D3DXVECTOR3 vector = m_end - m_start; // 例: X軸に向いたベクトル

	m_end += (m_endDest - m_end) / 6;

	// ベクトルを単位ベクトルに正規化
	D3DXVec3Normalize(&vector, &vector);

	// ベクトルから角度を計算
	float angleX = atan2f(vector.y, vector.z); // X軸周りの角度 (ラジアン)
	float angleY = atan2f(vector.z, vector.x); // Y軸周りの角度 (ラジアン)
	float angleZ = atan2f(vector.x, vector.y); // Z軸周りの角度 (ラジアン)
	SetRot(D3DXVECTOR3(angleX, angleY, angleZ));

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, GetRot().y, GetRot().x, GetRot().z);


	VERTEX_3D * pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;
	//法線の設定
	pVtx[0].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);


	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff->Unlock();
	

	m_pVtxBuff2->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, +m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, -m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&pVtx[0].pos, &pVtx[0].pos, &rotationMatrix);
	D3DXVec3TransformCoord(&pVtx[1].pos, &pVtx[1].pos, &rotationMatrix);

	pVtx[0].pos += m_start;
	pVtx[1].pos += m_start;
	pVtx[2].pos += m_end;

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;


	m_pVtxBuff2->Unlock();
}

//=============================================
//ポリゴンの描画処理
//=============================================
void CLine::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリクス

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//カリングの設定
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);


														 //頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff2, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//カリングの設定
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定
}

