//==================
//�X�R�A�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Score_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Score_H_
//�C���N���[�h
#include "main.h"
#include "number.h"

//�}�N����`
#define NUM_NUMBER (8)//����
//�N���X��`
class CScore:public CNumber
{
public:
	CScore();

	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore * Create(void);

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const int ndata) { m_ndata = ndata; }
	void Add(const int ndata) { m_ndata += ndata; }
	int GetScore(void) { return m_ndata; }

private:
	CNumber * m_apNumber[NUM_NUMBER]; //�i���o�[�I�u�W�F�N�g�ւ̃|�C���^
	int m_ndata;//�����Ă�����
	D3DXVECTOR3 m_pos;//�ꌅ�ڂ̍��W
};

#endif // ! _Score_H_
