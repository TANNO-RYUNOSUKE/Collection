//========================================================================================
//
// �����_���[
// Author: �O�� ���V��
//
//========================================================================================
//�C���N���[�h
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "manager.h"
#include "ZTexture.h"
#include "DepthShadow.h"
#include "player.h"
#include "camera.h"
#include "shader.h"
#include "effekseerControl.h"
//=============================================
//�R���X�g���N�^
//=============================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//=============================================
//�f�X�g���N�^
//=============================================
CRenderer::~CRenderer()
{
}

//=============================================
//�������֐�
//=============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//DirectX�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct#D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�e��I�u�W�F�N�g�����������͂���
	CEffekseer::GetInstance()->Init();
	// �G�t�F�N�g�̓Ǎ�
	//auto effect = Effekseer::Effect::Create(m_EfkManager,(const char16_t*)"Laser01.efkefc");
	m_pD3DDevice->CreateTexture(
		(SCREEN_WIDTH),          // �e�N�X�`���̕�
		(SCREEN_HEIGHT),          // �e�N�X�`���̍���
		0,              // �~�b�v�}�b�v ���x��
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8, // �t�H�[�}�b�g
		D3DPOOL_DEFAULT, // �v�[��
		&pSceneTexture,  // �e�N�X�`�� �I�u�W�F�N�g
		NULL);
	m_pD3DDevice->CreateTexture(
		(SCREEN_WIDTH),          // �e�N�X�`���̕�
		(SCREEN_HEIGHT),          // �e�N�X�`���̍���
		0,              // �~�b�v�}�b�v ���x��
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8, // �t�H�[�}�b�g
		D3DPOOL_DEFAULT, // �v�[��
		&pBloomTexture,  // �e�N�X�`�� �I�u�W�F�N�g
		NULL);

	m_pScreen = CObject2D::Create(SCREEN_CENTER, SCREEN_HEIGHT, SCREEN_WIDTH);
	m_pScreen->m_bDraw = false;
	m_pScreen->m_bAutoRelease = false;
	m_pScreen->SetTex(pSceneTexture);
	m_pBloom = CObject2D::Create(SCREEN_CENTER, SCREEN_HEIGHT, SCREEN_WIDTH);
	m_pBloom->m_bDraw = false;
	m_pBloom->m_bAutoRelease = false;
	m_pBloom->SetTex(pBloomTexture);
	m_pBlomMini = CObject2D::Create(VECTO3ZERO, SCREEN_HEIGHT , SCREEN_WIDTH , 0, NULL, D3DXVECTOR2(0.0f, 0.0f));
	m_pBlomMini->m_bDraw = false;
	m_pBlomMini->m_bAutoRelease = false;
	m_pBlomMini->SetTex(pBloomTexture);

	m_pMini = CObject2D::Create(VECTO3ZERO, SCREEN_HEIGHT , SCREEN_WIDTH , 0, NULL, D3DXVECTOR2(0.0f, 0.0f));
	m_pMini->m_bDraw = false;
	m_pMini->m_bAutoRelease = false;
	m_pMini->SetTex(pSceneTexture);
	
	Vdest = {};
	Rdest = {};
	V = {};
	R = {};
	
		V = (D3DXVECTOR3(0.0f, 500.0f, 0.0f));
		R = (D3DXVECTOR3(10.0f, -10.0f, 0.0f));
	
	
	// �V�F�[�_�[�p�̏������͈ȉ�
		Loadshader("data\\SHADER\\BrightCheck.fx", &pEffectBrightCheck);
		Loadshader("data\\SHADER\\Gauss.fx", &pGauss);
	// Z�l�e�N�X�`�������I�u�W�F�N�g�̐����Ə�����
	m_pDev = m_pD3DDevice;
	D3DXCreateSprite(m_pD3DDevice, &m_pSprite);// �X�v���C�g�쐬
	m_pZTex = DBG_NEW CZTexture;
	m_pZTex->Init(*m_pDev, SCREEN_WIDTH * 1.0f, SCREEN_WIDTH * 1.0f, D3DFMT_A32B32G32R32F);
	m_pZTex->GetZTex(&m_pZTexture);

	// �[�x�o�b�t�@�V���h�E�I�u�W�F�N�g�̐����Ə�����
	m_pDepthShadow = DBG_NEW CDepthShadow;
	m_pDepthShadow->Init(*m_pDev);
	m_pDepthShadow->SetShadowMap(&m_pZTexture);	// �V���h�E�}�b�v�e�N�X�`����o�^
	D3DXMatrixPerspectiveFovLH(&CameraProj, D3DXToRadian(45), 1.777f, 10.0f, 50000.0f);
	D3DXMatrixPerspectiveFovLH(&LightProj, D3DXToRadian(45), 1.0f, 30.0f, 50000.0f);
	D3DXMatrixLookAtLH(&LightView, &D3DXVECTOR3(3000.0f, 3000.0f, 000.0f), &D3DXVECTOR3(10.0f, -10.0f, 00.0f), &D3DXVECTOR3(0, 1, 0));

	// Z�l�e�N�X�`��OBJ�֓o�^
	m_pZTex->SetViewMatrix(&LightView);
	m_pZTex->SetProjMatrix(&LightProj);

	// �[�x�o�b�t�@�V���h�EOBJ�֓o�^
	// �J�����r���[�͖���ς��̂ŕ`�掞�ɓo�^���܂�
	m_pDepthShadow->SetLightViewMatrix(&LightView);
	m_pDepthShadow->SetLightProjMatrix(&LightProj);
	m_pDepthShadow->SetCameraProjMatrix(&CameraProj);

	return S_OK;
}
//=============================================
//�I���֐�
//=============================================
void CRenderer::Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	CEffekseer::GetInstance()->Uninit();
	//DirectX3d�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//DirectX3d�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	
	if (m_pDepthShadow != NULL)
	{
		delete m_pDepthShadow;
		m_pDepthShadow = NULL;
	}
	if (m_pZTex != NULL)
	{
		delete m_pZTex;
		m_pZTex = NULL;
	}
}
//=============================================
//�X�V�֐�
//=============================================
void CRenderer::Update(void)
{
	//�e��I�u�W�F�N�g�̍X�V����
	CObject::UpDateAll();
	CPlayer * pPlayer = CManager::GetInstance()->GetScene()->GetPlayer();
	if (pPlayer != NULL)
	{
		 Vdest = (D3DXVECTOR3(0000.0f, 1500.0f, 0.0f) );
		 Rdest = (D3DXVECTOR3(10.0f, -10.0f, 0.0f) );
		 Vdest += pPlayer->GetPos();
		 Rdest += pPlayer->GetPos();
		 V = (V + (Vdest - V)* 0.01f);
		 R = (R + (Rdest - R)* 0.1f);
		D3DXMatrixLookAtLH(&LightView, &V, &R, &D3DXVECTOR3(0, 1, 0));
		m_pDepthShadow->SetLightpos(V);
		m_pDepthShadow->SetLightSeepos(R);
		// Z�l�e�N�X�`��OBJ�֓o�^
		m_pZTex->SetViewMatrix(&LightView);
		// �[�x�o�b�t�@�V���h�EOBJ�֓o�^

		m_pDepthShadow->SetLightViewMatrix(&LightView);
	
	
	}
}
//=============================================
//�`��֐�
//=============================================
void CRenderer::Draw(void)
{
	CDebugProc * pDeb = CManager::GetInstance()->GetDeb();
	//�`��T�[�t�F�C�X�擾

	IDirect3DSurface9* pBackBuffer;
	m_pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	IDirect3DSurface9* pRenderTarget;
	IDirect3DSurface9* pBrightBuffer;
	IDirect3DSurface9* pBloomBuffer;
	pSceneTexture->GetSurfaceLevel(0, &pRenderTarget);
	pBloomTexture->GetSurfaceLevel(0, &pBloomBuffer);
	m_pD3DDevice->SetRenderTarget(0, pRenderTarget);
	//��ʃN���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//���������ꍇ
		m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		m_pZTex->Begin();
		CObject::Draw3D();
		m_pZTex->End();
		m_pDepthShadow->Begin();
		CObject::Draw3D();
		m_pDepthShadow->End();
		// �I�u�W�F�N�g�̑S�`��
	
		CObject::Draw3D();
	
	
		// �e�N�X�`���T���v�����O�X�e�[�g��ݒ�
		m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP); // U�����̃��b�s���O�𖳌���
		m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP); // V�����̃��b�s���O�𖳌���

		// ���ȏ�̋P�x�𔲂��o��


		m_pD3DDevice->SetRenderTarget(0, pBloomBuffer);
		// �Œ�@�\�ɖ߂�
		m_pD3DDevice->SetVertexShader(NULL);
		m_pD3DDevice->SetPixelShader(NULL);
		pEffectBrightCheck->Begin(NULL, 0);
		pEffectBrightCheck->BeginPass(0);
		pEffectBrightCheck->SetTechnique("brightcheck");
	
		m_pScreen->Draw();
	
		pEffectBrightCheck->EndPass();
		pEffectBrightCheck->End();
		// �Œ�@�\�ɖ߂�
		m_pD3DDevice->SetVertexShader(NULL);
		m_pD3DDevice->SetPixelShader(NULL);


		m_pD3DDevice->SetRenderTarget(0, pBloomBuffer);
		// �K�E�X�ڂ�����K�p
		pGauss->Begin(NULL, 1);
		pGauss->BeginPass(0);
		pGauss->SetTechnique("GaussianBlur");
		pGauss->SetTexture("InputTexture", pBloomTexture);
		m_pBloom->Draw();
		pGauss->EndPass();
		pGauss->End();
		// �Œ�@�\�ɖ߂�
		m_pD3DDevice->SetVertexShader(NULL);
		m_pD3DDevice->SetPixelShader(NULL);
	

		m_pD3DDevice->SetRenderTarget(0,pBackBuffer);
		m_pScreen->Draw();
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_pBloom->Draw();
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
		CObject::DrawUI();
	//	m_pBlomMini->Draw();
		D3DXMATRIX SpriteScaleMat;
		D3DXMatrixScaling(&SpriteScaleMat, 0.125f, 0.125f, 1.0f);
		m_pSprite->SetTransform(&SpriteScaleMat);
		m_pSprite->Begin(0);
		//m_pSprite->Draw(m_pZTexture, NULL, NULL, NULL, 0xffffffff);
		m_pSprite->End();
		pDeb->Draw();
		//�I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
