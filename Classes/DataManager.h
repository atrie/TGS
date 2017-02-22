#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "cocos2d.h"

class DataManager {
private:
	cocos2d::Sprite* hero;							// 勇者の情報
	cocos2d::Sprite* mother;						// お母さんの情報
	cocos2d::Vector<cocos2d::Sprite*> enemyCon;		// 敵の情報（コンテナ）
public:
	//-----------------------------------------------------
	// セット関数
	void SetHero(cocos2d::Sprite* sp);
	void SetMother(cocos2d::Sprite* sp);
	void SetEnemyCon(cocos2d::Vector<cocos2d::Sprite*> spCon);
	//-----------------------------------------------------
	// ゲット関数
	cocos2d::Sprite* GetHero();
	cocos2d::Sprite* GetMother();
	cocos2d::Vector<cocos2d::Sprite*> GetEnemyCon();
};

#endif