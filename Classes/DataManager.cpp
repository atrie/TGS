#include "DataManager.h"

using namespace cocos2d;

void DataManager::SetNum(int num) {
	count += num;
}

int DataManager::GetNum() {
	return count;
}