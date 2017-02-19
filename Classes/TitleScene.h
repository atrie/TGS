//----------------------------------------------------------------------------------------------------------------
// �Q�[���V�[���N���X
// TitleScene.h
// ����ҁF�ˌy����
//----------------------------------------------------------------------------------------------------------------
#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
#include "DataManager.h"

//----------------------------------------------------------------------------------------------------------------
// TitleScene�N���X�̒�`�F�V�[���N���X��Layer�N���X���p������
//----------------------------------------------------------------------------------------------------------------
class TitleScene : public cocos2d::Layer {
private:
	static DataManager* datamanager;
protected:
	TitleScene();							// �R���X�g���N�^
	virtual ~TitleScene();					// �f�X�g���N�^

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
	CREATE_FUNC(TitleScene);
};

#endif