//==================
//���b�V���t�B�[���h�w�b�_�[
//Author: �O�� ���V��
//==================
#ifndef  _Map_Editer_H_//��d�C���N���[�h�h�~�̃}�N��
#define _Map_Editer_H_
//�C���N���[�h
#include "main.h"
#include "objectX.h"
#include <string>

#define MAX_MAPOBJECT (64)
//�N���X��`
class CMap_Editer 
{
public:

	CMap_Editer();

	~CMap_Editer();

	struct MapObjects
	{
		std::string name;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	};

	virtual	HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);


	static CMap_Editer * Create();

	
	void Save(void);
	void SaveText(void);
	void Load(void);
	void LoadText(void);
private:
	CObjectX * m_pObject;
	MapObjects m_Map[MAX_MAPOBJECT];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nType;
};

#endif // ! _Map_Editer_H_
