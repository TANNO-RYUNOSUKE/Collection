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
#include "enemy.h"
#include "lockonmarker.h"
#include "orbit.h"
#include "line.h"
#include "object2D.h"
//�}�N����`
#define GRAVITY (1.0f)

#define MAX_LOCK (12)
#define MAX_LANGE (20000.0f)
//�N���X��`
class CPlayer : public CObject //�I�u�W�F�N�g�N���X�̌p��
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	typedef enum 
	{
		UPPERMOTION_NONE = -1,
		UPPERMOTION_NEUTRAL,
		UPPERMOTION_WALK,
		UPPERMOTION_SHOT,
		UPPERMOTION_ATTACK1,
		UPPERMOTION_ATTACK2,
		UPPERMOTION_ATTACK3,
		UPPERMOTION_MAX
	}UPPERMOTION;

	typedef enum
	{
		LOWERMOTION_NONE = -1,
		LOWERMOTION_NEUTRAL,
		LOWERMOTION_WALK,
		LOWERMOTION_STOP,
		LOWERMOTION_JUMP,
		LOWERMOTION_ATTACK1,
		LOWERMOTION_ATTACK2,
		LOWERMOTION_ATTACK3,
		LOWERMOTION_MAX
	}LOWERMOTION;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer * Create(void);

	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	void SetLand(bool bLand) { m_bLand = bLand; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	void AddLife(int nAdd) { m_nLife += nAdd; }
	int GetLife() { return m_nLife; }
	void Move(void);
	void LockOn(void);
	void SetFilterDisp(int nCnt) { m_nFilter = nCnt; }
	void Melee(D3DXVECTOR3 pos);
	CEnemy ** GetJump() { return m_pEnemyJump; }
	//CEnemy * GetLockEnemy(void) { return m_pLockOnEnemy; }
	float CheckEnemyAngle(const D3DXVECTOR3& cameraDirection, const D3DXVECTOR3& enemyDirection);
	static D3DXVECTOR3 LinePrediction(D3DXVECTOR3 shotPosition, D3DXVECTOR3 targetPosition, D3DXVECTOR3 targetPrePosition, float bulletSpeed);
	static float PlusMin(float a, float b);
	void BulletJump(void);
	CModel * GetModelUp(void) { return m_apModelUp[0]; }
private:
	int m_nBoost;
	int m_nFilter;
	int m_anDash[4];//�_�b�V���p�J�E���g
	bool m_bDash;
	CObject2D * m_pFilterDamage;
	//CLockonmarker * m_pLockmark[MAX_LOCK];//�}�[�J�[
	//CEnemy * m_pLockOnEnemy;//���b�N�I�������G
	int m_nLock;//���b�N�I���̐�
	int m_nLockCount;//���b�N�I������
	CEnemy ** m_pEnemy[MAX_LOCK];//���b�N�I�����̔z��
	CEnemy ** m_pEnemyJump;//���b�N�I��(�o���b�g�W�����v)
	int m_nCntLockEnemy;//�G�̐�
	int m_nLife;//�̗�
	CMotion * m_pMotionUp;//���[�V�����|�C���^
	CMotion * m_pMotionLow;//���[�V�����|�C���^
	D3DXVECTOR3 m_posOld;//1�t���[���O�̍��W
	D3DXVECTOR3 m_rotShot; //�ˌ�����
	bool m_bLand;//���n�������ǂ���
	CModel * m_apModel[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	CModel * m_apModelUp[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	CModel * m_apModelLow[NUM_MODEL];//�g�p���郂�f���̃|�C���^
	int m_nNumModel;//�g�p���郂�f���̐�
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	COrbit * m_pOrbit;//�O��
	COrbit * m_pOrbitJump;//�O��2
	bool m_bLockon; //���b�N�I�����Ă��邩�ǂ���
	int Scorebonus;
	
};

#endif // ! _PLAYER_H_