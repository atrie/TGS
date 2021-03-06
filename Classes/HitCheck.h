#ifndef _HITCHECK_H_
#define _HITCHECK_H_

#include "cocos2d.h"

class HitCheck {
private:
public:
	// 敵と敵同士の当たり判定
	bool EnemyAndEnemy(cocos2d::Vector<cocos2d::Sprite*> spCon);
	// 敵と勇者（またはお母さん）同士の当たり判定
	bool EnemyAndChara(cocos2d::Vector<cocos2d::Sprite*> spCon, cocos2d::Sprite* player);
	// 勇者とお母さん同士の当たり判定
	bool HeroAndMother(cocos2d::Sprite* her, cocos2d::Sprite* mothe);
};

#endif