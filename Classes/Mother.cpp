#include "Mother.h"
#include "HitCheck.h"
using namespace cocos2d;

DataManager* Mother::dataManager;
//=========================================================================================================================
// �����������F�V�[���i��ʁj�̎��O����
//=========================================================================================================================
bool Mother::init(DataManager* data) {

	dataManager = data;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// �L�[�z�񏉊���
	pressKeys.clear();
	// �L�[���̓C�x���g���X�i�[���쐬
	auto keyListener = cocos2d::EventListenerKeyboard::create();
	// �L�[�������ꂽ�Ƃ�
	keyListener->onKeyPressed =
		[this](EventKeyboard::KeyCode keyCode, Event* keyEvent)
	{
		pressKeys.push_back(keyCode);
	};

	// �L�[�������ꂽ�Ƃ�
	keyListener->onKeyReleased =
		[this](EventKeyboard::KeyCode keyCode, Event* keyEvent)
	{
		pressKeys.erase(remove(pressKeys.begin(), pressKeys.end(), keyCode), pressKeys.end());
	};
	// �L�[���̓C�x���g���X�i�[��o�^
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	// �v���C���[��\��
	auto sprite = Sprite::create("chara.png");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
	player = sprite;

	this->scheduleUpdate();

	return true;
}
//=========================================================================================================================
// ���t���[���Ă΂�鏈��
//=========================================================================================================================
void Mother::update(float dt) {
	//-------------------------------------------------------------------
	// �J�[�\���L�[����
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
	// �L�����N�^�[���m�̓����蔻��
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
// �C���X�^���X�𐶐�
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
// �L�[�{�[�h�������Ă��邩�ǂ����̔���
//=========================================================================================================================
bool Mother::IsInputKey(EventKeyboard::KeyCode keyCode) {
	for (auto key : pressKeys)
	{
		if (key == keyCode) return true;
	}
	return false;
}