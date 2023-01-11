#pragma once
#include "Direct3D.h"

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

//////�p�x

//0�x
#define ZEROPI_DEGREES  0

//360�x
#define TWOPI_DEGREES  360

//////������

//0�ɏ�����
#define ZERO_INITIALIZE(p) { p = 0;}

//1�ɏ�����
#define ONE_INITIALIZE(p) { p = 1;}

//�����ŏ�����
#define ARGUMENT_INITIALIZE(p,t){ p = t;}

//////�萔

//0�Ȃ�
#define ZERO 0.0f

//��̃x�N�g��
static const XMVECTOR UP_VECTOR = { 0,1,0,0 };

//���̃x�N�g��
static const XMVECTOR DOWN_VECTOR = { 0,-1,0,0 };

//���̃x�N�g��
static const XMVECTOR LEFT_VECTOR = { -1,0,0,0 };

//�E�̃x�N�g��
static const XMVECTOR RIGHT_VECTOR = { 1,0,0,0 };

//�O�̃x�N�g��
static const XMVECTOR STRAIGHT_VECTOR = { 0,0,1,0 };

//���̃x�N�g��
static const XMVECTOR BACK_VECTOR = { 0,0,-1,0 };


//////�֐�

//XMFLOAT3���m�������Z���Ă����(������ - ������)
static XMFLOAT3 SubTract(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

//XMFLOAT3���m�𑫂��Ă����
static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

//���������߂Ă����
static float RangeCalculation(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 c = SubTract(a, b);

	return sqrtf((c.x * c.x) +
		         (c.y * c.y) +
		         (c.z * c.z));
}

//XMVECTOR�̕ϐ���XMFLOAT3�ɕς��ĕԂ��Ă����
static XMFLOAT3 VectorToFloat3(XMVECTOR v)
{
	XMFLOAT3 a;
	XMStoreFloat3(&a, v);

	return a;
}

//ini�t�@�C������float�^�̕ϐ�������Ă���
static float GetPrivateProfilefloat(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault,LPCTSTR lpFileName)
{
	char caption[64];
	int len = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, caption, 64, lpFileName);

	//��񂪎��Ă���Ȃ�
	if (len)
		return strtof(caption, NULL);   //���������Ԃ�
	else
		return strtof(lpDefault, NULL); //Default�̏���Ԃ�
}