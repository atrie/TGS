#include "Mother.h"
#include "HitCheck.h"
using namespace cocos2d;

DataManager* Mother::dataManager;
//=========================================================================================================================
// 初期化処理：シーン（画面）の事前準備
//=========================================================================================================================
bool Mother::init(DataManager* data) {

	dataManager = data;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// キー配列初期化
	pressKeys.clear();
	// キー入力イベントリスナーを作成
	auto keyListener = cocos2d::EventListenerKeyboard::create();
	// キーが押されたとき
	keyListener->onKeyPressed =
		[this](EventKeyboard::KeyCode keyCode, Event* keyEvent)
	{
		pressKeys.push_back(keyCode);
	};

	// キーが離されたとき
	keyListener->onKeyReleased =
		[this](EventKeyboard::KeyCode keyCode, Event* keyEvent)
	{
		pressKeys.erase(remove(pressKeys.begin(), pressKeys.end(), keyCode), pressKeys.end());
	};
	// キー入力イベントリスナーを登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	// プレイヤーを表示
	auto sprite = Sprite::create("chara.png");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
	player = sprite;

	this->scheduleUpdate();

	return true;
}
//=========================================================================================================================
// 毎フレーム呼ばれる処理
//=========================================================================================================================
void Mother::update(float dt) {
	//-------------------------------------------------------------------
	// カーソルキー判定
	if (IsInputKey(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		Vec2 pos = player->getPosition();
		pos.x -= 1;
		player->setPosition(pos);
	}
	else if (IsInputKey(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		Vec2 pos = player->getPosition();
		pos.x += 1;
		player->setPosition(pos);
	}
	else if (IsInputKey(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		Vec2 pos = player->getPosition();
		pos.y -= 1;
		player->setPosition(pos);
	}
	else if (IsInputKey(EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		Vec2 pos = player->getPosition();
		pos.y += 1;
		player->setPosition(pos);
	}
	//-----------------------------------------------------------------------
	// キャラクター同士の当たり判定
	HitCheck check;
	if (check.EnemyAndChara(dataManager->GetEnemyCon(), player) == true) {
		CCLOG("Enemy Hit !!!!");
	}
	else if (check.EnemyAndEnemy(dataManager->GetEnemyCon()) == true)
		CCLOG("Enemy OverLap !!!!");
	else
		CCLOG("No Hit...");
}
//=========================================================================================================================
// インスタンスを生成
//=========================================================================================================================
Mother* Mother::create(DataManager* data) {
	Mother* pRet = new Mother();
	if (pRet && pRet->init(data))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
//=========================================================================================================================
// キーボードを押しているかどうかの判定
//=========================================================================================================================
bool Mother::IsInputKey(EventKeyboard::KeyCode keyCode) {
	for (auto key : pressKeys)
	{
		if (key == keyCode) return true;
	}
	return false;
}