//==================
//3D�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Orbit_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Orbit_H_
//�C���N���[�h
#include "main.h"
#include "object.h"

//�N���X��`
class COrbit : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	COrbit(int nPriority = 6);

	~COrbit();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static COrbit * Create(int nLength, D3DXCOLOR col,D3DXVECTOR3 Offset1, D3DXVECTOR3 Offset2, D3DXMATRIX * pMtx,char * Tex = NULL,int nPriority = 5);


	void end(void) { m_bEnd = true; }
	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	COrbit * Get3D(void) { return this; }
	LPDIRECT3DTEXTURE9 * GetTex(void) { return &m_pTexture; }
	LPDIRECT3DVERTEXBUFFER9 * GetBuff(void) { return &m_pVtxBuff; }
	void SetOffset(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2) { m_Offset1 = pos1; m_Offset2 = pos2; }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetPosOld() { return m_posOld; }
protected:
	//�|���S���\���p
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
private:

	int m_nLength;//����
	D3DXVECTOR3 * m_pPosOld;//���W�L�^�p
	D3DXVECTOR3 m_Offset1;//���W
	D3DXVECTOR3 m_Offset2;//���W
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	D3DXMATRIX * m_pMtx; 
	int m_nTex;
	D3DXCOLOR m_col;
	bool m_bEnd;
	bool m_bDisp;
	int m_nLife;
};

#endif // ! _Orbit_H_
