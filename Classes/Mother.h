#ifndef _MOTHER_H_
#define _MOTHER_H_

#include "cocos2d.h"
#include "DataManager.h"

class Mother : public cocos2d::Layer {
private:
	cocos2d::Sprite* player;
	static DataManager* dataManager;

	// .h�ɃN���X�̃����o�ϐ��Ƃ��Ē�`
	std::vector<cocos2d::EventKeyboard::KeyCode> pressKeys;
	// �L�[�{�[�h�������Ă��邩�ǂ����̔���
	bool IsInputKey(cocos2d::EventKeyboard::KeyCode keyCode);
public:
	virtual bool init(DataManager* data);
	virtual void update(float dt);

	static Mother* create(DataManager* data);
};

#endif