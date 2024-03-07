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
#include "lockonmarker.h"
#include "motion.h"
#include "orbit.h"

class CHitBox //�}�l�[�W���N���X
{
public:
	CHitBox();
	~CHitBox();

	static CHitBox * Create(D3DXVECTOR3 max, D3DXVECTOR3 min, D3DXVECTOR3 pos, CHitBox * pNext = NULL);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetMax() { return m_max; }
	D3DXVECTOR3 GetMin() { return m_min; }
	CHitBox * GetNext() { return m_pNext; }
	void SetShot(int nShot) { m_nShot = nShot; }
	void SetNext(CHitBox * pHitBox) { m_pNext = pHitBox; }
	int GetShot() { return m_nShot; }
private:
	int m_nShot;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_pos;
	CHitBox * m_pNext;
};

//�N���X��`
class CEnemy : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CEnemy();
	~CEnemy();

	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_WALKER,
		TYPE_DORONE,
		TYPE_ELITE,
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

	float GetDis(void) { return m_fdIstance; }
	void SetStag(bool bStag) { m_bStag = bStag; }
	bool GetStag(void) { return m_bStag; }
	void AddLife(int nAdd) { m_nLife += nAdd; }//���C�t�ɉ��Z
	void SetLock(bool bLock);
	CEnemy * GetThis() { return this; }

	void SetID(int nID) { m_nID = nID; }
	int GetID(void) { return m_nID; }
	void SetState(STATE State, int nCount) { m_State = State; m_nStateCount = nCount; }
	STATE GetState(void) { return m_State; }
	void Release(void);
	CHitBox * GetHitBox() { return pHitBox; }
protected:
	STATE m_State;
	D3DXVECTOR3 posOld;
	int m_nStateCount;
	float m_fdIstance;//�v���C���[�Ƃ̋���
	int m_nLife; //�̗�
	bool m_bStag;//�o���b�g�W�����v�̑Ώ�
	bool m_bLocked;//���b�N����Ă��邩
	D3DXVECTOR3 m_posDest;
	D3DXVECTOR3 m_rotDest;
	CMotion * m_pMotion;//���[�V�����|�C���^
	CModel * m_apModel[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	CHitBox * pHitBox;
	int m_nCoolTime;
private:

	//CModel * m_pModel;//���f���̃|�C���^
	

	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X

	CJumpmarker * m_pMark;//�}�[�J�[
	CLockonmarker * m_pLockMark;//�}�[�J�[
	CBillboard * m_pPointMark;
	
	int m_nID;//ID
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
		MOVE_ATTACK,
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
//�G�l�~�[(drone)
class CEnemy_Drone : public CEnemy
{
public:
	CEnemy_Drone();
	~CEnemy_Drone();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy_Drone * Create(D3DXVECTOR3 pos, int nLife);
private:
	float m_fRot;
	float m_fLength;
	int m_nHeat;
	int m_nMaxHeat;
	int m_nCount;
	bool m_bOverHeat;
};

//�G�l�~�[(�G���[�g)
class CEnemy_Elite : public CEnemy
{
public:
	CEnemy_Elite();
	~CEnemy_Elite();
	typedef enum
	{
		ENEMYELITE_MOTION_NEUTRAL = 0,
		ENEMYELITE_MOTION_ACT,
		ENEMYELITE_MOTION_MAX
	}ENEMYELITE_MOTION;
	typedef enum
	{
		ACT_NONE = 0,
		ACT_L,
		ACT_R,
		ACT_F,
		ACT_B,
		ACT_UP,
		ACT_DOWN,
		ACT_MAX
	}ACT;
	typedef enum
	{
		ENEMYE_STATE_NONE = 0,
		ENEMYE_STATE_ACT,
		ENEMYE_STATE_ATTACK,
		ENEMYE_STATE_MAX
	}ENEMYE_STATE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy_Elite * Create(D3DXVECTOR3 pos, int nLife);
private:
	int m_nActCount;
	int m_nCooling;
	ENEMYE_STATE m_State;
	ACT m_Act;
	int m_nActCounter;
	COrbit * m_pOrbit;//�O��
	COrbit * m_pOrbit2;//�O��2
};

//�G�l�~�[(�G���[�g)
class CEnemy_Boss : public CEnemy
{
public:
	CEnemy_Boss();
	~CEnemy_Boss();
	typedef enum
	{
		MODE_NEUTRAL = 0,
		MODE_ACT,
		MODE_MAX
	}MODE;
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy_Boss * Create(D3DXVECTOR3 pos, int nLife);
private:
	int m_nActCount;
	int m_nAttack;
	int m_nCooling;
	int m_nActCounter;
	COrbit * m_pOrbit;//�O��
	COrbit * m_pOrbit2;//�O��2
	MODE m_Mode;
	int m_nBitID[15];
};
//�G�l�~�[(Bit)
class CEnemy_Bit : public CEnemy
{
public:
	CEnemy_Bit();
	~CEnemy_Bit();
	typedef enum
	{
		MODE_NEUTRAL = 0,
		MODE_ACT,
		MODE_MAX
	}MODE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	MODE GetMode() { return m_mode; }
	void SetPosDest(D3DXVECTOR3 pos) { m_posDest = pos; }
	void SetMode(MODE mode, int nCnt) { m_mode = mode; m_nModeCount = nCnt; }
	static CEnemy_Bit * Create(D3DXVECTOR3 pos, int nLife);
	void Boom() { m_bBom = true; }
private:
	MODE m_mode;
	int m_nModeCount;
	float m_fRot;
	float m_fLength;
	int m_nHeat;
	int m_nMaxHeat;
	int m_nCount;
	bool m_bOverHeat;
	bool m_bBom;
	COrbit * m_pOrbit;//�O��
};

#endif // ! _ENEMY_H_
