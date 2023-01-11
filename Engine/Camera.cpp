#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMVECTOR _UpDirection;
XMMATRIX _billBoard;
int _field_angle;

//////////�U���ɕK�v�ȕϐ�
float _vibrationQuantity;     //�U����
float _vibrationAttenuation;  //�U���̌���
bool  _vibrationFlag;         //�J������U�������邩�ǂ���
int   _sign;                  //����

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	ARGUMENT_INITIALIZE(_position,XMFLOAT3(ZERO, 50, -50));	            //�J�����̈ʒu
	ARGUMENT_INITIALIZE(_target,XMFLOAT3(ZERO, ZERO, ZERO));	        //�J�����̏œ_
	ARGUMENT_INITIALIZE(_UpDirection,XMVectorSet(ZERO, 1, ZERO, ZERO)); //�J�����̏�����̃x�N�g��
	ARGUMENT_INITIALIZE(_field_angle,45);                               //�J�����̉�p
	ARGUMENT_INITIALIZE(_vibrationFlag,false);                          //�J�����̐U��Off
	ARGUMENT_INITIALIZE(_vibrationQuantity, ZERO);                      //�U����
	ARGUMENT_INITIALIZE(_vibrationAttenuation,0.01);                    //�U���̌���
	ARGUMENT_INITIALIZE(_sign,1);                                       //����

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�J�����̐U�� 
	_target = Float3Add(_target,Vibration());

	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, ZERO),
		XMVectorSet(_target.x, _target.y, _target.z, ZERO), _UpDirection);

	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	_billBoard = XMMatrixLookAtLH(XMVectorSet(ZERO, ZERO, ZERO, ZERO), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), _UpDirection);
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//�J�����̐U��
XMFLOAT3 Camera::Vibration()
{
	//�U���ʂǂ�ǂ񌸂炵�Ă���
	if (abs(_vibrationQuantity) < 0.01)
		_vibrationQuantity = ZERO;
	else
		_vibrationQuantity = _sign * (abs(_vibrationQuantity) - _vibrationAttenuation);

	//�������΂�
	_sign *= -1;

	return XMFLOAT3(_vibrationQuantity, _vibrationQuantity, _vibrationQuantity);
}

//�œ_��ݒ�
void Camera::SetTarget(const XMFLOAT3& target) { _target = target;}

//�ʒu��ݒ�
void Camera::SetPosition(const XMFLOAT3& position) { _position = position; }

//������̃x�N�g����ݒ�
void Camera::SetUpDirection(XMVECTOR direction) { _UpDirection = direction; }

//��p��ݒ�
void Camera::SetFieldAngle(int angle) 
{
	//��p�X�V
	_field_angle = angle;
	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(_field_angle), (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�J�����U��
//���� : �U���̋���
void Camera::SetCameraVibration(float strength,float attenuation)
{
	//�����ݒ�
	ARGUMENT_INITIALIZE(_vibrationQuantity, strength);

	//�����ݒ�
	ARGUMENT_INITIALIZE(_vibrationAttenuation, attenuation);

	//������1�ɂ��Ă���
	ARGUMENT_INITIALIZE(_sign,1);

}

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }