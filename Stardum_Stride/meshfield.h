//==================
//���b�V���t�B�[���h�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _MESHFIELD_H_//��d�C���N���[�h�h�~�̃}�N��
#define _MESHFIELD_H_
//�C���N���[�h
#include "main.h"
#include "object.h"

//�N���X��`
class CMeshfield : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CMeshfield(int nPriority = 0);

	~CMeshfield();

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	float GetHeight(void) { return m_fHeight; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	float GetWidth(void) { return m_fWidth; }

	static CMeshfield * Create(float fHeight, float fWidth, int nU,int nV,D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	bool MeshRay(const D3DXVECTOR3 & Start, const D3DXVECTOR3 & End);
	bool Collision(D3DXVECTOR3 * ppos);
	void Save(void);
	void Load(void);
	CMeshfield * Get3D(void) { return this; }
	LPDIRECT3DTEXTURE9 * GetTex(void) { return &m_pTexture; }
	LPDIRECT3DVERTEXBUFFER9 * GetBuff(void) { return &m_pVtxBuff; }

private:
	//�|���S���\���p
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	PDIRECT3DINDEXBUFFER9 m_pIdxBuff; //�C���f�b�N�X�o�b�t�@
	float m_fHeight;	//����
	float m_fWidth;		//��
	int m_nSplit_V;//�c�̕�����
	int m_nSplit_U;//���̕�����
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X


};

#endif // ! _MESHFIELD_H_
