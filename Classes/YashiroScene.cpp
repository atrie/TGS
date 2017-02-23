//=========================================================================================================================
// �E�҂������i�Ƃ肠�����j�V�[���N���X
// YashiroScene.cpp
// ����� ����b��
//=========================================================================================================================
#include "YashiroScene.h"
//#include "TitleScene.h"
using namespace cocos2d;

DataManager* YashiroScene::datamanager;

static int ENEMY_SPAWN_RATE = 50;//�G�̏o���p�x

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

	DistanceOnOff = true;//������T�����Ɏg��

	BraveAni = 0;//�E�҂̃A�j���[�V������؂�ւ��邽�߂̕ϐ�
	EnemysTag = 0;//�G�̃^�O
	distance2 = 10000000000000000;

	//��l��(�E�҂͉p���Brave�Ƃ���)
	BraveSp = Sprite::create("Brave0.png");
	BraveSp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	BraveSp->setScale(0.5f);
	this->addChild(BraveSp);

	//�E�҃A�j���[�V�������s
	this->BraveAnimation();

	//this->addEnemys();

	// update�𖈃t���[�����s����悤�ɓo�^����
	this->scheduleUpdate();
	return true;
}

//=========================================================================================================================
// ���t���[���Ă΂�鏈��
//=========================================================================================================================
void YashiroScene::update(float dt) 
{
	//�����_���̐��l
	int randam = _engine() % ENEMY_SPAWN_RATE;
	//randam��0�ɂȂ�����G����
	if (randam == 0)
	{
		this->addEnemys();
	}

	for (Sprite* Enemys : _enemys)
	{
		//�G�̍ő�l������
		int MaxEnemyTag = EnemysTag;
		for (int count = 0; count < MaxEnemyTag; MaxEnemyTag--)
		{
			log("x���W�F%i", MaxEnemyTag);
			//�G�|�W�V�����擾
			Sprite* SetEnemy = (Sprite *)this->getChildByTag(MaxEnemyTag);
			Vec2 EnemysPos = SetEnemy->getPosition();
			log("x���W�F%f, y���W�F%f", EnemysPos.x, EnemysPos.y);

			//�E�҂̈ʒu
			Vec2 BravePoint2 = BraveSp->getPosition();
			//�G�̑��x
			float EnemysSpeed = 2;
			//�E�Ғǔ�
			float Angle2 = ccpToAngle(ccpSub(BravePoint2, EnemysPos));//�p�x�����߂� ��EnemysPos=�G�̈ʒu
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

				//���߂��G���Z�b�g(�^�O�擾)SetTag��int
				SetTag = Enemys->getTag();

				log("MaxEnemyTagMin = %d", MaxEnemyTag);
				//��ԋ߂��G�����̃X�v���C�g�ɓ����
				Sprite* SetTagEnemy = (Sprite *)this->getChildByTag(MaxEnemyTag);
				//�I�΂ꂽ�G�̃|�W�V�����擾
				EnemyPos = SetTagEnemy->getPosition();
			}
		}
		//�E�҂̑��x
		float BraveSpeed = 1;
		//�E�Ғǔ�
		Vec2 BravePoint = BraveSp->getPosition();//�E�҂̈ʒu
		float Angle = ccpToAngle(ccpSub(EnemyPos, BravePoint));//�p�x�����߂� ��EnemysPos=�G�̈ʒu
		Angle = CC_RADIANS_TO_DEGREES(Angle);
		Vec2 dir = Vec2(
			cos(CC_DEGREES_TO_RADIANS(-Angle)),
			sin(CC_DEGREES_TO_RADIANS(Angle))
			);
		// ���݂̈ʒu�Ɉړ��������ړ����x�����Z
		Vec2 BraveVec2 = BraveSp->getPosition() + dir * BraveSpeed;
		BraveSp->setPosition(BraveVec2);

		//----------------------
		//�������瓖���蔻��
		//----------------------
		BraveRect = BraveSp->getBoundingBox();//�E�҂̒Z�`�����o��
		//�E�҂ƓG�̓����蔻��
		if (BraveRect.containsPoint(EnemyPos))
		{
			log("ON");
		}
		break;
	}
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
	EnemysTag++;//�^�O���₷
	Enemys->setTag(EnemysTag);//�^�O��ۑ��@�Ȃ�̃p�[�c���l���������f���邽��
	Enemys->setScale(0.5f);
	//�o���ʒu�����_��
	//float randparts = _engine() % 7 + 2;
	//float partsPosX = randparts / 10;
	float partsXPos = _engine() % static_cast<int>(visibleSize.width); //X���̃����_��
	float partsYPos = _engine() % static_cast<int>(visibleSize.height);//Y���̃����_��
	Enemys->setPosition(Vec2(partsXPos, partsYPos));//�p�[�c�̔z�u
	this->addChild(Enemys);
	_enemys.pushBack(Enemys);//�x�N�^�[�ɒǉ�
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