//==================
//���b�N�I���}�[�J�[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _LOCKONMARKER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _LOCKONMARKER_H_
//�C���N���[�h
#include "main.h"
#include "billboard.h"

//�N���X��`
class CMarker : public CBillboard //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CMarker(int nPriority = 7);
	~CMarker();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetPosdest(D3DXVECTOR3 pos) { m_posDest = pos; }
	void SetDisp(bool bDisp) { m_bDisp = bDisp; }
	bool GetDisp(void) { return m_bDisp; }
private:
	
	bool m_bDisp;
	D3DXVECTOR3 m_posDest;
};

//�N���X��`
class CLockonmarker : public CMarker //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CLockonmarker();
	~CLockonmarker();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

//�N���X��`
class CJumpmarker : public CMarker //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CJumpmarker();
	~CJumpmarker();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif // ! _LOCKONMARKER_H_