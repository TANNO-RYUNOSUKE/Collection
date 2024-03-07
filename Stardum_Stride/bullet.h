//==================
//�o���b�g�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _BULLET_H_//��d�C���N���[�h�h�~�̃}�N��
#define _BULLET_H_
//�C���N���[�h
#include "main.h"
#include "billboard.h"
#include "orbit.h"
#include "collision.h"
static D3DXCOLOR Col[] =
{
	D3DXCOLOR(0.5f,0.5f,0.5f,1.0f),
	D3DXCOLOR(0.5f,0.3f,0.75f,1.0f),
	D3DXCOLOR(1.0f,0.6f,0.25f,1.0f),
	D3DXCOLOR(0.3f,1.0f,0.7f,1.0f),
	D3DXCOLOR(0.6f,0.6f,1.0f,1.0f),
	D3DXCOLOR(1.0f,0.3f,0.3f,1.0f),
};
//�N���X��`
class CBullet : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CBullet(int nPriority = 2);
	CBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nLife);
	~CBullet();
	enum TYPE
	{
		TYPE_NONE =0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_MAX
	};
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CBullet * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE type);
	void SetLife(int nLife) { m_nLife = nLife; }
	
protected:
	TYPE m_Type;
	CSphereCollision * m_pColl;
	COrbit * m_pOrbit;
	COrbit * m_pOrbit2;
	CObject * m_pTarget;
	int m_nLife;//����
private:

	

};

class CMissile : public CBullet
{
public:
	CMissile();
	~CMissile();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMissile * Create(D3DXVECTOR3 pos, D3DXVECTOR3 vec, int nLife, TYPE type,float fSpeed,float fPower,CObject * Target);
	void Homing();
private:
	float m_fSpeed; 
	float m_fPower;
	CObject ** m_pTarget;
};
class CSwarm : public CBullet
{
public:
	CSwarm();
	~CSwarm();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSwarm * Create(D3DXVECTOR3 pos, D3DXVECTOR3 vec, int nLife, TYPE type, int nStop, CObject * Target);
	void Homing();
private:

	int m_nStop;

	CObject ** m_pTarget;
};

#endif // ! _BULLET_H_