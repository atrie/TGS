#ifndef _MOTHER_H_
#define _MOTHER_H_

#include "cocos2d.h"
#include "DataManager.h"

class Mother : public cocos2d::Layer {
private:
	cocos2d::Sprite* player;
	static DataManager* dataManager;

	// .hにクラスのメンバ変数として定義
	std::vector<cocos2d::EventKeyboard::KeyCode> pressKeys;
	// キーボードを押しているかどうかの判定
	bool IsInputKey(cocos2d::EventKeyboard::KeyCode keyCode);
public:
	virtual bool init(DataManager* data);
	virtual void update(float dt);

	static Mother* create(DataManager* data);
};

#endif