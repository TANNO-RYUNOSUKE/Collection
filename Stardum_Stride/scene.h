//==================
//�V�[���w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _SCENE_H_//��d�C���N���[�h�h�~�̃}�N��
#define _SCENE_H_
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "pause.h"

//�O���錾
class CEnemyManager; //�G�l�~�[�}�l�[�W���[
class CInputKeyboard; //�L�[�{�[�h
class CInputGamePad;//�R���g���[���[
class CInputMouse;//�}�E�X
class CPlayer;//�v���C���[
class CEnemy;//�G�l�~�[
class CDebugProc;//�f�o�b�O
class CExplosion;//����
class CRenderer;//�����_���[
class CSound;//�T�E���h
class CScore;//�X�R�A
class CCamera;//�J����
class CLight;//���C�g
class CTexture;//�e�N�X�`��
class CMeshfield;//���b�V���t�B�[���h
class CFog;//�t�H�O
class CFade;//�t�F�[�h
class CWave;//�E�F�[�u
class CWave_UI;//�E�F�[�uUI
class CEnemy_UI;//�G�l�~�[UI
class CMap_Editer;
class CRankng;
class CObjectX;


//�N���X��`
class CScene :public CObject
{
public:
	CScene();
	~CScene();
	enum MODE
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	};
	virtual	HRESULT Init(void) = 0;
	virtual	void Uninit(void) = 0;
	virtual	void Update(void) = 0;
	virtual	void Draw(void) = 0;
	virtual void ScoreUp(int nScore) {};
	static CScene * Create(MODE mode);
	const void SetMode(MODE mode) { m_Mode = mode; }
	MODE GetMode(void) { return m_Mode; }
	static CFade * GetFade(void) { return m_pFade; }
	static CFade * m_pFade;
	virtual CPlayer * GetPlayer(void) { return NULL; }
	virtual CCamera * GetCamera(void) { return NULL; }
	virtual int GetWave() { return -1; }
	virtual CMeshfield * GetMeshfield(void) { return NULL; }
	int m_nFrame;
private:
	MODE m_Mode;
	
};


class CTitle:public CScene
{
public:
	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CCamera* GetCamera(void) { return m_pCamera; }
private:
	CObject2D * m_pTitle;
	CObject2D* m_pIcon[2];
	D3DXVECTOR3 m_posDest;
	CCamera* m_pCamera;//�J�����̃|�C���^
	CLight* m_pLight;//���C�g�̃|�C���^
};
class CTutorial :public CScene
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D * m_pTitle[2];
	int m_nDisp;
	int m_nCool;
};
class CResult :public CScene
{
public:
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CRankng *m_pRanking;
	CObject2D* m_pRank;
};

#define MAX_X (15000.0f)
#define MAX_Y (3000.0f)
#define MAX_Z (15000.0f)
class CGame :public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ScoreUp(int nScore);
	static void positionLimiter(D3DXVECTOR3 * pos);
	 CPlayer * GetPlayer(void) { return m_pPlayer; }
	 CMeshfield * GetMeshfield(void) { return m_pMeshfield; }
	 CCamera * GetCamera(void) { return m_pCamera; }

	 int GetWave() { return m_nWaveCount; }
	 void SetPlayer(CPlayer * pPlayer) { m_pPlayer = pPlayer; }
private:
	 CPause * m_pPause;
	 CPlayer * m_pPlayer;//�v���C���[�̃|�C���^
	 CObjectX* pSky;
	 CCamera * m_pCamera;//�J�����̃|�C���^
	 CLight * m_pLight;//���C�g�̃|�C���^
	 CMeshfield * m_pMeshfield;//���b�V���t�B�[���h�ւ̃|�C���^
	 int m_nEnemy;
	int m_nCnt;
	int m_nEnemyCount;
	int m_nWaveCount;

	bool b_Pause;//�|�[�Y
};



#endif // ! _SCENE_H_