#ifndef _HITCHECK_H_
#define _HITCHECK_H_

#include "cocos2d.h"

class HitCheck {
private:
public:
	// �G�ƓG���m�̓����蔻��
	bool EnemyAndEnemy(cocos2d::Vector<cocos2d::Sprite*> spCon);
	// �G�ƗE�ҁi�܂��͂��ꂳ��j���m�̓����蔻��
	bool EnemyAndChara(cocos2d::Vector<cocos2d::Sprite*> spCon, cocos2d::Sprite* player);
	// �E�҂Ƃ��ꂳ�񓯎m�̓����蔻��
	bool HeroAndMother(cocos2d::Sprite* hero, cocos2d::Sprite* mother);
};

#endif