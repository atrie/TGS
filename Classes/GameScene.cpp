//=========================================================================================================================
// �Q�[���V�[���N���X
// GameScene.cpp
// ����� �ˌy����
//=========================================================================================================================
#include "GameScene.h"
#include "TitleScene.h"
using namespace cocos2d;

DataManager* GameScene::datamanager;

//=========================================================================================================================
// Layer��Scene�ɓ\��t���ĕԂ����\�b�h
//=========================================================================================================================
Scene* GameScene::createScene(DataManager* data) {
	datamanager = data;
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
//=========================================================================================================================
// �R���X�g���N�^
//=========================================================================================================================
GameScene::GameScene() {
	// �����o�ϐ��̏�����
}
//=========================================================================================================================
// �f�X�g���N�^
//=========================================================================================================================
GameScene::~GameScene() {
	// �����o�ϐ��̉��
}
//=========================================================================================================================
// �����������F�V�[���i��ʁj�̎��O����
//=========================================================================================================================
bool GameScene::init() {
	if (!Layer::init())	return false;
	//------------------------------------------------------------------------------------------
	// ��ʃT�C�Y�ƌ��_���W���擾
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//------------------------------------------------------------------------------------------
	// �^�b�`�C�x���g��L���ɂ���
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

	// �R�}���X�v���C�g�t���[���z��(frames)�Ɋi�[����
	Vector< SpriteFrame * > frames;
	for (int i = 0; i < 4; i++)
	{
		auto rect = Rect(64 * i, 0, 64, 64);
		auto frame = SpriteFrame::create("slime_1_1.png", rect);
		frame = SpriteFrame::create("slime_1_2.png", rect);
		frames.pushBack(frame);
	}

	// �X�v���C�g�t���[������A�j���[�V�������쐬����@�P�R�}�P�b�\��
	auto anime = Animation::createWithSpriteFrames(frames, 60.0 / 60.0);

	// �S�R�}�A�j���[�V�����𖳌��ɌJ��Ԃ��A�N�V�������쐬
	auto action = RepeatForever::create(Animate::create(anime));

	// �A�N�V�������X�v���C�g�Ɏ���
	Sp->runAction(action);

	// �V�[���ɒǉ�
	this->addChild(Sp);

	//sp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(sp);

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();
	return true;
}

//=========================================================================================================================
// ���t���[���Ă΂�鏈��
//=========================================================================================================================
void GameScene::update(float dt) {

}
//=========================================================================================================================
// ��ʑJ�ڂ̃g�����W�V�������I�����������ɂP�x�����Ă΂�郁�\�b�h
//=========================================================================================================================
void GameScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}

//=========================================================================================================================
// �^�b�`�����u�ԂɌĂ΂�郁�\�b�h
//=========================================================================================================================
bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	Vec2 touchPos = pTouch->getLocation();

	return true;
}
//=========================================================================================================================
// �^�b�`����Ă��鎞�ɌĂ΂�郁�\�b�h
//=========================================================================================================================
void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
//=========================================================================================================================
// �^�b�`�������ꂽ���ɂ�΂�郁�\�b�h
//=========================================================================================================================
void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {

}