//==================
//3D�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Line_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Line_H_
//�C���N���[�h
#include "main.h"
#include "object.h"

//�N���X��`
class CLine : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CLine(int nPriority = 5);

	~CLine();

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CLine * Create(D3DXVECTOR3 start, D3DXVECTOR3 end,D3DXCOLOR col, int nPriority = 5);

	CLine * GetLine(void) { return this; }
	void SetStart(D3DXVECTOR3 pos) { m_start = pos; }
	void SetEnd(D3DXVECTOR3 pos) { m_end = pos; }
	void SetEndDest(D3DXVECTOR3 pos) { m_endDest = pos; }
	D3DXVECTOR3 GetEnd(void) { return m_end; }
	D3DXVECTOR3 GetStart(void) { return m_start; }
protected:
	//�|���S���\���p

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff2;		//���_�o�b�t�@
private:
	float m_fHeight;	//����
	float m_fWidth;		//
	D3DXVECTOR3 m_start;
	D3DXVECTOR3 m_end;
	D3DXVECTOR3 m_endDest;
	D3DXCOLOR col;
};

#endif // ! _Line_H_
