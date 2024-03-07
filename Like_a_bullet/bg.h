//==================
//BG�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _BG_H_//��d�C���N���[�h�h�~�̃}�N��
#define _BG_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"

//�}�N����`
#define NUM_BG (3) //�w�i�̐�

//�N���X��`
class CBg : public CObject2D //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CBg();
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg * Create(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_BG]; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR2 m_aTexUV[NUM_BG];//�e�N�X�`�����W
	
};

#endif // ! _BG_H_
