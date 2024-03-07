//==================
//�o���b�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Collision_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Collision_H_
//�C���N���[�h
#include "main.h"
#include "billboard.h"
#include "orbit.h"

//�N���X��`
class CCollision : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CCollision(int nPriority = 2);
	~CCollision();
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCollision * Create(D3DXVECTOR3 pos,int nDamage, TYPE type);

	bool CollisionEnemy(D3DXVECTOR3 pos);
	bool CollisionPlayer(D3DXVECTOR3 pos);
private:
	TYPE m_Type;
	int m_nDamage;
	bool  m_bactive;
};

#endif // ! _Collision_H_