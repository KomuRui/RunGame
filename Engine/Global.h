#pragma once
#include "Direct3D.h"
#include <sstream>
#include <iomanip>

using namespace std;

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

//XMVECTOR�̕ϐ���XMFLOAT3�ɕς��ĕԂ��Ă����
static XMFLOAT3 VectorToFloat3(XMVECTOR v)
{
	XMFLOAT3 a;
	XMStoreFloat3(&a, v);

	return a;
}

//���������߂Ă����
static float RangeCalculation(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 c = SubTract(a, b);

	return sqrtf((c.x * c.x) +
		         (c.y * c.y) +
		         (c.z * c.z));
}

//���������߂Ă����
static float RangeCalculation(XMVECTOR a, XMVECTOR b)
{
	return  RangeCalculation(VectorToFloat3(a), VectorToFloat3(b));
}

//�����_��(a�ȏ�b�ȉ��̃����_���̒l���o��)
static int Random(int a, int b)
{
	int num = (b - a) + 1;

	return (rand() % num) + a;
}

//�x�N�g����0���ǂ���
static bool VectorNotZero(XMVECTOR a)
{
	return (XMVectorGetX(a) == 0 && XMVectorGetY(a) == 0 && XMVectorGetZ(a) == 0 && XMVectorGetW(a) == 0);
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

static std::string float_to_string(float f, int digits)
{
	ostringstream oss;

	oss << setprecision(digits) << setiosflags(ios::fixed) << f;

	return oss.str();

}