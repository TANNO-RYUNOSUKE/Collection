//==================
//�E�F�[�uUI�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Enemy_UI_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Enemy_UI_H_
//�C���N���[�h
#include "main.h"
#include "number.h"

//�}�N����`
#define NUM_E_UINUMBER (2)//����
//�N���X��`
class CEnemy_UI :public CNumber
{
public:
	CEnemy_UI();

	~CEnemy_UI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy_UI * Create(void);

	
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const int ndata) { m_ndata = ndata; }
private:
	CObject2D * m_pUi;
	CNumber * m_apNumber[NUM_E_UINUMBER]; //�i���o�[�I�u�W�F�N�g�ւ̃|�C���^
	int m_ndata;//�����Ă�����
	D3DXVECTOR3 m_pos;//�ꌅ�ڂ̍��W
};

#endif // ! _Enemy_UI_H_