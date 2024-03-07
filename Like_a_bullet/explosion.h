//==================
//�G�N�X�v���[�W�����w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _EXPLOSION_H_//��d�C���N���[�h�h�~�̃}�N��
#define _EXPLOSION_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"

//�N���X��`
class CExplosion : public CObject2D //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CExplosion * Create(D3DXVECTOR3 pos);

	static HRESULT Load(void);
	static void Unload(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	int m_nCountAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
};

#endif // ! _EXPLOSION_H_
