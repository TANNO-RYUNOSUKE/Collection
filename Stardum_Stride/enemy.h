//==================
//�G�l�~�[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _ENEMY_H_//��d�C���N���[�h�h�~�̃}�N��
#define _ENEMY_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"

#include "motion.h"
#include "orbit.h"
#include "lifegage.h"
#include "collision.h"
#include "light.h"
#include "effekseerControl.h"
//�N���X��`
class CEnemy : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CEnemy();
	~CEnemy();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_TEST,
		TYPE_ARMY,
		TYPE_DRONE,
		TYPE_BOSS,
		TYPE_MAX
	};
	enum STATE
	{
		STATE_NONE = 0,
		STATE_DAMAGE,
		STATE_DEAD,
		STATE_MAX
	};

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CEnemy * Create(D3DXVECTOR3 pos,  int nLife);

	CModel *GetModel(void) { return m_apModel[0]; }

	bool GetShield() { return m_bShield; }
	void SetShield(bool bShield) { m_bShield = bShield; }
	void AddLife(int nAdd) { m_nLife += nAdd; }//���C�t�ɉ��Z
	virtual bool Damage(int nDamage, D3DXVECTOR3 knockback);
	void SetState(STATE state, int nCnt) { m_state = state,m_nStateCount = nCnt; }
	TYPE GetType() { return m_type; }
	D3DXVECTOR3 GetParentModelPos() { return D3DXVECTOR3(m_apModel[0]->GetMatrix()._41, m_apModel[0]->GetMatrix()._42, m_apModel[0]->GetMatrix()._43); }
	static Clist<CEnemy *> EnemyList;
protected:
	D3DXVECTOR3 posOld;
	STATE m_state;
	int m_nStateCount;
	float m_fdIstance;//�v���C���[�Ƃ̋���
	int m_nLife; //�̗�
	int m_nArmor;
	int m_nArmorMax;
	D3DXVECTOR3 m_posDest;
	D3DXVECTOR3 m_Force;
	D3DXVECTOR3 m_rotDest;
	CMotion * m_pMotion;//���[�V�����|�C���^
	CModel * m_apModel[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	CSphereCollision * m_pCollision;
	TYPE m_type;
	bool m_bShield;
private:
	
};
//�G�l�~�[(�e�X�g)
class CEnemy_TEST : public CEnemy
{
public:
	CEnemy_TEST();
	~CEnemy_TEST();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy_TEST * Create(D3DXVECTOR3 pos, int nLife);
private:
	
};


//�G�l�~�[(���s���)
class CEnemy_Walker : public CEnemy
{
public:
	CEnemy_Walker();
	~CEnemy_Walker();
	enum MOVE
	{
		MOVE_NONE = 0,
		MOVE_WALK,
		MOVE_DAMAGE,
		MOVE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy_Walker * Create(D3DXVECTOR3 pos, int nLife);
private:
	MOVE m_Move;

};

//�G�l�~�[(���)
class CEnemy_army : public CEnemy
{
public:
	CEnemy_army();
	~CEnemy_army();
	enum MOTION
	{
		MOTION_NONE = 0,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_DAMAGE,
		MOTION_DOWN,
		MOTION_MAX
	};
	enum ROUTINE
	{
		ROUTINE_WAIT = 0,
		ROUTINE_FORWARD,
		ROUTINE_BACK,
		ROUTINE_ATTACK,
		ROUTINE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Walk();
	void Attack();
	bool Damage(int nDamage, D3DXVECTOR3 knockback);
	static CEnemy_army * Create(D3DXVECTOR3 pos, int nLife);
	void SetRoutine(ROUTINE Routine, int nCnt) { m_Routine = Routine; m_nRoutineCount = nCnt; }
	
private:
	ROUTINE m_Routine;
	COrbit * m_pOrbit;
	int m_nRoutineCount;
	CSphereCollision * m_pAttackCollision;

};

//�G�l�~�[(���)
class CEnemy_Drone : public CEnemy
{
public:
	CEnemy_Drone();
	~CEnemy_Drone();
	
	enum ROUTINE
	{
		ROUTINE_WAIT = 0,
		ROUTINE_FORWARD,
		ROUTINE_BACK,
		ROUTINE_SATELLITE,
		ROUTINE_ATTACK,
		ROUTINE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Damage(int nDamage, D3DXVECTOR3 knockback);
	static CEnemy_Drone* Create(D3DXVECTOR3 pos, int nLife);
	void SetRoutine(ROUTINE Routine, int nCnt) { m_Routine = Routine; m_nRoutineCount = nCnt; }
private:
	ROUTINE m_Routine;
	COrbit* m_pOrbit;
	int m_nRoutineCount;
	CEnemy* m_pGuard;
	CEffekseer::CEffectData* m_pBarrier;
};
//�G�l�~�[(�{�X)
class CEnemy_Boss : public CEnemy
{
public:
	CEnemy_Boss();
	~CEnemy_Boss();
	enum MOTION
	{
		MOTION_NONE = 0,
		MOTION_ROTATION,
		MOTION_WALK,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_SPIN,
		MOTION_DOWN,
		MOTION_MAX
	};
	enum ROUTINE
	{
		ROUTINE_WAIT = 0,
		ROUTINE_FORWARD,
		ROUTINE_ROTATION,
		ROUTINE_ATTACK,
		ROUTINE_JUMP,

		ROUTINE_CHARGE,
		ROUTINE_FALLDOWN,
		ROUTINE_BEAM,
		ROUTINE_MAX
	};
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void Jump();
	
	void Charge();

	void Attack();
	void Spin();
	bool Damage(int nDamage, D3DXVECTOR3 knockback);
	static CEnemy_Boss * Create(D3DXVECTOR3 pos, int nLife);
	void SetRoutine(ROUTINE Routine, int nCnt) { m_Routine = Routine; m_nRoutineCount = nCnt; }
private:
	ROUTINE m_Routine;
	int m_nRoutineCount;
	int m_nCoolTime;
	bool m_bMotionLock;
	bool m_bLand;
	bool m_bTrigger;
	CGage * m_pGage;
	D3DXVECTOR3 m_vec;
	CSphereCollision * m_pAttackCollision;

};
#endif // ! _ENEMY_H_
