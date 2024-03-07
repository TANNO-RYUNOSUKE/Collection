//========================================================================================
//
// エフェクト
// Author: 丹野 竜之介
//
//========================================================================================
//インクルード
#include "effekseerControl.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include <codecvt>
#include <locale>
#pragma warning(disable : 4996)
CEffekseer* CEffekseer::pInstance = NULL;
CEffekseer::CEffekseer()
{
}

CEffekseer::~CEffekseer()
{
}

void CEffekseer::Init()
{
	//エフェクシア系
	m_vEffect.clear();
// エフェクトのマネージャーの作成
	m_EfkManager = ::Effekseer::Manager::Create(8000);

	// 描画デバイスの作成
	auto graphicsDevice = ::EffekseerRendererDX9::CreateGraphicsDevice(CManager::GetInstance()->GetRenderer()->GetDevice());

	// Create a renderer of effects
	// エフェクトのレンダラーの作成
	m_efkRenderer = ::EffekseerRendererDX9::Renderer::Create(graphicsDevice, 8000);

	// Sprcify rendering modules
	// 描画モジュールの設定
	m_EfkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_EfkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_EfkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_EfkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_EfkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	// Specify a texture, model, curve and material loader
	// It can be extended by yourself. It is loaded from a file on now.
	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
	// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
	m_EfkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_EfkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_EfkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_EfkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
	// 座標系を設定する。アプリケーションと一致させる必要がある。
	m_EfkManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

}
void CEffekseer::Uninit()
{
	m_EfkManager->StopAllEffects();
	
	//onLostDevice();
}
void CEffekseer::Processing()
{
	CCamera* pCamera = CManager::GetInstance()->GetScene()->GetCamera();
	if (!CManager::GetInstance()->GetPause())
	{
		time++;



		for (int i = 0; i < (int)m_vEffect.size(); i++)
		{
			Effekseer::Handle loacalhandle = m_vEffect[i]->handle;

			if (!m_EfkManager->Exists(loacalhandle))
			{
				m_EfkManager->StopEffect(loacalhandle);

				// 削除
				if (!m_vEffect[i]->m_bLoop)
				{
					m_vEffect.erase(m_vEffect.begin() + i);

				}
				else
				{

					// 新たにエフェクトを再生し直す。座標はエフェクトを表示したい場所を設定する
					// (位置や回転、拡大縮小も設定しなおす必要がある)
					m_vEffect[i]->handle = m_EfkManager->Play(m_vEffect[i]->efcRef, 0.0f, 0.0f, 0.0f);

					m_EfkManager->SetLocation(m_vEffect[i]->handle, m_vEffect[i]->m_pos.X, m_vEffect[i]->m_pos.Y, m_vEffect[i]->m_pos.Z);
					m_EfkManager->SetRotation(m_vEffect[i]->handle, m_vEffect[i]->m_rot.X, m_vEffect[i]->m_rot.Y, m_vEffect[i]->m_rot.Z);
					m_EfkManager->SetScale(m_vEffect[i]->handle, m_vEffect[i]->m_fScale, m_vEffect[i]->m_fScale, m_vEffect[i]->m_fScale);
				}
			}
			else
			{// 再生中
				m_EfkManager->SetLocation(m_vEffect[i]->handle, m_vEffect[i]->m_pos.X, m_vEffect[i]->m_pos.Y, m_vEffect[i]->m_pos.Z);
				m_EfkManager->SetRotation(m_vEffect[i]->handle, m_vEffect[i]->m_rot.X, m_vEffect[i]->m_rot.Y, m_vEffect[i]->m_rot.Z);
				m_EfkManager->SetScale(m_vEffect[i]->handle, m_vEffect[i]->m_fScale, m_vEffect[i]->m_fScale, m_vEffect[i]->m_fScale);
				m_EfkManager->AddLocation(m_vEffect[i]->handle, m_vEffect[i]->m_move);
			}
		
		}
		// レイヤーパラメータの設定
		Effekseer::Manager::LayerParameter layerParameter;

		if (pCamera != NULL)
		{
			::Effekseer::Matrix44 cameraMatrix;
			cameraMatrix = pCamera->m_mtxView;
			::Effekseer::Matrix44 invEfkCameraMatrix;
			::Effekseer::Matrix44::Inverse(invEfkCameraMatrix, cameraMatrix);
			layerParameter.ViewerPosition = ::Effekseer::Vector3D(invEfkCameraMatrix.Values[3][0], invEfkCameraMatrix.Values[3][1], invEfkCameraMatrix.Values[3][2]);
		}
		m_EfkManager->SetLayerParameter(0, layerParameter);

		// マネージャーの更新
		Effekseer::Manager::UpdateParameter updateParameter;
		m_EfkManager->Update(updateParameter);
	}
	m_efkRenderer->SetTime(time / 60.0f);
	
	// 時間を更新する
	if (pCamera != NULL)
	{
		// エフェクトの描画開始処理を行う。
		m_efkRenderer->BeginRendering();
		// Specify a projection matrix
		// 投影行列を設定
		::Effekseer::Matrix44 projectionMatrix; 
		D3DXMATRIX mtx = pCamera->m_mtxView;
		//D3DXMatrixInverse(&mtx, NULL, &mtx);

		projectionMatrix = pCamera->m_mtxProjection;
		m_efkRenderer->SetProjectionMatrix(projectionMatrix);
		
		::Effekseer::Matrix44 cameraMatrix; cameraMatrix = mtx;
		
		// Specify a camera matrix
		// カメラ行列を設定
	
		m_efkRenderer->SetCameraMatrix(cameraMatrix);
		// エフェクトの描画を行う。
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix = m_efkRenderer->GetCameraProjectionMatrix();
		m_EfkManager->Draw(drawParameter);

		// エフェクトの描画終了処理
		m_efkRenderer->EndRendering();
	}
	
}
CEffekseer::CEffectData* CEffekseer::Create(std::string path, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fScale, bool bLoop)
{
	CEffectData* pEffect = DBG_NEW CEffectData;
	pEffect->efcRef = Loading(path);
	// エフェクトの再生
	pEffect->handle = m_EfkManager->Play(pEffect->efcRef, pos.x, pos.y, pos.z);
	pEffect->m_pos = pos;
	pEffect->m_rot = rot;
	pEffect->m_move = move;
	pEffect->m_fScale = fScale;
	pEffect->m_bLoop = bLoop;
	return pEffect;
}
Effekseer::EffectRef CEffekseer::Loading(std::string path)
{
	// char16_tに変換
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
	std::u16string string16t = converter.from_bytes(path);

	// エフェクトの読込
	auto effect = Effekseer::Effect::Create(m_EfkManager, string16t.c_str());


	//onLostDevice = [effect]() -> void
	//{
	//	// 読み込んだエフェクトのリソースは全て破棄する。
	//	if (effect != nullptr)
	//	{
	//		effect->UnloadResources();
	//	}
	//};

	//onResetDevice = [effect]() -> void
	//{
	//	// エフェクトのリソースを再読み込みする。
	//	if (effect != nullptr)
	//	{
	//		effect->ReloadResources();
	//	}
	//};

	return effect;
}

CEffekseer::CEffectData::CEffectData()
{
	GetInstance()->m_vEffect.push_back(this);
}

CEffekseer::CEffectData::~CEffectData()
{
	CEffekseer::GetInstance()->GetManager()->StopEffect(handle);
	GetInstance()->m_vEffect.erase(std::find(GetInstance()->m_vEffect.begin(), GetInstance()->m_vEffect.end(), this));
}
