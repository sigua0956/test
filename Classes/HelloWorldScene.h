#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Plane.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
	HelloWorld();
	~HelloWorld();

    CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode, BatchNode);
    CC_SYNTHESIZE_RETAIN(Plane*,_player,Player);
    
//private:
//    cocos2d::CCSpriteBatchNode* _batchNode;
//public:
//    virtual cocos2d::CCSpriteBatchNode* getBatchNode()
//    {
//        return _batchNode;
//    }
//    
//    virtual void setBatchNode(cocos2d::CCSpriteBatchNode* node)
//    {
//        if (_batchNode != node)
//        {
//            CC_SAFE_RETAIN(node);
//            CC_SAFE_RELEASE(_batchNode);
//            //_batchNode->release();
//            _batchNode = node;
//        }
//    }
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool,
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	virtual void menuCloseCallback(cocos2d::CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

	void spriteMoveFinished(cocos2d::CCNode* sender);

	void gameLogic(float dt);

	void updateGame(float dt);
    
    void addMissile(float dt);
    void releaseMissile(CCNode *pSender);
    
	void registerWithTouchDispatcher();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void gameover(CCNode* sender);
    //virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
protected:
	cocos2d::CCArray *_targets;
	cocos2d::CCArray *_projectiles;
	int _projectilesDestroyed;

	void addTarget();
private:
   Plane * m_SelectSprite;

};

#endif  // __HELLOWORLD_SCENE_H__