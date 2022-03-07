#include "Scene.h"
#include "Lib.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "EnemyDerived.h"

#include "EffectManager.h"
#include "EffectDerived.h"
#include "ObjectManager.h"
#include "ObjectDerived.h"
#include "ObjectFunctionManager.h"
#include "UIManager.h"
#include "EXPManager.h"
#include "EXP.h"

#include "UIDerived.h"
//モデルの読み込み
void SceneGame::LoadModel()
{

	//FontTexture = TK_Lib::Load::LoadTexture("./Data/Sprite/fonts/font0.png");

	//プレイヤー
	Model[PlayerModel] = TK_Lib::Load::LoadModel("./Data/Model/Player/Player.mdl", "Player");
	TK_Lib::Model::SetModelTexture("Player", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//ミニオン
	Model[MinionPlayerModel] = TK_Lib::Load::LoadModel("./Data/Model/MinionPlayer/MinionPlayer.mdl", "MinionPlayer");
	TK_Lib::Model::SetModelTexture("MinionPlayer", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//敵スライム
	Model[EnemySlimeModel] = TK_Lib::Load::LoadModel("./Data/Model/Slime/Slime.mdl", "Slime");
	TK_Lib::Model::SetModelTexture("Slime", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//敵爆発
	Model[EnemyBoomModel] = TK_Lib::Load::LoadModel("./Data/Model/Boom/Boom.mdl", "Boom");
	TK_Lib::Model::SetModelTexture("Boom", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//敵浮遊
	Model[EnemyBeholderModel] = TK_Lib::Load::LoadModel("./Data/Model/Beholder/Beholder.mdl", "Beholder");
	TK_Lib::Model::SetModelTexture("Beholder", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//敵宝箱
	Model[EnemyChestModel] = TK_Lib::Load::LoadModel("./Data/Model/ChestEnemy/ChestEnemy.mdl", "ChestEnemy");
	TK_Lib::Model::SetModelTexture("ChestEnemy", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//敵亀
	Model[EnemyTurtleShellModel] = TK_Lib::Load::LoadModel("./Data/Model/TurtleShell/TurtleShell.mdl", "TurtleShell");
	TK_Lib::Model::SetModelTexture("TurtleShell", "./Data/Model/TurtleShell/Textures/PBRTurtleShellNormal.png", 4);
	//敵ボス
	TK_Lib::Load::LoadModel("./Data/Model/Boss/Boss.mdl", "Boss");
	TK_Lib::Model::SetModelTexture("Boss", "./Data/Model/Boss/Texture/NormalMap .png", 4);
	//敵ダミー
	Model[Traning_Dummy] = TK_Lib::Load::LoadModel("./Data/Model/Training_Dummy/Training_dummy.mdl", "Dummy");
	TK_Lib::Model::SetModelTexture("Dummy", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);


	//Model[StageCollisionModel] = TK_Lib::Load::LoadModel("./Data/Model/Stage/Panel01/CollisionStagePanel1.mdl", "Collision");
	//Model[StageNav] = TK_Lib::Load::LoadModel("./Data/Model/Stage/Panel01/NavStagepanel1.mdl", "Nav");
	//Model[StageModel] = TK_Lib::Load::LoadModel("./Data/Model/Stage/Panel01/StagePanel1.mdl", "Stage");
	
	//1ステージ
	Model[StageCollisionModel1] = TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel01/CollisionStage01.mdl", "Collision1");
	Model[StageNav1] =            TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel01/NavStage01.mdl", "Nav1");
	Model[StageModel2] =          TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel01/StageWall.mdl", "Stage1");
	                              TK_Lib::Model::SetModelTexture("Stage1", "./Data/Model/Stage/NormalMap.png", 4);

	                              TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel01/StageGround.mdl", "Stage1NoMakeShadow");
								  TK_Lib::Model::SetModelTexture("Stage1NoMakeShadow", "./Data/Model/Stage/NormalMap.png", 4);

	//2ステージ
	Model[StageCollisionModel2] = TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel02/CollisionStage02.mdl", "Collision2");
	Model[StageNav2] =            TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel02/NavStage02.mdl", "Nav2");
	Model[StageModel2] =          TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel02/StageWall.mdl", "Stage2");
	                              TK_Lib::Model::SetModelTexture("Stage2", "./Data/Model/Stage/NormalMap.png", 4);
	                              TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel02/StageGround.mdl", "Stage2NoMakeShadow");
								  TK_Lib::Model::SetModelTexture("Stage2NoMakeShadow", "./Data/Model/Stage/NormalMap.png", 4);

	//3ステージ
	TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel03/NavStage03.mdl", "Nav3");
	TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel03/CollisionStage03.mdl", "Collision3");
	TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel03/StageWall.mdl", "Stage3");
	TK_Lib::Model::SetModelTexture("Stage3", "./Data/Model/Stage/NormalMap.png", 4);
	TK_Lib::Load::LoadModel("./Data/Model/Stage/NewPanel03/StageGround.mdl", "Stage3NoMakeShadow");
	TK_Lib::Model::SetModelTexture("Stage3NoMakeShadow", "./Data/Model/Stage/NormalMap.png", 4);

	//ポット
	Model[Pat] = TK_Lib::Load::LoadModel("./Data/Model/Pat/Pat.mdl", "Pat");
	TK_Lib::Model::SetModelTexture("Pat", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//タワー
	TK_Lib::Load::LoadModel("./Data/Model/Tower/Tower.mdl", "Tower");
	TK_Lib::Model::SetModelTexture("Tower", "./Data/Model/Tower/Textures/NormalMap .png", 4);
	//壁
	Model[Wall] = TK_Lib::Load::LoadModel("./Data/Model/Wall/Wall.mdl", "Wall");
	TK_Lib::Model::SetModelTexture("Wall", "./Data/Model/Player/Textures/PBRTurtleShellNormal.png", 4);
	//壁
	TK_Lib::Load::LoadModel("./Data/Model/Wall/CollisionWall.mdl", "CollisionWall");
	//空
	TK_Lib::Load::LoadModel("./Data/Model/Sky/Sky.mdl","Sky");


	//Model[StageModel] = TK_Lib::Load::LoadModel("./Data/Model/Stage/Stage2.mdl", "Stage");

	//Model[StageModel] = TK_Lib::Load::CopyModel(Model[StageCollisionModel]);
	// 
	//Model[StageModel]            = TK_Lib::Load::LoadModel("./Data/Model/Stage/SmartStage2.mdl"         , "Stage");
	//Model[StageModel] = TK_Lib::Load::LoadModel("./Data/Model/Stage/Onemesh.mdl", "Stage");
	//Model[StageModel] = TK_Lib::Load::CopyModel(Model[StageCollisionModel]);


    //debugType[DebugParameter] = true;
 
	////Collision
	//TK_Lib::Model::Tranceform(Model[StageCollisionModel], Pos, Angle, Scale);
	//TK_Lib::Model::PlayAnimation(Model[StageCollisionModel], 0, false);
	//TK_Lib::Model::AnimetionUpdate(Model[StageCollisionModel]);
	//Collision::Instance().RegisterModel(Model[StageCollisionModel], ModelCollisionType::CollisionModel);
	//
	////Navメッシュ
	//TK_Lib::Model::Tranceform(Model[StageNav], Pos, Angle, Scale);
	//TK_Lib::Model::PlayAnimation(Model[StageNav], 0, false);
	//TK_Lib::Model::AnimetionUpdate(Model[StageNav]);
	//Collision::Instance().RegisterModel(Model[StageNav], ModelCollisionType::NavModel);
	//Collision::Instance().NacStageBuild();
	//
	////ステージ
	//TK_Lib::Model::Tranceform(Model[StageModel], Pos, Angle, Scale);
	//TK_Lib::Model::PlayAnimation(Model[StageModel], 0, false);
	//TK_Lib::Model::AnimetionUpdate(Model[StageModel]);
}

//サウンドの読み込み
void SceneGame::LoadSound()
{
	const float SoundVolume = 0.5f;
	const float BGMVolume = 0.3f;
	//const float SoundVolume = 0.0f;
	//BGM
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Title/BGM/TitleBGM.wav", "Title");
	TK_Lib::Lib_Sound::SoundSetVolume("Title", BGMVolume);

	//BGM
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/BGM/BossBGM.wav", "BossBGM");
	TK_Lib::Lib_Sound::SoundSetVolume("BossBGM", BGMVolume);

	//SE Coin
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/GetCoin.wav", "GetCoin");
	TK_Lib::Lib_Sound::SoundSetVolume("GetCoin", 0.3f);
	//TK_Lib::Lib_Sound::SoundSetVolume("GetCoin", 0.0f);
	//SE SummonEXP
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/SummonEXP.wav", "SummonEXP");
	TK_Lib::Lib_Sound::SoundSetVolume("SummonEXP", SoundVolume);

	//SE PlayerDamage
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/PlayerDamage.wav", "PlayerDamage");
	TK_Lib::Lib_Sound::SoundSetVolume("PlayerDamage", SoundVolume);

	//SE TutoButton
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/TutoButton.wav", "TutoButton");
	TK_Lib::Lib_Sound::SoundSetVolume("TutoButton", SoundVolume);

	//SE 
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/TutoMisstionClear.wav", "TutoMisstionClear");
	TK_Lib::Lib_Sound::SoundSetVolume("TutoMisstionClear", SoundVolume);

	//SE 
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/AllTowerBreak.wav", "AllTowerBreak");
	TK_Lib::Lib_Sound::SoundSetVolume("AllTowerBreak", SoundVolume);

	//SE 
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/MinionAttack.wav", "MinionAttack");
	TK_Lib::Lib_Sound::SoundSetVolume("MinionAttack", SoundVolume);

	//SE 
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/MinionDown.wav", "MinionDown");
	TK_Lib::Lib_Sound::SoundSetVolume("MinionDown", SoundVolume);


	//SE タワーの破壊
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/TowerBreak.wav", "TowerBreak");
	TK_Lib::Lib_Sound::SoundSetVolume("TowerBreak", SoundVolume);


	//SE タワーの破壊２
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/TowerBreak2.wav", "TowerBreak2");
	TK_Lib::Lib_Sound::SoundSetVolume("TowerBreak2", SoundVolume);

	//SE ボスの回転（ゴロゴロ）
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/BossRoll.wav", "BossRoll");
	TK_Lib::Lib_Sound::SoundSetVolume("BossRoll", 0.7f);

	//SE ボスの走る
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/BossRun.wav", "BossRun");
	TK_Lib::Lib_Sound::SoundSetVolume("BossRun", 0.7f);

	//SE ボス変身
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/BossTranceform.wav", "BossTranceform");
	TK_Lib::Lib_Sound::SoundSetVolume("BossTranceform", 0.7f);

	//SE ボス着地
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/BossJumpDown.wav", "BossJumpDown");
	TK_Lib::Lib_Sound::SoundSetVolume("BossJumpDown", 0.7f);

	//SE ボス着地
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/BGM/BossWind.wav", "BossWind");
	TK_Lib::Lib_Sound::SoundSetVolume("BossWind", 0.7f);

	//SE ボス攻撃始まり
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/BossAttackStart.wav", "BossAttackStart");
	TK_Lib::Lib_Sound::SoundSetVolume("BossAttackStart", 0.7f);

	//SE ボス行動始まり
	TK_Lib::Lib_Sound::RegisterSound("./Data/Sound/Game/SE/BossEntry.wav", "BossEntry");
	TK_Lib::Lib_Sound::SoundSetVolume("BossEntry", 0.7f);


	
}

//エフェクトの読み込み
void SceneGame::LoadEffect()
{

	{
		shared_ptr<EffectFire> efc;
		efc = make_shared<EffectFire>();
		efc->Create("./Data/Efc/particle256x256.png", 3000, VECTOR2{ 64,64 }, VECTOR2{ 4,4 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "Fire");
	}


	{
		shared_ptr<EffectBossFire> efc;
		efc = make_shared<EffectBossFire>();
		efc->Create("./Data/Efc/particle256x256.png", 1000, VECTOR2{ 64,64 }, VECTOR2{ 4,4 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "BossFire");
	}

	{
		shared_ptr<EffectBossExplosion> efc;
		efc = make_shared<EffectBossExplosion>();
		efc->Create("./Data/Efc/particle256x256.png", 1000, VECTOR2{ 64,64 }, VECTOR2{ 4,4 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "BossExplosion");
	}

	{
		shared_ptr<EffectBossSiteBreak> efc;
		efc = make_shared<EffectBossSiteBreak>();
		efc->Create("./Data/Efc/particle256x256.png", 1000, VECTOR2{ 64,64 }, VECTOR2{ 4,4 }, Bland_state::BS_ALPHA);
		effectManager->Register(efc, "BossSiteBreak");
	}

	{
		shared_ptr<EffectAttack> efc;
		efc = make_shared<EffectAttack>();
		efc->Create("./Data/Efc/bomb256x256.png", 100, VECTOR2{ 64,64 }, VECTOR2{ 4,4 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "Attack");
	}

	{
		shared_ptr<EffectTowerBreak> efc;
		efc = make_shared<EffectTowerBreak>();
		efc->Create("./Data/Efc/TowerBreak.png", 50, VECTOR2{ 800,800 }, VECTOR2{ 1,1 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "TowerBreak");
	}

	{
		shared_ptr<EffectStageClear> efc;
		efc = make_shared<EffectStageClear>();
		efc->Create("./Data/Efc/StageClearEfc.png", 600, VECTOR2{ 1024,1024 }, VECTOR2{ 1,1 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "StageClear");
	}


	{
		shared_ptr<EffectThrow> efc;
		efc = make_shared<EffectThrow>();
		efc->Create("./Data/Efc/particle_boss.png", 1000, VECTOR2{ 64,64 }, VECTOR2{ 1,1 }, Bland_state::BS_ADD);
		effectManager->Register(efc, "Destroy");
	}





}
//初期化処理
void SceneGame::Initialize()
{
	//モデルの読み込み
	LoadModel();
	//サウンドの読み込み
	LoadSound();

	
	//UI管理クラスの生成
	//uiManager = make_shared<UIManager>(this);
	//uiManager->Init();

	//オブジェクト関数の設定
	objectFunctionManager = make_shared<ObjectFunctionManager>(this);
	objectFunctionManager->Init();

	//プレイヤーは初期化処理
	mPlayer = std::make_unique<Player>();


	//敵の初期化処理
	enemyManager = std::make_shared<EnemyManager>(this);
	enemyManager->Init();

	//エフェクト
	effectManager = std::make_unique<EffectManager>();
	effectManager->Init();
	//エフェクトの読み込み
	LoadEffect();

	//カメラマネージャー
	cameraManager = std::make_unique<CameraManager>();
	cameraManager->Init(mPlayer.get());
	cameraManager->SetEnemyManager(enemyManager.get());


	//ステージ
	stageManager = make_unique<StageManager>(this);
	stageManager->Init();

	//オブジェクトの初期化処理
	objectManager = make_unique<ObjectManager>(this);
	//objectManager->Init();
	//{
	//		shared_ptr<ObjectWall> obj;
	//		obj = make_shared<ObjectWall>(objectManager.get());
	//		objectManager->Register(obj);
	//}

	//EXPManager
	expManager = make_shared<EXPManager>(this);
	expManager->Init();





	VECTOR3 Pos, Angle, Scale;
	Pos = { 0,0,0 };
	Angle = { 0,0,0 };
	Scale = { 0.06f,0.06f,0.06f };



	//ステージの登録
	//1
	{
		shared_ptr<TutoStage> stage;
		stage = make_shared<TutoStage>("Stage1","Stage1NoMakeShadow", "Collision1", "Nav1", Pos, Angle, Scale, "./Data/Stage/NewStage01.Data", this);
		stageIndex1 = stageManager->Register(stage);
	}
	
	//2
	{
		shared_ptr<Stage> stage;
		stage = make_shared<Stage>("Stage2","Stage2NoMakeShadow", "Collision2", "Nav2", Pos, Angle, Scale, "./Data/Stage/NewStage03.Data", this);
	
		stageIndex2 = stageManager->Register(stage);
	
	}
	
	//3
	{
		shared_ptr<BossStage> stage;
		//	stage = make_shared<Stage>("Stage2", "Collision2", "Nav2", Pos, Angle, Scale, "./Data/Stage/Stage6.Data", this);
 		stage = make_shared<BossStage>("Stage3", "Stage3NoMakeShadow", "Collision3", "Nav3", Pos, Angle, Scale, "./Data/Stage/Stage7.Data", this);
	
		stageIndex3 = stageManager->Register(stage);
	
	}
	

	//
	//{
	//	shared_ptr<EnemyBase> enm;
	//	enm = make_shared<EnemyDummy>(enemyManager.get());
	//	enm->SetPos({ -30, 0,0 });
	//	//enm->pos = ;
	//	//enm->Create("./Data/particle256x256.png", 10000, VECTOR2{ 64,64 }, VECTOR2{ 4,4 }, Bland_state::BS_ADD);
	//	enemyManager->Register(enm);
	//}

	////ポット
	//{
	//	TK_Lib::Model::Tranceform(Model[Pat], Pos, Angle, Scale);
	//	TK_Lib::Model::PlayAnimation(Model[Pat], 0, false);
	//	TK_Lib::Model::AnimetionUpdate(Model[Pat]);
	//}
	//Pos = { 20,0,0 };
	////トレーニング用
	//{
	//	TK_Lib::Model::Tranceform(Model[Traning_Dummy], Pos, Angle, Scale);
	//	TK_Lib::Model::PlayAnimation(Model[Traning_Dummy], 0, false);
	//	TK_Lib::Model::AnimetionUpdate(Model[Traning_Dummy]);
	//}
	//Pos = { 40,0,0 };
	//壁
	{
		TK_Lib::Model::Tranceform(Model[Wall], Pos, Angle, Scale);
		TK_Lib::Model::PlayAnimation(Model[Wall], 0, false);
		TK_Lib::Model::AnimetionUpdate(Model[Wall]);
	}

	
	TK_Lib::Light::SetLookAt({ 500, 800,500 }, { 0,0,100 }, { 0,1,0 });
	TK_Lib::Camera::SetLookAt({ 0,5,-10 }, { 0,0,0 }, { 0,1,0 });
	//プレイヤーにSceneGameを持たせる
	mPlayer->SetSceneGame(this);
	mPlayer->Init();

	stageManager->ChangeStage(stageIndex1);

	////敵ダミーの生成
	//{
	//	shared_ptr<EnemyBase> enm;
	//	enm = make_shared<EnemyDummy>(enemyManager.get());
	//	enm->SetPos({ -20, 0,0 });
	//	enemyManager->Register(enm);
	//}

	//



	//{
	//	shared_ptr<ObjectPot> obj;
	//	obj = make_shared<ObjectPot>(objectManager.get(),this);
	//	obj->SetPos({ 0,0,0 });
	//	objectManager->Register(obj);
	//}
	//
	//{
	//	shared_ptr<ObjectTower> obj;
	//	obj = make_shared<ObjectTower>(objectManager.get(), this);
	//	obj->SetPos({ 40,0,0 });
	//	objectManager->Register(obj);
	//}
	//
	{
		shared_ptr<ObjectWall> obj;
		obj = make_shared<ObjectWall>(objectManager.get(), this);
		obj->SetPos({ 80,0,0 });
		objectManager->Register(obj);
	}
	//
	//
	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
	
	ClearFlg = false;
}
//更新処理
void SceneGame::Update()
{
	//ゲームオーバー処理
	GameOver();

	//if (TK_Lib::Gamepad::GetButtonDown(BTN::X) >= 1)
	//{
	//	effectManager->GetEffectFromSerchKey("BossFire")->Play({ 3,0,0 }, 10);
	//}
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::X) >= 1)
	//{
	//	effectManager->GetEffectFromSerchKey("BossSiteBreak")->Play({ 3,0,0 }, 2);
	//}

	//if (TK_Lib::Gamepad::GetButtonDown(BTN::Y) == 1)
	//{
	//	effectManager->GetEffectFromSerchKey("BossExplosion")->Play({ 3,0,0 }, 10);
	//}

	//
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::B) == 1)
	//{
	//	shared_ptr<EnemySlime> enm;
	//	enm = make_shared<EnemySlime>(enemyManager.get());
	//	enm->SetPos({ 7,0,00 });
	//	enemyManager->Register(enm);
	//}
	//
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::X) == 1)
	//{
	//	shared_ptr<EnemyTurtleShell> enm;
	//	enm = make_shared<EnemyTurtleShell>(enemyManager.get());
	//	enm->SetPos({ 7,0,00 });
	//	enemyManager->Register(enm);
	//}
	//
	//
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::LB) == 1)
	//{
	//	shared_ptr<EnemyChest> enm;
	//	enm = make_shared<EnemyChest>(enemyManager.get());
	//	enm->SetPos({ 7,0,00 });
	//	enemyManager->Register(enm);
	//}
	cameraManager->Update();
	
	mPlayer->Update();
	//TK_Lib::Light::SetLookAt({ mPlayer->GetPos().x + 100, mPlayer->GetPos().y + 120,mPlayer->GetPos().z + 100}, mPlayer->GetPos(), { 0,1,0 });
	//TK_Lib::Light::SetLookAt({ mPlayer->GetPos().x + 100, mPlayer->GetPos().y + 100,mPlayer->GetPos().z + 100 }, mPlayer->GetPos(), { 0,1,0 });
	//	if (TK_Lib::Gamepad::GetButtonDown(BTN::Y) == 1)
    //	{
    //		effectManager->GetEffectFromSerchKey("test")->Play({ 3,0,0 }, 30);
    //	}
	//エフェクトの更新
	effectManager->Update();
	//敵の更新処理
	enemyManager->Update();
	//オブジェクトの更新処理
	objectManager->Update();

	expManager->Update();

	//ステージの更新処理
	stageManager->Update();

	objectFunctionManager->Update();



//	if (TK_Lib::Gamepad::GetButtonDown(BTN::X) == 1)
//	{
//		stageManager->ChangeStage(stageIndex2);
//	}
//
//
	
	//uiManager->Update();





	//if (TK_Lib::Gamepad::GetButtonDown(BTN::A) == 1)
	//{
	//	SceneManager::Instance().ChangeScene(new SceneClear);
	//}
	

	if (GameClear())
	{
		SceneManager::Instance().ChangeScene(new SceneClear);
	}


}
//描画処理
void SceneGame::Render()
{

	
	//TK_Lib::Draw::Font("GAME", FontTexture, { 0,0 }, { 32,32 }, { 1,1,1,1 }, 20);

	objectFunctionManager->CollisionDebug();

	//敵の更新処理
	enemyManager->Render();
	mPlayer->Render();




	expManager->Render();
	stageManager->Render();

	//uiManager->Render();
}
//モデル用の処理
void SceneGame::ModelRender()
{

	 mPlayer->ModelRender();
	stageManager->ModelRender();
	
	//オブジェクトの更新処理
	objectManager->ModelRender();

	//敵の更新処理
	enemyManager->ModelRender();

	//mEnemy->ModelRender();
	// 6TK_Lib::Draw::Model(Model[Pat], ShaderType::Shader_Shadow);
	// 6TK_Lib::Draw::Model(Model[Wall], ShaderType::Shader_Shadow);
	// 6TK_Lib::Draw::Model(Model[Traning_Dummy], ShaderType::Shader_Shadow);
	
//	TK_Lib::Draw::Model(Model[StageCollisionModel], ShaderType::Shader_Shadow);

//	TK_Lib::Draw::Model(Model[StageModel], ShaderType::Shader_Shadow);
	//TK_Lib::Draw::Model(Model[MinionPlayerModel], ShaderType::Shader_Shadow);
	

	
	//TK_Lib::Draw::Model(NavModel, ShaderType::ShaderLambert);
}
//ゲームオーバー処理
bool SceneGame::GameOver()
{
	if (GetStageManager()->GetNowStage()->GetUiTimer()->GetGameTimer() <= 0)
	{
		//プレイヤーの死亡
	     GetPlayer()->SetDeadFlg(true);
		 return true;
	}
	return false;
}
//ゲームクリア処理
bool SceneGame::GameClear()
{
	return ClearFlg;
}

//デバック
void SceneGame::DegugImgui()
{
	ImGui::Begin(u8"ゲーム");

	const char* DebugName[DebugEnd] = {
	 "Parameter",
	 "Collision",
	 "Shader",
	 "DebugNav",
	 "DebugCamera",
	};
	for (int i = 0; i < DebugEnd; i++)
	{
		ImGui::Checkbox(DebugName[i], &debugType[i]);
	}

	for (int i = 0; i < DebugEnd; i++)
	{
		if (!debugType[i])continue;
		switch (i)
		{
		case DebugParameter:ImguiParameter();
			break;
		case DebugCollision:ImguiCollision();
			break;
		case DebugShader:ImguiShader();
			break;
		case DebugNav:ImguiNav();
			break;
		case DebugCamera:ImguiCamera();
			break;
		}
	}


	ImGui::Text("ModelNum:%d",TK_Lib::Model::GetModels().size());
	ImGui::End();

}
//デバッグパラメータ
void SceneGame::ImguiParameter()
{
	ImGui::Text("=============Parameter=============");
	//Charactor* SelectChara=nullptr;

	//SelectChara->ParameterDebug();

	//mPlayer->ParameterDebug();
	//mPlayer->ImguiDebug();
	//mEnemy->ParameterDebug();
}
//デバッグ当たり判定
void SceneGame::ImguiCollision()
{
	ImGui::Text("=============Collision=============");
	mPlayer->CollisionDebug();
	enemyManager->CollisionDebug();
	Collision::Instance().CollisionRender();
}
//デバッグシェーダー
void SceneGame::ImguiShader()
{
	ImGui::Text("=============Shader=============");
	ImGui::Text("No Text");
}
//デバッグナビ
void SceneGame::ImguiNav()
{
	ImGui::Text("=============Nav=============");
	Collision::Instance().NavRender();
}
//デバッグカメラImgui
void SceneGame::ImguiCamera()
{
	cameraManager->Imgui();
}
//終了処理
void SceneGame::End()
{
	TK_Lib::Lib_Sound::SoundStop("Title");
	Collision::Instance().Clear();
	mPlayer->DeleteModel();
	enemyManager->Clear();
	effectManager->Clear();
	stageManager->Clear();
	objectManager->Clear();
	objectFunctionManager->Clear();
	expManager->Clear();
	//modelIndexManager->Clear();
	//delete mPlayer;

	TK_Lib::Lib_Sound::SoundClear();
	//TK_Lib::Delete::DeleteTexture(FontTexture);
}