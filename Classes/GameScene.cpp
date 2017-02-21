//=========================================================================================================================
// ゲームシーンクラス
// GameScene.cpp
// 製作者 戸軽隆二
//=========================================================================================================================
#include "GameScene.h"
#include "TitleScene.h"
using namespace cocos2d;

DataManager* GameScene::datamanager;

//=========================================================================================================================
// LayerをSceneに貼り付けて返すメソッド
//=========================================================================================================================
Scene* GameScene::createScene(DataManager* data) {
	datamanager = data;
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
//=========================================================================================================================
// コンストラクタ
//=========================================================================================================================
GameScene::GameScene() {
	// メンバ変数の初期化
}
//=========================================================================================================================
// デストラクタ
//=========================================================================================================================
GameScene::~GameScene() {
	// メンバ変数の解放
}
//=========================================================================================================================
// 初期化処理：シーン（画面）の事前準備
//=========================================================================================================================
bool GameScene::init() {
	if (!Layer::init())	return false;
	//------------------------------------------------------------------------------------------
	// 画面サイズと原点座標を取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//------------------------------------------------------------------------------------------
	// タッチイベントを有効にする
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto label = Label::createWithTTF("Game", "fonts/Marker Felt.ttf", 60);
	label->setPosition(Vec2(visibleSize.width /2, visibleSize.height / 2));
	this->addChild(label);

	auto sp = Sprite::create("slime_1_1.png");
	auto Sp = Sprite::create();
	Sp->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height / 2.0));

	// コマをスプライトフレーム配列(frames)に格納する
	Vector< SpriteFrame * > frames;
	for (int i = 0; i < 4; i++)
	{
		auto rect = Rect(64 * i, 0, 64, 64);
		auto frame = SpriteFrame::create("slime_1_1.png", rect);
		frame = SpriteFrame::create("slime_1_2.png", rect);
		frames.pushBack(frame);
	}

	// スプライトフレームからアニメーションを作成する　１コマ１秒表示
	auto anime = Animation::createWithSpriteFrames(frames, 60.0 / 60.0);

	// ４コマアニメーションを無限に繰り返すアクションを作成
	auto action = RepeatForever::create(Animate::create(anime));

	// アクションをスプライトに実装
	Sp->runAction(action);

	// シーンに追加
	this->addChild(Sp);

	//sp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(sp);

	// updateを毎フレーム実行するように登録する
	this->scheduleUpdate();
	return true;
}

//=========================================================================================================================
// 毎フレーム呼ばれる処理
//=========================================================================================================================
void GameScene::update(float dt) {

}
//=========================================================================================================================
// 画面遷移のトランジションが終了したた時に１度だけ呼ばれるメソッド
//=========================================================================================================================
void GameScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}

//=========================================================================================================================
// タッチした瞬間に呼ばれるメソッド
//=========================================================================================================================
bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	Vec2 touchPos = pTouch->getLocation();

	return true;
}
//=========================================================================================================================
// タッチされている時に呼ばれるメソッド
//=========================================================================================================================
void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
//=========================================================================================================================
// タッチが離された時によばれるメソッド
//=========================================================================================================================
void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {

}