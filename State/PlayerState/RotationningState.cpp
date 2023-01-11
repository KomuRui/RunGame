#include "RotationningState.h"
#include "../../Engine/Input.h"
#include "../../Manager/GameManager/GameManager.h"
#include "PlayerStateManager.h"
#include "../../Engine/Model.h"
#include "../../Manager/EffectManager/PlayerEffectManager/PlayerEffectManager.h"

//�萔
namespace
{
	static const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");	//FPS
	static const int NORMAL_ROTATION_ANGLE = 1;       //��]����Ƃ��̉��Z����p�x
	static const float ROTATION_ATTENUATION = 0.015f; //��]�̌���
	static const float HIT_DISTANCE_2D = 1.0f; //���C�̓�����������(2D)
	static const float HIT_DISTANCE    = 0.9f; //���C�̓�����������(3D)
}

//�X�V
void RotationningState::Update2D(Player* player)
{
	//���Ƀ��C���΂�
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(DOWN_VECTOR);
	Model::RayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//���C�̓�������������1.0f��菬�����Ȃ�
	if (dataNormal.dist < HIT_DISTANCE_2D)
	{
		dataNormal.pos.y += HIT_DISTANCE_2D;
		GameManager::GetpPlayer()->SetPosition(dataNormal.pos);
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(GameManager::GetpPlayer()->GetPlayerhModel());

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= FPS)
	{
	    //��]��~
		ARGUMENT_INITIALIZE(rotationCount_,ZERO);

		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	//rotationCount1�����₷
	rotationCount_++;

	HandleInput(player);
}

//3D�p�X�V
void RotationningState::Update3D(Player* player)
{
	RayCastData dataNormal;
	dataNormal.start = GameManager::GetpPlayer()->GetPosition();
	dataNormal.dir = VectorToFloat3(GameManager::GetpPlayer()->GetDown());
	Model::AllRayCast(GameManager::GetpStage()->GethModel(), &dataNormal);

	//��������������0.9f��菬�����Ȃ�
	if (dataNormal.dist < HIT_DISTANCE)
	{
		//�n�`�ɍ������킹��
		GameManager::GetpPlayer()->SetPosition(VectorToFloat3(XMLoadFloat3(&dataNormal.pos) + GameManager::GetpPlayer()->GetNormal()));
		GameManager::GetpPlayer()->SetAcceleration(1);
	}

	//�G�t�F�N�g�̕\��
	PlayerEffectManager::RotationEffect(GameManager::GetpPlayer()->GetPlayerhModel());

	//Player�̏㎲������]������
	GameManager::GetpPlayer()->SetAngle(GameManager::GetpPlayer()->GetAngle() + (NORMAL_ROTATION_ANGLE - (rotationCount_ * ROTATION_ATTENUATION)));

	//������]���n�߂Ă���60�t���[���ȏオ�o�߂��Ă���Ȃ�
	if (rotationCount_ >= FPS)
	{
		//��]��~
		ARGUMENT_INITIALIZE(rotationCount_, ZERO);

		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerStanding_;
	}

	//rotationCount1�����₷
	rotationCount_++;

	HandleInput(player);
}

//���͂ɂ���ď�ԕω�����
void RotationningState::HandleInput(Player* player)
{
	//�W�����v��ԂɕύX
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		//��ԕύX
		PlayerStateManager::playerState_ = PlayerStateManager::playerJumping_;
		PlayerStateManager::playerState_->Enter(player);
	}
}

//��ԕω������Ƃ���񂾂��Ă΂��֐�
void RotationningState::Enter(Player* player)
{
	//0�ɏ�����
	ZERO_INITIALIZE(rotationCount_);
}