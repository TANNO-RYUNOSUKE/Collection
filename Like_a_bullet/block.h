//==================
//�o���b�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _BLOCK_H_//��d�C���N���[�h�h�~�̃}�N��
#define _BLOCK_H_
//�C���N���[�h
#include "main.h"
#include "object2D.h"

//�N���X��`
class CBlock : public CObject2D //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CBlock(int nPriority = 2);
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBlock * Create(D3DXVECTOR3 pos);

	static HRESULT Load(void);
	static void Unload(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

private:
	bool Collision();

	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^

};

#endif // ! _BLOCK_H_