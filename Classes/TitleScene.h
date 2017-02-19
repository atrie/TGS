//----------------------------------------------------------------------------------------------------------------
// ゲームシーンクラス
// TitleScene.h
// 製作者：戸軽隆二
//----------------------------------------------------------------------------------------------------------------
#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
#include "DataManager.h"

//----------------------------------------------------------------------------------------------------------------
// TitleSceneクラスの定義：シーンクラスはLayerクラスを継承する
//----------------------------------------------------------------------------------------------------------------
class TitleScene : public cocos2d::Layer {
private:
	static DataManager* datamanager;
protected:
	TitleScene();							// コンストラクタ
	virtual ~TitleScene();					// デストラクタ

	virtual bool init();
	virtual void update(float dt);
	virtual void onEnterTransitionDidFinish();

	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

public:
	static cocos2d::Scene* createScene(DataManager* data);
	// createメソッドを自動的に作成する仕組み（コンビニエンスコンストラクタ）
	CREATE_FUNC(TitleScene);
};

#endif