//=========================================================================================================================
// 勇者が動く（とりあえず）シーンクラス
// YashiroScene.cpp
// 製作者 八代恵輔
//=========================================================================================================================
#include "YashiroScene.h"
//#include "TitleScene.h"
using namespace cocos2d;

DataManager* YashiroScene::datamanager;

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

	BraveAni = 0;//勇者のアニメーションを切り替えるための変数

	//主人公(勇者は英語でBraveという)
	BraveSp = Sprite::create("Brave0.png");
	BraveSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BraveSp);

	//勇者アニメーション実行
	this->BraveAnimation();

	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();
	return true;
}

//=========================================================================================================================
// 毎フレーム呼ばれる処理
//=========================================================================================================================
void YashiroScene::update(float dt) {

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
	//parts->setTag(partsType);//タグを保存　なんのパーツを獲ったか判断するため

	Size partsSize = Enemys->getContentSize();
	//出現位置ランダム
	//int num = (rand() % NUM_MAX) + 1;
	float randparts = _engine() % 7 + 2;
	float partsPosX = randparts / 10;
	//float partsXPos = _engine() % static_cast<int>(visibleSize.width / 2); //X軸のランダム
	float partsYPos = _engine() % static_cast<int>(visibleSize.height / 2);//Y軸のランダム
	Enemys->setPosition(Vec2(visibleSize.width * partsPosX, partsYPos));//パーツの配置
	this->addChild(Enemys);
	//_parts.pushBack(parts);//ベクターに追加
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