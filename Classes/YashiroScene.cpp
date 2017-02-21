//=========================================================================================================================
// �E�҂������i�Ƃ肠�����j�V�[���N���X
// YashiroScene.cpp
// ����� ����b��
//=========================================================================================================================
#include "YashiroScene.h"
//#include "TitleScene.h"
using namespace cocos2d;

DataManager* YashiroScene::datamanager;

//=========================================================================================================================
// Layer��Scene�ɓ\��t���ĕԂ����\�b�h
//=========================================================================================================================
Scene* YashiroScene::createScene(DataManager* data) {
	datamanager = data;
	Scene* scene = Scene::create();
	YashiroScene* layer = YashiroScene::create();
	scene->addChild(layer);
	return scene;
}
//=========================================================================================================================
// �R���X�g���N�^
//=========================================================================================================================
YashiroScene::YashiroScene() {
	// �����o�ϐ��̏�����
	//�����̏�����(_engine���g���ƃ����_���ɂȂ�)
	std::random_device rdev;
	_engine.seed(rdev());
}
//=========================================================================================================================
// �f�X�g���N�^
//=========================================================================================================================
YashiroScene::~YashiroScene() {
	// �����o�ϐ��̉��
}
//�����_���ϐ��̏�����
float YashiroScene::generateRandom(float min, float max)
{
	std::uniform_real_distribution<float> dest(min, max);
	return dest(_engine);
}
//=========================================================================================================================
// �����������F�V�[���i��ʁj�̎��O����
//=========================================================================================================================
bool YashiroScene::init() {
	if (!Layer::init())	return false;
	//------------------------------------------------------------------------------------------
	// ��ʃT�C�Y�ƌ��_���W���擾
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//------------------------------------------------------------------------------------------
	// �^�b�`�C�x���g��L���ɂ���
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(YashiroScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(YashiroScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(YashiroScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Label* label = Label::createWithTTF("Yashiro", "fonts/Marker Felt.ttf", 60);
	label->setPosition(Vec2(visibleSize.width /2, visibleSize.height / 2));
	this->addChild(label);

	BraveAni = 0;//�E�҂̃A�j���[�V������؂�ւ��邽�߂̕ϐ�

	//��l��(�E�҂͉p���Brave�Ƃ���)
	BraveSp = Sprite::create("Brave0.png");
	BraveSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BraveSp);

	//�E�҃A�j���[�V�������s
	this->BraveAnimation();

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();
	return true;
}

//=========================================================================================================================
// ���t���[���Ă΂�鏈��
//=========================================================================================================================
void YashiroScene::update(float dt) {

}
//=========================================================================================================================
// �v���C���[�̃A�j���[�V����
//=========================================================================================================================
void YashiroScene::BraveAnimation()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::vector<std::string> fileNames[1];

	BraveSp->setTexture("Brave0.png");
	// �j��
	fileNames[0].push_back("Brave0.png");
	fileNames[0].push_back("Brave1.png");
	fileNames[0].push_back("Brave0.png");
	fileNames[0].push_back("Brave2.png");

	Animation* animation = Animation::create();

	for (std::string fileName : fileNames[BraveAni])
	{
		animation->addSpriteFrameWithFile(fileName);
	}
	animation->setDelayPerUnit(0.3f);			// �摜�؂�ւ��̃f�B���C
	animation->setRestoreOriginalFrame(true);	// �A�j���[�V�������I������ۂɍŏ��̃t���[���ɖ߂�
												//�X�v���C�g�̃A�N�V������S����~�I
	BraveSp->stopAllActions();
	BraveSp->runAction(RepeatForever::create(Animate::create(animation)));
}
//=========================================================================================================================
//�G������
//=========================================================================================================================
Sprite* YashiroScene::addEnemys()
{
	//��ʃT�C�Y
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�G�̍쐬
	Sprite* Enemys = Sprite::create("Enemy.png");
	//parts->setTag(partsType);//�^�O��ۑ��@�Ȃ�̃p�[�c���l���������f���邽��

	Size partsSize = Enemys->getContentSize();
	//�o���ʒu�����_��
	//int num = (rand() % NUM_MAX) + 1;
	float randparts = _engine() % 7 + 2;
	float partsPosX = randparts / 10;
	//float partsXPos = _engine() % static_cast<int>(visibleSize.width / 2); //X���̃����_��
	float partsYPos = _engine() % static_cast<int>(visibleSize.height / 2);//Y���̃����_��
	Enemys->setPosition(Vec2(visibleSize.width * partsPosX, partsYPos));//�p�[�c�̔z�u
	this->addChild(Enemys);
	//_parts.pushBack(parts);//�x�N�^�[�ɒǉ�
	return Enemys;
}
//=========================================================================================================================
// ��ʑJ�ڂ̃g�����W�V�������I�����������ɂP�x�����Ă΂�郁�\�b�h
//=========================================================================================================================
void YashiroScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}

//=========================================================================================================================
// �^�b�`�����u�ԂɌĂ΂�郁�\�b�h
//=========================================================================================================================
bool YashiroScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	Vec2 touchPos = pTouch->getLocation();

	return true;
}
//=========================================================================================================================
// �^�b�`����Ă��鎞�ɌĂ΂�郁�\�b�h
//=========================================================================================================================
void YashiroScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
//=========================================================================================================================
// �^�b�`�������ꂽ���ɂ�΂�郁�\�b�h
//=========================================================================================================================
void YashiroScene::onTouchEnded(Touch* pTouch, Event* pEvent) {

}