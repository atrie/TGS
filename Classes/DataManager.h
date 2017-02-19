#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "cocos2d.h"

class DataManager {
private:
	int count = 0;
public:
	void SetNum(int num);
	int GetNum();
};

#endif