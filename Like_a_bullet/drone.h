//==================
//3D�I�u�W�F�N�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Drone_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Drone_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "objectX.h"
#include "line.h"
#include "orbit.h"
//�N���X��`
class CDrone : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:

	CDrone(int nPriority = 0);

	~CDrone();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CDrone * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 3);
private:
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rotDest;
	CObjectX * m_pObjectX;
	CLine * m_pLine;
	COrbit * m_pOrbit;//�O��
	COrbit * m_pOrbit2;//�O��2
};

#endif // ! _Drone_H_
