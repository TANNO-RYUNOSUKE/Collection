//==================
//�E�F�[�uUI�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Wave_UI_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Wave_UI_H_
//�C���N���[�h
#include "main.h"
#include "number.h"

//�}�N����`
#define NUM_UINUMBER (2)//����
//�N���X��`
class CWave_UI :public CNumber
{
public:
	CWave_UI();

	~CWave_UI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CWave_UI * Create(void);

	void SetDisp(const int nCntDisp) { m_nCntDisp = nCntDisp; }
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(const int ndata) { m_ndata = ndata; }
private:
	CObject2D * m_pUi;
	CNumber * m_apNumber[NUM_UINUMBER]; //�i���o�[�I�u�W�F�N�g�ւ̃|�C���^
	int m_ndata;//�����Ă�����
	int m_nCntDisp;
	D3DXVECTOR3 m_pos;//�ꌅ�ڂ̍��W
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_Uipos1;
	D3DXVECTOR3 m_Uipos2;
	D3DXVECTOR3 m_Uisize1;
	D3DXVECTOR3 m_Uisize2;
	D3DXVECTOR3 m_NumberSize1;
	D3DXVECTOR3 m_NumberSize2;
};

#endif // ! _Wave_UI_H_