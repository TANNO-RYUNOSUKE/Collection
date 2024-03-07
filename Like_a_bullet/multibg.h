//==================
//MultiBg�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _MULTIBG_H_//��d�C���N���[�h�h�~�̃}�N��
#define _MULTIBG_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"

//�}�N����`
#define NUM_MULTIBG (3) //�w�i�̐�

//�O���錾
class CObject2D;

//�N���X��`
class CMultiBg : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CMultiBg();
	~CMultiBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void Unload(void);

	static CMultiBg * Create(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeight, float fWidth);
	void BindTexture();
private:
	static CObject2D * m_apObject2D[NUM_MULTIBG];//2d�I�u�W�F�N�g
	static LPDIRECT3DTEXTURE9 m_paTexture[NUM_MULTIBG];	//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR2 m_aTexUV;//�e�N�X�`�����W
};

#endif // ! _MULTIBG_H_
