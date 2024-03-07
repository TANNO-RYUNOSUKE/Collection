//========================================================================================
//
// �t�H�O�w�b�_�[[fog.h]
// Author: �O�� ���V��
//
//========================================================================================
#ifndef _FOG_H_
#define _FOG_H_
#include "main.h"

class CFog
{
public:
	CFog();
	~CFog();
	
	//�v���g�^�C�v�錾
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(D3DFOGMODE FogMode, D3DXCOLOR FogColor, float FogStart, float FogEnd, float FogDensity);
private:
	D3DFOGMODE m_FogMode;	//�t�H�O�̃��[�h
	D3DXCOLOR m_FogColor;	//�t�H�O�̐F
	float m_FogStart;		//�t�H�O�̊J�n�n�_
	float m_FogEnd;		//�t�H�O�̏I���n�_
	float m_FogDensity;	//�t�H�O�̖��x
};




#endif // !_FOG_H_
