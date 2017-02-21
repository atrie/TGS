//----------------------------------------------------------------------------------------------------------------
// �E�҂������i�Ƃ肠�����j�V�[���N���X
// YashiroScene.h
// ����ҁF����b��
//----------------------------------------------------------------------------------------------------------------
#ifndef __YASHIRO_SCENE_H__
#define __YASHIRO_SCENE_H__

#include "cocos2d.h"
#include "DataManager.h"

//----------------------------------------------------------------------------------------------------------------
// GameScene�N���X�̒�`�F�V�[���N���X��Layer�N���X���p������
//----------------------------------------------------------------------------------------------------------------
class YashiroScene : public cocos2d::Layer {
private:
	// �f�[�^���L
	static DataManager* datamanager;

	cocos2d::Sprite* BraveSp;		//�v���C���[�̃X�v���C�g

	float generateRandom(float min, float max);//�����_���ϐ��̏�����
	int BraveAni;	//�E�҂̃A�j���[�V������؂�ւ��邽�߂̕ϐ�

	void BraveAnimation();	//�j���A�j���[�V����

	cocos2d::Sprite* addEnemys();//�G������

	CC_SYNTHESIZE(std::mt19937, _engine, Engine);//�����_���̕ϐ�
protected:
	YashiroScene();							// �R���X�g���N�^
	virtual ~YashiroScene();					// �f�X�g���N�^

	virtual bool init();
	virtual void update(float dt);
	virtual void onEnterTransitionDidFinish();

	// �^�b�`�C�x���g����
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

public:
	static cocos2d::Scene* createScene(DataManager* data);
	// create���\�b�h�������I�ɍ쐬����d�g�݁i�R���r�j�G���X�R���X�g���N�^�j
	CREATE_FUNC(YashiroScene);
};

#endif