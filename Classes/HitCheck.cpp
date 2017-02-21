//================================================================================================================
// HitCheck.cpp
// ����ҁF�ˌy����
//================================================================================================================
/* �T�v
		���̃N���X�ł�
		�E�G�ƗE�ҁi�܂��͂��ꂳ��j���m�̓����蔻��
		�E�G���m�̓����蔻��
		�̂Q�̔�������邽�߂̊֐�������܂��B
   �g������
		HitCheck check;
		if (check.EnemyAndChara(�G�̏���Vector<Sprite*>��, �E�ҁi�܂��͂��ꂳ��j�̏���Sprite*��) == true) {
			�G�ƗE�ҁi�܂��͂��ꂳ��j���G��Ă��鎞�̏���
		}
		if (check.EnemyAndEnemy(�G�̏���Vector<Sprite*>��) == true){
			�G���m���G��Ă��鎞�̏���
		}
  */
  //================================================================================================================
  // �o�[�W����
  //		1.0 �N���X����                              2017/02/21 �ˌy���� 
  //================================================================================================================
#include "HitCheck.h"
using namespace cocos2d;

//=========================================================================================================================
// �����蔻��F�G�ƗE�ҁi�܂��͂��ꂳ��j���m�̓����蔻�������
//=========================================================================================================================
bool HitCheck::EnemyAndChara(Vector<Sprite*> spCon, Sprite* player) {
	// �����蔻��͈̔�
	int disMax = 64;
	for (auto enemy : spCon) {
		// �G�ƗE�ҁi�������͂��ꂳ��j�̋������v�Z
		float distance = player->getPosition().getDistance(enemy->getPosition());
		// �G�ƗE�ҁi�܂��͂��ꂳ��j�̋����������蔻��͈͓̔��Ȃ�true��Ԃ�
		if (distance <= disMax)
			return true;
	}
	// �G�ƗE�ҁi�������͂��ꂳ��j���G��Ă��Ȃ����false��ς���
	return false;
}
//=========================================================================================================================
// �����蔻��F�G�ƓG���m�̓����蔻�������
//=========================================================================================================================
bool HitCheck::EnemyAndEnemy(Vector<cocos2d::Sprite*> spCon) {
	// �����蔻��͈̔�
	int disMax = 64;
	for (auto enemy1 : spCon) {
		for (auto enemy2 : spCon) {
			// �����G�͔�r���Ȃ�
			if (enemy1 == enemy2) continue;
			else {
				// �G���m�̋������v�Z
				float distance = enemy1->getPosition().getDistance(enemy2->getPosition());
				// �G���m�̋����������蔻��͈͓̔��Ȃ�true��Ԃ�
				if (distance <= disMax) {
					return true;
				}
			}
		}
	}
	// �G���m���d�Ȃ��Ă��Ȃ����false��Ԃ�
	return false;
}