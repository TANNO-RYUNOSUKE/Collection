#include "Supporter.h"

// �x�N�g�����p�x�ɕϊ�����֐�
D3DXVECTOR3 VectorToAngles(const D3DXVECTOR3& vector)
{
	D3DXVECTOR3 angles;

	// Yaw�i���[�j���v�Z
	angles.y = atan2f(vector.x, vector.z);

	// Pitch�i�s�b�`�j���v�Z
	angles.x = atan2f(vector.y, sqrt(vector.x * vector.x + vector.z * vector.z));

	// Roll�i���[���j��0�x�ɐݒ�
	angles.z = 0.0f;



	return angles;
}

// �p�x���x�N�g���ɕϊ�����֐�
D3DXVECTOR3 AnglesToVector(const D3DXVECTOR3& angles)
{
	D3DXVECTOR3 vector;

	// ���W�A����x�ɕϊ�
	float yaw = (angles.y);
	float pitch = (angles.x);

	// �x�N�g�����v�Z
	vector.x = sinf(yaw) * cosf(pitch);
	vector.y = sinf(pitch);
	vector.z = cosf(yaw) * cosf(pitch);

	return vector;
}

float ComparisonAngle(const D3DXVECTOR3& Direction1, const D3DXVECTOR3& Direction2)
{
	// �x�N�g���̐��K��
	D3DXVECTOR3 normalizedCameraDir, normalizedEnemyDir;
	D3DXVec3Normalize(&normalizedCameraDir, &Direction1);
	D3DXVec3Normalize(&normalizedEnemyDir, &Direction2);
	// �x�N�g���̓��ς��v�Z
	float dotProduct = D3DXVec3Dot(&normalizedCameraDir, &normalizedEnemyDir);
	float fAnswer = acosf(dotProduct) * (180.0f / D3DX_PI);
	if (fAnswer < 0.0f)
	{
		fAnswer *= -1;
	}
	// ���W�A������x���@�ɕϊ����ĕԂ�
	return fAnswer;
}

//=============================================
//�����擾�֐�
//=============================================
float GetDistance(D3DXVECTOR3 vec)
{
	if (vec.x < 0.0f)
	{
		vec.x *= -1.0f;
	}
	if (vec.y < 0.0f)
	{
		vec.y *= -1.0f;
	}
	if (vec.z < 0.0f)
	{
		vec.z *= -1.0f;
	}
	float fDis = vec.x + vec.y + vec.z;
	return fDis;
}

float GetAngleDifference(const D3DXVECTOR3& vec1, const D3DXVECTOR3& vec2)
{
	// �x�N�g���𐳋K�����܂��B
	D3DXVECTOR3 v1, v2;
	D3DXVec3Normalize(&v1, &vec1);
	D3DXVec3Normalize(&v2, &vec2);

	// �h�b�g�ς��v�Z���āA�p�x�����߂܂��B
	float dotProduct = D3DXVec3Dot(&v1, &v2);
	float angle = acosf(dotProduct);
	if (angle < 0.0f)
	{
		angle *= -1.0f;
	}
	// �p�x�̍���Ԃ��܂��B
	return angle;
}