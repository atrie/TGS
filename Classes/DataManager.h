#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "cocos2d.h"

class DataManager {
private:
	cocos2d::Sprite* hero;							// �E�҂̏��
	cocos2d::Sprite* mother;						// ���ꂳ��̏��
	cocos2d::Vector<cocos2d::Sprite*> enemyCon;		// �G�̏��i�R���e�i�j
public:
	//-----------------------------------------------------
	// �Z�b�g�֐�
	void SetHero(cocos2d::Sprite* sp);
	void SetMother(cocos2d::Sprite* sp);
	void SetEnemyCon(cocos2d::Vector<cocos2d::Sprite*> spCon);
	//-----------------------------------------------------
	// �Q�b�g�֐�
	cocos2d::Sprite* GetHero();
	cocos2d::Sprite* GetMother();
	cocos2d::Vector<cocos2d::Sprite*> GetEnemyCon();
};

#endif