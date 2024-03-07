//==================
//�v���C���[�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _PLAYER_H_//��d�C���N���[�h�h�~�̃}�N��
#define _PLAYER_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
#include "orbit.h"
#include "collision.h"
#include "enemy.h"
#include "billboard.h"
#include "animbillboard.h"
#include "object2D.h"

#include "lifegage.h"
#include <vector>
//�}�N����`
#define GRAVITY (0.4f)
#define SCORE_BORDER (300)
#define WALK_SPEED (0.18f)
#define DASH_SPEED (1.0f)
#define ENERGY_MAX (3.0f)
#define PLAYERLIFE_MAX (150)
//�N���X��`
class CPlayer : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CPlayer(int nPriority = 6);
	~CPlayer();

	typedef enum 
	{
		MOTION_NONE = -1,
		MOTION_NEUTRAL,
		MOTION_WALK,
		MOTION_DASH,
		MOTION_DODGE,
		MOTION_JUMP,
		
		MOTION_COMBINATION1,
		MOTION_COMBINATION2,
		MOTION_COMBINATION3,
		MOTION_COMBINATION4,

		MOTION_COMBINATION_B1,
		MOTION_COMBINATION_B2,
		
		MOTION_COMBINATION_C1,
		MOTION_COMBINATION_C2,
		MOTION_COMBINATION_C3,
		MOTION_COMBINATION_C4,

		MOTION_CHARGE,
		MOTION_STREAK,
		MOTION_HIGHROLLER,
		MOTION_SPLIT,
		MOTION_PAYLINE,

		MOTION_DAMAGE,
		MOTION_MAX
	}MOTION;



	typedef enum 
	{
		STATE_NONE = 0,
		STATE_NEUTRAL,
		STATE_DASH,
		STATE_HOVER,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer * Create(void);

	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	void SetLand(bool bLand) { m_bLand = bLand; }

	void AddLife(int nAdd) { m_nLife += nAdd; }
	int GetLife() { return m_nLife; }
	D3DXVECTOR3 GetAttackPos() { return m_attackpos; }
	CModel * GetModel(int nData = 0) { return m_apModel[nData]; }
	CEnemy * GetTarget() { if (m_pEnemy != NULL) { return *m_pEnemy; } else { return NULL; } }
	void StylishRank();

	//���[�V�����n
	void Action();
	void Command();
	void Walk();
	void Dash();
	void Jump();
	void Attack1();
	void Attack2();
	void Attack3();
	void Attack4();
	void AttackB1();
	void AttackB2();
	void AttackC1();
	void AttackC2();
	void AttackC3();
	void AttackC4();
	void Charge();
	void Streak();
	void Highroller();
	void Split();
	void Payline();
	void Down();
	void Dodge();
	void DeletCollision();
	void AutoCollisionCreate();
	void Direction();
	void Mirage();
	void Lockon();

	bool Damage(int Damage, D3DXVECTOR3 Knockback);
	void ScoreUp();
	CSphereCollision * GetHitCol() { return m_pHitCol; }
	void SetLog(MOTION motion);
	int GetActionLogCount();
	int GetRank() { return m_nRank; }
private:
	
	int m_nLife;//�̗�

	CMotion * m_pMotion;//���[�V�����|�C���^
	COrbit *  m_pOrbit;
	D3DXVECTOR3 m_Force;//�O��
	D3DXVECTOR3 m_posOld;//1�t���[���O�̍��W
	D3DXVECTOR3 m_rotDest;
	D3DXVECTOR3 m_rotShot; //�ˌ�����
	D3DXVECTOR3 m_attackpos;
	D3DXVECTOR3 m_PaylineVec;
	bool m_bLand;//���n���� ���ǂ���
	int m_nLand;
	int m_nComboB;
	bool m_bMotionLock;
	bool m_bKey;
	CModel * m_apModel[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	int m_nNumModel;//�g�p���郂�f���̐�
	int   m_nDamage;
	float m_fPower;
	float m_Size;
	int m_nMovecount;
	CEnemy ** m_pEnemy;
	CSphereCollision * m_pColl;
	CSphereCollision * m_pHitCol;
	CObject2D * m_pRank;
	CObject2D * m_pScoreGage;
	CAnimBillboard * m_pTarget;
	int m_nScore;
	int m_nRank;
	int m_nRankOld;
	int m_nHike;
	CGage * pGage;
	std::vector<MOTION> m_vActionLog;

};

#endif // ! _PLAYER_H_
