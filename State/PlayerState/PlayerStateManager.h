#pragma once
#include "../../Engine/Input.h"
#include "PlayerState.h"
#include "../../Engine/Global.h"
#include "JumpingState.h"
#include "JumpRotationningState.h"
#include "RotationningState.h"
#include "RunningState.h"
#include "StandingState.h"
#include "WalkingState.h"

//��`
class Player;

//Player�̏�Ԃ̊��N���X
class PlayerStateManager : public PlayerState
{
private:

	//�L�����̑O�����̃x�N�g��
	XMVECTOR front_;                        

public:

	//��Ԃ������ϐ�
	static PlayerState* playerState_;

	//�e��ԕϐ�
	static JumpingState*          playerJumping_;             //�W�����v
	static JumpRotationningState* playerJumpRotationning_;    //�W�����v��]
	static RotationningState*     playerRotationning_;		  //��]
	static RunningState*          playerRunning_;		      //����
	static StandingState*		  playerStanding_;			  //�����Ă�
	static WalkingState* 		  playerWalking_;			  //����

    //�R���X�g���N�^
	PlayerStateManager();

	//2D�p�X�V
	virtual void Update2D(Player* player);

	//3D�p�X�V
	virtual void Update3D(Player* player);

	//���͂ɂ���ď�ԕω�����
	virtual void HandleInput(Player* player);

	//��ԕω������Ƃ���񂾂��Ă΂��֐�
	virtual void Enter(Player* player);

};



