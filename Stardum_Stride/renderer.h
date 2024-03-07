//==================
//�����_���[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _RENDERER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _RENDERER_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"
class CZTexture;	//Z�e�N�X�`��
class CDepthShadow; //�[�x�V���h�E
struct EffekseerData
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	Effekseer::Handle handle;
	bool b_loop;
}; 


//�N���X��`
class CRenderer //�����_���[�N���X
{
public:
	//�R���X�g���N�^�ƃf�X�g���N�^
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;}
	CZTexture * GetZShader(void) { return m_pZTex; }
	CDepthShadow * GetDepthShader(void) { return m_pDepthShadow; }

private:
	ID3DXSprite * m_pSprite;	 //�V���h�E�p�X�v���C�g
	ID3DXSprite * m_pSpriteBloom;	 //�V���h�E�p�X�v���C�g

	CZTexture * m_pZTex;		//Z�e�N�X�`�������p
	CDepthShadow * m_pDepthShadow;					//�[�x�e
	LPDIRECT3D9 m_pD3D;						//direct3D�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//direct3D�f�o�C�X�ւ̃|�C���^
	IDirect3DDevice9 * m_pDev; //�`��f�o�C�X
	D3DXVECTOR3 Vdest, Rdest,V,R;
	D3DXMATRIX CameraView, CameraProj;	// �J�����r���[�ϊ��E�ˉe�ϊ�
	D3DXMATRIX LightView, LightProj;	// ���C�g�r���[�ϊ��E�ˉe�ϊ�
	LPDIRECT3DTEXTURE9 pSceneTexture;
	LPDIRECT3DTEXTURE9 pBloomTexture;
	LPD3DXEFFECT pEffectBrightCheck;//�P�x�m�F
	LPD3DXEFFECT pGauss;//�ڂ���
	IDirect3DTexture9 * m_pZTexture;				//Z�e�N�X�`���{��
	CObject2D * m_pScreen;
	CObject2D * m_pMini;
	CObject2D * m_pBloom;
	CObject2D * m_pBlomMini;


};

#endif // ! _RENDERER_H_
