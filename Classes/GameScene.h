//----------------------------------------------------------------------------------------------------------------
// �Q�[���V�[���N���X
// GameScene.h
// ����ҁF�ˌy����
//----------------------------------------------------------------------------------------------------------------
#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "DataManager.h"

//----------------------------------------------------------------------------------------------------------------
// GameScene�N���X�̒�`�F�V�[���N���X��Layer�N���X���p������
//----------------------------------------------------------------------------------------------------------------
class GameScene : public cocos2d::Layer {
private:
	// �f�[�^���L
	static DataManager* datamanager;
protected:
	GameScene();							// �R���X�g���N�^
	virtual ~GameScene();					// �f�X�g���N�^

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
	CREATE_FUNC(GameScene);
};

#endif