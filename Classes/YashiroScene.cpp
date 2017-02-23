//=========================================================================================================================
// 勇者が動く（とりあえず）シーンクラス
// YashiroScene.cpp
// 製作者 八代恵輔
//=========================================================================================================================
#include "YashiroScene.h"
//#include "TitleScene.h"
using namespace cocos2d;

DataManager* YashiroScene::datamanager;

static int ENEMY_SPAWN_RATE = 50;//敵の出現頻度

//=========================================================================================================================
// LayerをSceneに貼り付けて返すメソッド
//=========================================================================================================================
Scene* YashiroScene::createScene(DataManager* data) {
	datamanager = data;
	Scene* scene = Scene::create();
	YashiroScene* layer = YashiroScene::create();
	scene->addChild(layer);
	return scene;
}
//=========================================================================================================================
// コンストラクタ
//=========================================================================================================================
YashiroScene::YashiroScene() {
	// メンバ変数の初期化
	//乱数の初期化(_engineを使うとランダムになる)
	std::random_device rdev;
	_engine.seed(rdev());
}
//=========================================================================================================================
// デストラクタ
//=========================================================================================================================
YashiroScene::~YashiroScene() {
	// メンバ変数の解放
}
//ランダム変数の初期化
float YashiroScene::generateRandom(float min, float max)
{
	std::uniform_real_distribution<float> dest(min, max);
	return dest(_engine);
}
//=========================================================================================================================
// 初期化処理：シーン（画面）の事前準備
//=========================================================================================================================
bool YashiroScene::init() {
	if (!Layer::init())	return false;
	//------------------------------------------------------------------------------------------
	// 画面サイズと原点座標を取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//------------------------------------------------------------------------------------------
	// タッチイベントを有効にする
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(YashiroScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(YashiroScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(YashiroScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Label* label = Label::createWithTTF("Yashiro", "fonts/Marker Felt.ttf", 60);
	label->setPosition(Vec2(visibleSize.width /2, visibleSize.height / 2));
	this->addChild(label);

	DistanceOnOff = true;//距離を探す時に使う

	BraveAni = 0;//勇者のアニメーションを切り替えるための変数
	EnemysTag = 0;//敵のタグ
	distance2 = 10000000000000000;

	//主人公(勇者は英語でBraveという)
	BraveSp = Sprite::create("Brave0.png");
	BraveSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	BraveSp->setScale(0.5f);
	this->addChild(BraveSp);

	//勇者アニメーション実行
	this->BraveAnimation();

	//this->addEnemys();

	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();
	return true;
}

//=========================================================================================================================
// 毎フレーム呼ばれる処理
//=========================================================================================================================
void YashiroScene::update(float dt) 
{
	//ランダムの数値
	int randam = _engine() % ENEMY_SPAWN_RATE;
	//randamが0になったら敵生成
	if (randam == 0)
	{
		this->addEnemys();
	}

	for (Sprite* Enemys : _enemys)
	{
		//敵の最大値を入れる
		int MaxEnemyTag = EnemysTag;
		for (int count = 0; count < MaxEnemyTag; MaxEnemyTag--)
		{
			log("x座標：%i", MaxEnemyTag);
			//敵ポジション取得
			Sprite* SetEnemy = (Sprite *)this->getChildByTag(MaxEnemyTag);
			Vec2 EnemysPos = SetEnemy->getPosition();
			log("x座標：%f, y座標：%f", EnemysPos.x, EnemysPos.y);

			//勇者の位置
			Vec2 BravePoint2 = BraveSp->getPosition();
			//敵の速度
			float EnemysSpeed = 2;
			//勇者追尾
			float Angle2 = ccpToAngle(ccpSub(BravePoint2, EnemysPos));//角度を求める ※EnemysPos=敵の位置
			Angle2 = CC_RADIANS_TO_DEGREES(Angle2);
			Vec2 dir2 = Vec2(
				cos(CC_DEGREES_TO_RADIANS(-Angle2)),
				sin(CC_DEGREES_TO_RADIANS(Angle2))
				);
			Vec2 EnemysVec2 = SetEnemy->getPosition() + dir2 * EnemysSpeed;
			SetEnemy->setPosition(EnemysVec2);

			log("MaxEnemyTagMax = %d", MaxEnemyTag);
			distance = BraveSp->getPosition().getDistance(EnemysPos);
			if (distance < distance2)
			{
				log("kyori = %f", distance);
				log("kyori2 = %f", distance2);

				distance2 = distance;

				//より近い敵をセット(タグ取得)SetTagはint
				SetTag = Enemys->getTag();

				log("MaxEnemyTagMin = %d", MaxEnemyTag);
				//一番近い敵を仮のスプライトに入れる
				Sprite* SetTagEnemy = (Sprite *)this->getChildByTag(MaxEnemyTag);
				//選ばれた敵のポジション取得
				EnemyPos = SetTagEnemy->getPosition();
			}
		}
		//勇者の速度
		float BraveSpeed = 1;
		//勇者追尾
		Vec2 BravePoint = BraveSp->getPosition();//勇者の位置
		float Angle = ccpToAngle(ccpSub(EnemyPos, BravePoint));//角度を求める ※EnemysPos=敵の位置
		Angle = CC_RADIANS_TO_DEGREES(Angle);
		Vec2 dir = Vec2(
			cos(CC_DEGREES_TO_RADIANS(-Angle)),
			sin(CC_DEGREES_TO_RADIANS(Angle))
			);
		// 現在の位置に移動方向＊移動速度を加算
		Vec2 BraveVec2 = BraveSp->getPosition() + dir * BraveSpeed;
		BraveSp->setPosition(BraveVec2);

		//----------------------
		//ここから当たり判定
		//----------------------
		BraveRect = BraveSp->getBoundingBox();//勇者の短形を取り出す
		//勇者と敵の当たり判定
		if (BraveRect.containsPoint(EnemyPos))
		{
			log("ON");
		}
		break;
	}
}
//=========================================================================================================================
// プレイヤーのアニメーション
//=========================================================================================================================
void YashiroScene::BraveAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::vector<std::string> fileNames[1];

	BraveSp->setTexture("Brave0.png");
	// 泳ぐ
	fileNames[0].push_back("Brave0.png");
	fileNames[0].push_back("Brave1.png");
	fileNames[0].push_back("Brave0.png");
	fileNames[0].push_back("Brave2.png");

	Animation* animation = Animation::create();

	for (std::string fileName : fileNames[BraveAni])
	{
		animation->addSpriteFrameWithFile(fileName);
	}
	animation->setDelayPerUnit(0.3f);			// 画像切り替えのディレイ
	animation->setRestoreOriginalFrame(true);	// アニメーションが終わった際に最初のフレームに戻す
	//スプライトのアクションを全部停止！
	BraveSp->stopAllActions();
	BraveSp->runAction(RepeatForever::create(Animate::create(animation)));
}
//=========================================================================================================================
//敵精製仮
//=========================================================================================================================
Sprite* YashiroScene::addEnemys()
{
	//画面サイズ
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//敵の作成
	Sprite* Enemys = Sprite::create("Enemy.png");
	EnemysTag++;//タグ増やす
	Enemys->setTag(EnemysTag);//タグを保存　なんのパーツを獲ったか判断するため
	Enemys->setScale(0.5f);
	//出現位置ランダム
	//float randparts = _engine() % 7 + 2;
	//float partsPosX = randparts / 10;
	float partsXPos = _engine() % static_cast<int>(visibleSize.width); //X軸のランダム
	float partsYPos = _engine() % static_cast<int>(visibleSize.height);//Y軸のランダム
	Enemys->setPosition(Vec2(partsXPos, partsYPos));//パーツの配置
	this->addChild(Enemys);
	_enemys.pushBack(Enemys);//ベクターに追加
	return Enemys;
}
//=========================================================================================================================
// 画面遷移のトランジションが終了したた時に１度だけ呼ばれるメソッド
//=========================================================================================================================
void YashiroScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}

//=========================================================================================================================
// タッチした瞬間に呼ばれるメソッド
//=========================================================================================================================
bool YashiroScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	Vec2 touchPos = pTouch->getLocation();

	return true;
}
//=========================================================================================================================
// タッチされている時に呼ばれるメソッド
//=========================================================================================================================
void YashiroScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
//=========================================================================================================================
// タッチが離された時によばれるメソッド
//=========================================================================================================================
void YashiroScene::onTouchEnded(Touch* pTouch, Event* pEvent) {

}