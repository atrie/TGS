//----------------------------------------------------------------------------------------------------------------
// 勇者が動く（とりあえず）シーンクラス
// YashiroScene.h
// 製作者：八代恵輔
//----------------------------------------------------------------------------------------------------------------
#ifndef __YASHIRO_SCENE_H__
#define __YASHIRO_SCENE_H__

#include "cocos2d.h"
#include "DataManager.h"

//----------------------------------------------------------------------------------------------------------------
// GameSceneクラスの定義：シーンクラスはLayerクラスを継承する
//----------------------------------------------------------------------------------------------------------------
class YashiroScene : public cocos2d::Layer {
private:
	// データ共有
	static DataManager* datamanager;

	float generateRandom(float min, float max);//ランダム変数の初期化

	bool DistanceOnOff;//距離を探す時に使う

	int BraveAni;	//勇者のアニメーションを切り替えるための変数
	int EnemysTag;	//敵のタグ
	int SetTag;		//一番近い敵のタグ

	float distance;	//距離１
	float distance2;//距離２
	float Angle2;

	void BraveAnimation();	//泳ぎアニメーション

	cocos2d::Vector<cocos2d::Sprite *> _enemys;//敵のスプライト：クラス型

	cocos2d::Sprite* addEnemys();//敵精製仮

	cocos2d::Vec2 EnemyPos;		//敵のポジション

	cocos2d::Sprite* BraveSp;	//プレイヤーのスプライト

	cocos2d::Rect BraveRect;	//勇者の短形

	CC_SYNTHESIZE(std::mt19937, _engine, Engine);//ランダムの変数
protected:
	YashiroScene();			// コンストラクタ
	virtual ~YashiroScene();// デストラクタ

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
	CREATE_FUNC(YashiroScene);
};

#endif