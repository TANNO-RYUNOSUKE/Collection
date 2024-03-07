//==================
//�����_���[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _RENDERER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _RENDERER_H_
//�C���N���[�h
#include "main.h"

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

private:						
	LPDIRECT3D9 m_pD3D;						//direct3D�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//direct3D�f�o�C�X�ւ̃|�C���^
};

#endif // ! _RENDERER_H_
