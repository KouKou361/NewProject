#pragma once
#include "Player.h"
#include "Lib.h"
#include "Mathf.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "SiroboPlayer.h"
#include "CameraController.h"
#include "Animetion.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "UIDerived.h"

#include "UIManager.h"
#include "ExportScript.h"
void Player::Init()
{
	//�X�e�[�^�X�ݒ�
	SetStatus("Player");

	//���f������
	SetModel(TK_Lib::Load::GetModel("Player"));

	//�A�j���[�V�����̓o�^
	RegisterAnimetion();
	
	//�^�O�Â�
	SetTag(ObjectTag::TAG_PLAYER);

	//�A�j���[�V����
	RegisterAnimetion();

	//�S�Ă̍s����o�^
	RegisterState();
	

	//�~�j�I�������̏���������
	siroboManager = make_unique<SiroboManager>();
	siroboManager->Init();

	//�e�N�X�`���̓ǂݍ��݁A�ݒ�
	int TargetCursurSprite = TK_Lib::Load::LoadTexture("./Data/Sprite/TargetCursor.png");
	int HealthPointSprite = TK_Lib::Load::LoadTexture("./Data/Sprite/Game/HealthPoint.png");

	//�G�}�l�[�W���[�̐ݒ�
	EnemyManager* enemyManager = sceneGame->GetEnemyManager();
	siroboManager->SetEnemyManager(enemyManager);

	//�}�l�[�W���[�̐ݒ�
	ObjectManager* objectManager = sceneGame->GetObjectManager();
	siroboManager->SetObjectManager(objectManager);

	//�U���ڕW�̕\��UI�̐���
	{
		uiTargetCursur = make_shared<UITargetCursur>();
		uiTargetCursur->SetTexture(TargetCursurSprite);
		uiTargetCursur->SetCharactor(this);
		uiTargetCursur->Init();
	}

	//�G��HP�̕\��UI�̐���
	{
		uiTargetHP = make_shared<UITargetHP>();
		uiTargetHP->SetCharactor(this);
		uiTargetHP->Init();
	}

	//�G�ɍU�����Ă���~�j�I���̐�
	{
		uiSiroboAttack = make_shared<UISiroboAttack>();
		uiSiroboAttack->Init();
		uiSiroboAttack->SetCharactor(this);
	}

	//�V���{�B�̍U�����󂯂郊�X�g���N���A�i�O�̂��߁j
	attackSirobo.clear();

	SetOldPos(GetPos());

	//manager->Register(uiPlayerHP);

}
void Player::Update()
{
	
	ImGui::Begin("test");
	ImGui::Text("test=%f", GetMaskVolume());
	if (ImGui::Button("test"))
	{
		MaskStart(0.1f);
	}
	ImGui::End();
	//�_���[�W�m�F
	if (GetDamageFlg() == true)
	{
		ChangeState(stateDamage.get());
	}
	//���S�m�F
	if (GetDeadFlg() == true)
	{
		ChangeState(stateDead.get());
	}


	stateMachine->Run(this);

	//�G�Ƃ̓����蔻��
	VsEnemy();

	//Nav���b�V���Ɍ��ݒn���X�V����
	Collision::Instance().SetTarget(GetPos());

	//�ߋ��̒n�_�̕ۑ�
	SetOldPos(GetPos());

	//�^�[�Q�b�g�̌�����
	ResetFarTarget(LossTargetFar);

	//�~�j�I�������̍X�V����
	siroboManager->Update();

	//���G���Ԃ̍X�V
	InvincibleTimeUpdate();

	//�s��Ȃǂ̍X�V����
	Charactor::Update();

}

//���͏���
void Player::Input()
{
	//�v���C���[�̈ړ����͏���
	InputMove();

	//�G�ڕW�̐ݒ�
	SetTargetActor();

	//�v���C���[�̃J�������͏���
	InputCamera();

	//�U�����͏���
	InputAttack();

	//�~�j�I���̋A�ғ��͏���
	InputSiroboBack();

	//�~�j�I���̑h������
	InputSiroboResuscitation();
	
}
//�V�[���Q�[���̐ݒ�
void Player::SetSceneGame(SceneGame* scene) {
	this->sceneGame = scene;
}

//RB�őS�ẴV���{�̋A��
void Player::InputSiroboBack()
{
	if (TK_Lib::Gamepad::GetButtonDown(BTN::RB) == 1)
	{
		siroboManager->AllBack();
	}
}

//���͍U��
void Player::InputAttack()
{
	CameraManager* cameraManager = sceneGame->GetCameraManager();

	//����Aim�J�������ł͂Ȃ���ԂȂ�return 
	if (cameraManager->GetNowType() != CameraManager::CameraType::TYPE_AIM)return;
	//�����U�����[�h�Ȃ�return;
	if (state == State::ATTACK)return;

	if (GetSiroboManager()->GetTypeSiroboSize(Sirobo::StateType::TYPE_STAND_BY) == 0)return;

	if (TK_Lib::Gamepad::GetButtonDown(BTN::RT) == 1)
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::Y) == 1)
	{
		ChangeState(stateAttack.get());
	}


}

//���͏���(���͂��ꂽ���l��moveVec�ɓ������)
void Player::InputMove()
{
	float ax = TK_Lib::Gamepad::GetAxisLX();
	float az = TK_Lib::Gamepad::GetAxisLY();

	VECTOR3 CameraFront = TK_Lib::Camera::GetFront();
	//XZ���ʂɕϊ�����
	{
		CameraFront.y = 0.0f;
		XMVECTOR Front = DirectX::XMLoadFloat3(&CameraFront);
		Front = XMVector3Normalize(Front);
		DirectX::XMStoreFloat3(&CameraFront, Front);
	}

	VECTOR3 CameraRight = TK_Lib::Camera::GetRight();
	//XZ���ʂɕϊ�����
	{
		CameraRight.y = 0.0f;
		XMVECTOR right = DirectX::XMLoadFloat3(&CameraRight);
		right = XMVector3Normalize(right);
		DirectX::XMStoreFloat3(&CameraRight, right);
	}

	moveVec.x = (CameraFront.x * az + CameraRight.x * ax);
	moveVec.z = (CameraFront.z * az + CameraRight.z * ax);
	moveVec.y = 0.0f;

	//���K��
	moveVec=Mathf::Vec3Normalize(moveVec);
}

//�v���C���[�̃J�������͏���
void Player::InputCamera()
{
	if (GetSiroboManager()->GetTypeSiroboSize(Sirobo::StateType::TYPE_STAND_BY) == 0)return;

	//if (TK_Lib::Gamepad::GetButtonDown(BTN::X) == 1)
	if (TK_Lib::Gamepad::GetButtonDown(BTN::LT) >= 1)
	{
		CameraManager* cameraManager = sceneGame->GetCameraManager();
		//����Aim�J�������ł͂Ȃ���ԂȂ�return 
		if (cameraManager->GetNowType() == CameraManager::CameraType::TYPE_AIM)return;
		//Aim�J�����Ɉڍs
		ChangeCameraAim();
	}
}

//�V���{�̑h�����͏���
void Player::InputSiroboResuscitation()
{
	//�V���{�B�A�h���͈�
	const float ResuscitationLength = 10.0f;
	//TK_Lib::Debug3D::Circle(GetPos(), ResuscitationLength, {0,1,0,1});
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::Y) <= 0)return;
	float NearPos = FLT_MAX;
	Sirobo* ResuscitationTarget = nullptr;

	for (int i = 0;i < siroboManager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo=siroboManager->GetSiroboIndex(i);

		//���S�̃~�j�I���̂�
		if (sirobo->GetState() == Sirobo::StateType::TYPE_DEAD ||
			sirobo->GetState() == Sirobo::StateType::TYPE_RESUSCITATION
			)
		{
			const float L = Length(sirobo->GetPos());
			//�h���͈͂ɓ����Ă����Ȃ�
			if (ResuscitationLength <= L)continue;
			//�ŒZ�����̃~�j�I����h���^�[�Q�b�g�ɂ���
			if (NearPos >= L)
			{
				NearPos = L;
				ResuscitationTarget = sirobo;
			}

		}

	}

	//�h����ԂɈڍs�I
	if (ResuscitationTarget != nullptr)
	{
		ResuscitationTarget->SetResuscitation();
	}
}

//�f�o�b�O
void Player::CollisionDebug()
{
	//�����蔻��
	TK_Lib::Debug3D::Circle(GetPos(), collisionRadius);
	//���C�s�b�N�̕␳

	//���C�s�b�N�p�̓����蔻��
	VECTOR3 Start = { GetPos().x,GetPos().y + BesideRayPickUP,     GetPos().z };
	VECTOR3 End = { GetPos().x,GetPos().y - VerticalRayPickUnder, GetPos().z };
	TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });

	//���C�s�b�N�p�̓����蔻��
	Start = { GetPos().x - moveVec.x, GetPos().y - moveVec.y + BesideRayPickUP,     GetPos().z - moveVec.z };
	End = { GetPos().x + moveVec.x ,GetPos().y + moveVec.y + BesideRayPickUP, GetPos().z + moveVec.z };

	TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });

	for (int i = 0; i < siroboManager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = siroboManager->GetSiroboIndex(i);
		sirobo->CollisionDebug();

		//�����蔻��
		//TK_Lib::Debug3D::Circle(GetPos(), sirobo->StandBySerchL);
	}
}
//�ڕW�̓G�̐ݒ�
bool Player::SetTargetActor()
{
	float nearDot = FLT_MAX;

	VECTOR3  vec1 = TK_Lib::Camera::GetFront();
	vec1.y = 0;
	XMVECTOR Vec1 = XMLoadFloat3(&vec1);
	XMVECTOR NVec1 = XMVector3Normalize(Vec1);

	SetTarget(nullptr);


	//�G�̃^�[�Q�b�g�ݒ�

	{
		EnemyManager* enemyManager = sceneGame->GetEnemyManager();
		constexpr float ViewAngle = 10;
		for (int i = 0; i < enemyManager->GetEnemiesSize(); i++)
		{
			EnemyBase* enm = enemyManager->GetEnemiesIndex(i);

			if (enm->GetTargetFlg() == TargetFlg::FAILED)continue;
			//�ŒZ�����܂ł̒���


			//�����������Ȃ�continue;
			if (Length(enm->GetPos()) >= AttackMaxLength)continue;

			float dot = 0;
			{
				VECTOR3  vec2 = enm->GetPos() - TK_Lib::Camera::GetPos();
				vec2.y = 0;
				XMVECTOR Vec2 = XMLoadFloat3(&vec2);
				XMVECTOR Nvec2 = XMVector3Normalize(Vec2);
				XMVECTOR Dot = XMVector3Dot(NVec1, Nvec2);
				XMStoreFloat(&dot, Dot);
				dot = acosf(dot);
			}
			//�^�[�Q�b�g����p�ɓ����ĂȂ��Ȃ�continue
			if (XMConvertToDegrees(dot) >= ViewAngle)
			{
				continue;
			}
			if (dot >= nearDot)
			{
				continue;
			}

			////�����v���C���[����݂ēG����둤�Ȃ�continue;
			//if(sceneGame->GetCameraManager()->GetNowType()!=CameraManager::CameraType::TypeAim)
			//{
			//	float Dot=0;

			//	//�v���C���[�ƓG�̃x�N�g��
			//	XMVECTOR Nvec2;
			//	{
			//		VECTOR3  vec2 = enm->GetPos() - GetPos();
			//		vec2.y = 0;
			//		XMVECTOR Vec2 = XMLoadFloat3(&vec2);
			//		Nvec2 = XMVector3Normalize(Vec2);
			//	}
			//	//�J�����ƓG�̃x�N�g��
			//	XMVECTOR Nvec3;
			//	{
			//		VECTOR3 PlayerFront = enm->GetPos() - TK_Lib::Camera::GetPos();
			//		PlayerFront.y = 0;
			//		XMVECTOR Vec3 = XMLoadFloat3(&PlayerFront);
			//		Nvec3 = XMVector3Normalize(Vec3);
			//	}

			//
			//	XMVECTOR mDot = XMVector3Dot(Nvec3, Nvec2);
			//	XMStoreFloat(&Dot, mDot);
			//	Dot = acosf(Dot);
			//	if (XMConvertToDegrees(Dot) >=  180 - ViewAngle)continue;
			//}

			SetTargetEnemy(enm);
			nearDot = dot;
		}
	}


	//�I�u�W�F�N�g�̐ݒ�
	{
		ObjectManager* objectManager = sceneGame->GetObjectManager();
		constexpr float ViewAngle = 10;
		for (int i = 0; i < objectManager->GetObjesSize(); i++)
		{
			ObjectBase* obj = objectManager->GetObjesIndex(i);
			//�ŒZ�����܂ł̒���


			//�����������Ȃ�continue;
			if (Length(obj->GetPos()) >= AttackMaxLength)continue;

			float dot = 0;
			{
				VECTOR3  vec2 = obj->GetPos() - TK_Lib::Camera::GetPos();
				vec2.y = 0;
				XMVECTOR Vec2 = XMLoadFloat3(&vec2);
				XMVECTOR Nvec2 = XMVector3Normalize(Vec2);
				XMVECTOR Dot = XMVector3Dot(NVec1, Nvec2);
				XMStoreFloat(&dot, Dot);
				dot = acosf(dot);
			}
			//�^�[�Q�b�g����p�ɓ����ĂȂ��Ȃ�continue
			if (XMConvertToDegrees(dot) >= ViewAngle)
			{
				continue;
			}
			if (dot >= nearDot)
			{
				continue;
			}
			SetTargetEnemy(obj);
			nearDot = dot;
		}
	}



	//�^�[�Q�b�g�ɂƂ炦�邱�Ƃ��o���Ȃ��Ȃ�
	if (GetTarget() == nullptr)
	{
		return false;
	}
	return true;
}
//Aim�J�����̎��_�ύX
bool Player::ChangeCameraAim()
{
	CameraManager* cameraManager = sceneGame->GetCameraManager();
	EnemyManager* enemyManager = sceneGame->GetEnemyManager();

	if (GetTarget() != nullptr)
	{
		cameraManager->ChangeCamera(new CameraAim(this, GetTarget(), enemyManager));
		return true;
	}
	return false;
}

//�ʒu�␳�ƍX�V����
void Player::UpdateCollision()
{
	//�������̓����蔻��iXZ���ʁj
	BesideCollision();
	//�c�����̓����蔻��iY�����j
	VerticalCollision();
	//�X�e�[�W�̓����蔻��@�ŏI
	//StageOverhang();


}
void Player::VsEnemy()
{
	EnemyManager* enemyManager = sceneGame->GetEnemyManager();

	VECTOR3 OutPos;
	EnemyBase* OutEnm;
	if (enemyManager->CollisionEnemy(GetPos(), weight, collisionRadius, OutPos, OutEnm))
	{
		SetPos(OutPos);
	}
}

//��ԃ}�V���̕ϊ�
void Player::ChangeState(PlayerState* state)
{
	//�������̃X�e�[�g�ƌ��݂̃X�e�[�W�������Ȃ�
	if (stateMachine == state)return;
	//���݂̃X�e�[�g�}�V���̏I������
	if(stateMachine)stateMachine->End(this);
	stateMachine = state;
	stateMachine->Start(this);
}

//��ԃ}�V���̕ϊ�
void Player::ChangeState(const State &state,BossStage* stage)
{
	PlayerState* playerstate=nullptr;
	switch (state)
	{
	case State::ATTACK://�U��
		playerstate = stateAttack.get();
			break;
	case State::DAMAGE://�_���[�W
		playerstate = stateDamage.get();
			break;
	case State::DEAD://���S
		playerstate = stateDead.get();
			break;
	case State::WAIT://�ҋ@
		playerstate = stateWait.get();
			break;
	case State::WALK://�ړ�
		playerstate = stateWalk.get();
			break;
	case State::BOSS_ENTRY://�{�X�̓o��
		playerstate = stateBossEntry.get();
		stateBossEntry->SetState(stage);
		break;
	default:
		break;
	}
	if (playerstate == nullptr)return;
	ChangeState(playerstate);
}
//�^�[�Q�b�g��������x���������ꍇ������
void Player::ResetFarTarget(const float &L)
{

	if (GetTarget() == nullptr)
	{
		if (sceneGame->GetCameraManager()->GetNowType() == CameraManager::CameraType::TYPE_AIM)
		{
			sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(this));
		
		}
		return;
	}
	float l=Length(GetTarget()->GetPos());
	if (L <= l)
	{
		SetTarget(nullptr);
		sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(this));
	}
}
//�ڕW�̓G�ݒ�
void Player::SetTargetEnemy(Actor* enm) {

	SetTarget(enm);

	//�~�j�I���ɂ��U���Ώۂ�ς���
	for (int i = 0; i < siroboManager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = siroboManager->GetSiroboIndex(i);
		if (sirobo->GetState() == Sirobo::StateType::TYPE_STAND_BY)
		{
			sirobo->SetTarget(enm);
		}
	}
}

//CameraManager�̐ݒ�
void Player::ModelRender()
{
	TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
	//�~�j�I�������̃��f���`�揈��
	siroboManager->ModelRender();
}
//�J�[�\���̕`��
void Player::RenderCursur()
{
	//if (GetTarget() == nullptr)return;
	
	//XMVECTOR WorldPosition;
	//VECTOR3 targetPos = GetTarget()->GetPos();
	//WorldPosition = XMLoadFloat3(&targetPos);  
	//
	////���W�ϊ�
	//XMMATRIX View = XMLoadFloat4x4(&TK_Lib::Camera::GetView());
	//XMMATRIX Projection = XMLoadFloat4x4(&TK_Lib::Camera::GetProjection());
	//XMMATRIX World = XMMatrixIdentity();
	//
	//VECTOR2 viewport = TK_Lib::Window::GetWindowSize();
	//
	//VECTOR3 screenPos;
	////���[���h���W����X�N���[�����W�ɕϊ�����
	//XMVECTOR ScreenPosition;
	//ScreenPosition = XMVector3Project(WorldPosition, 0, 0, viewport.x, viewport.y, 0.0f, 1.0, Projection, View, World);
	//XMStoreFloat3(&screenPos, ScreenPosition);
	//const float offsetX = -50;
	//const float offsetY = -75;
	//TK_Lib::Draw::Sprite(TargetCursurSprite, VECTOR2{screenPos.x+ offsetX,screenPos.y + offsetY }, { 100,100 }, { 0,0,256,256 });

	//RenderTargetHP({ screenPos.x - 50,screenPos.y - 80 });
}
//�ڕW��HP�̕\��
void Player::RenderTargetHP(const VECTOR2& Pos)
{
	//if (GetTarget()->GetHp() <= 0)return;
	//GetTarget()->HPRender(TargetHPGageSprite, Pos);
}
//2D�Ȃǂ̕`��
void Player::Render()
{
	//�v���C���[��HP
	//uiPlayerHP->Render();
	//�ڕW�̕W��
	uiTargetCursur->Render();
	//�ڕW��HP
	uiTargetHP->Render();

	uiSiroboAttack->Render();
	
	//HPRender(HealthPointSprite, {0,0});
	//�ڕW�̕W��
	//RenderCursur();
	//�~�j�I��������2D�Ȃǂ̕`�揈��
	siroboManager->Render();



}

//�v���C���[�̗͕̑\��
void Player::HPRender(const int &spriteIndex, const VECTOR2& pos)
{
//	VECTOR2 HPPosition= Pos;
//	const VECTOR2 SpriteSize = { 150,150 };
//
//	//�v���C���[�̍ő�HP�̕\��
//	for (int i = 0; i < GetMaxHp(); i++)
//	{
//		HPPosition.x += 50;
//		TK_Lib::Draw::Sprite(SpriteIndex, HPPosition, SpriteSize, VECTOR4{ 0,0,256,256 });
//	}
//	//�v���C���[��HP�̕\��
//	HPPosition = Pos;
//	for (int i = 0; i < GetHp(); i++)
//	{
//		HPPosition.x += 50;
//		TK_Lib::Draw::Sprite(SpriteIndex, HPPosition, SpriteSize, VECTOR4{ 256 * 2,256 * 1,256,256 });
//	}
//
}
//�v���C���[�̃X�e�[�W���Z�b�g����
void Player::ResetPlayer()
{
	siroboManager->Clear();
	sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(this), GetPos());
	
	//for (int i = 0; i < 4; i++)
	//{
	//	shared_ptr<SiroboPlayer> sirobo;
	//	sirobo = make_shared<SiroboPlayer>();
	//	sirobo->Init(this);
	//	sirobo->SetPos({ 5,0,static_cast<float>(i * 8) });
	//	//	sirobo->pos = { 5,0,static_cast<float>(140) };
	//	siroboManager->Register(sirobo);
	//}
}

//�_���[�W�𔻒�
bool Player::AddDamage(const int &damage, const float &setInvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp() <= 0)return false;
	//���G���Ȃ�
	if (invincibleTime > 0)return false;

	invincibleTime = setInvincibleTime;
	const float SubtractTime = -10;
	sceneGame->GetStageManager()->GetNowStage()->GetUiTimer()->AddGameOverTimer(SubtractTime);
	TK_Lib::Lib_Sound::SoundPlay("PlayerDamage", false);
	

	if (sceneGame->GetStageManager()->GetNowStage()->GetUiTimer()->GetGameTimer() <= 0)
	{
		//���S
		SetDeadFlg(true);
	}
	else
	{
		//�_���[�W�t���O�̃I��
		SetDamageFlg(true);
	}
	//hp -= Damage;
	//���������c���Ă����Ȃ�
	//if (hp >= 1)
	//{//�_���[�W�t���O�̃I��
	//	SetDamageFlg(true);
	//}
	//else//���S���Ă���Ȃ�
	//{
	//	//�_���[�W�t���O�̃I��
	//	SetDeadFlg(true);
	//}
	return true;
}

//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
void Player::SetStatus(const string &searchName)
{
	AlliesStatusData* data = sceneGame->GetexportSCV()->GetAlliesStatusDataSearchName(searchName);
	SetQuaternion({ 0,0,0,1 });
	SetMaxHp(data->GetHp());
	SetHp(data->GetHp());
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	speed = data->GetSpeed();
	collisionRadius = data->GetCollisionRadius();
	weight = data->GetWeight();
	SetMaxInvincibleTime(data->GetMaxInvincibleTime());
}
//�A�j���[�V�����̐ݒ�
void Player::RegisterAnimetion()
{
	anime = make_shared<Animetion>();

	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		anime->Attack1,//"Attack",
		anime->Damage,//"Damage",
		anime->Die,//Dead
		anime->Idle,//"Wait",
		anime->Run,//"Walk",
		anime->End,//"End",
	};
	//�A�j���[�V�����̓o�^
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//�S�Ẵ��[�V������o�^
void Player::RegisterState()
{
	//�S�Ă̏�Ԃ��ɓo�^���Ă���
	stateAttack = make_unique<AttackState>();
	stateDamage = make_unique<DamageState>();
	stateDead = make_unique<DeadState>();
	stateWait = make_unique<WaitState>();
	stateWalk = make_unique<WalkState>();
	stateBossEntry = make_unique<BossEntryPlayerState>();

	stateMachine = nullptr;
	ChangeState(stateWalk.get());
}




