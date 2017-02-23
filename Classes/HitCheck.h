#ifndef _HITCHECK_H_
#define _HITCHECK_H_

#include "cocos2d.h"

class HitCheck {
private:
public:
	// “G‚Æ“G“¯m‚Ì“–‚½‚è”»’è
	bool EnemyAndEnemy(cocos2d::Vector<cocos2d::Sprite*> spCon);
	// “G‚Æ—EÒi‚Ü‚½‚Í‚¨•ê‚³‚ñj“¯m‚Ì“–‚½‚è”»’è
	bool EnemyAndChara(cocos2d::Vector<cocos2d::Sprite*> spCon, cocos2d::Sprite* player);
	// —EÒ‚Æ‚¨•ê‚³‚ñ“¯m‚Ì“–‚½‚è”»’è
	bool HeroAndMother(cocos2d::Sprite* hero, cocos2d::Sprite* mother);
};

#endif