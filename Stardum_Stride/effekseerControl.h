//==================
//エフェクトヘッダー
//Author: 丹野 竜之介
//==================
#ifndef  _EFFEKSEERCONTROL_H_//二重インクルード防止のマクロ
#define _EFFEKSEERCONTROL_H_
//インクルード
#include "main.h"
#include <vector>
#include <functional>

class CEffekseer
{
public:
	//クラス内クラス
	class CEffectData
	{
	public:

		CEffectData();
		~CEffectData();

		::Effekseer::Vector3D m_pos;
		::Effekseer::Vector3D m_rot;
		::Effekseer::Vector3D m_move;
		Effekseer::Handle handle;
		Effekseer::EffectRef efcRef;
		float m_fScale;
		bool m_bLoop;
	};

	CEffekseer();
	~CEffekseer();
	void Init();
	void Processing();
	void Uninit();
	Effekseer::EffectRef Loading(std::string path);
	CEffectData* Create(std::string path, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fScale = 1.0f, bool bLoop = false);
	static CEffekseer* GetInstance() {
		if (pInstance == NULL) { pInstance = DBG_NEW CEffekseer; return pInstance; }
		else
		{
			return pInstance;
		}
	}
	Effekseer::ManagerRef GetManager() { return m_EfkManager; }
protected:
	std::function<void()> onLostDevice;
	std::function<void()> onResetDevice;

private:
	static CEffekseer* pInstance;
	std::vector<CEffectData *> m_vEffect;
	EffekseerRendererDX9::RendererRef m_efkRenderer;
	Effekseer::ManagerRef m_EfkManager;
	int32_t time = 0;
};


#endif // ! _EFFEKSEERCONTROL_H_