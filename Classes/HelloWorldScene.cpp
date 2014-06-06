#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

HelloWorld::~HelloWorld()
{
	if (_targets)
	{
		_targets->release();
		_targets = NULL;
	}

	if (_projectiles)
	{
		_projectiles->release();
		_projectiles = NULL;
	}

	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

HelloWorld::HelloWorld()
:_targets(NULL)
,_projectiles(NULL)
,_projectilesDestroyed(0)
,_batchNode(NULL)
,_player(NULL)
{
}

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
    
    
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);
        
		// Place the menu item bottom-right conner.
        CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        pCloseItem->setScale(0.5);
		pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2,
                                    origin.y + pCloseItem->getContentSize().height/2));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		/////////////////////////////
		// 2. add your codes below...
        CCSprite *background = CCSprite::create("Mainpage-bg.jpg");
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        background->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
        this->addChild(background);
        
//		CCSprite *player = CCSprite::create("Airplane.png", CCRectMake(0, 0, 80, 80) );
//        //27 40
//        player->cocos2d::CCNode::setScale(0.4);
//		player->setPosition( ccp(origin.x + visibleSize.width/2,
//                                 origin.y + player->getContentSize().height/2 ) );
//        player->setTag(99);
//       
//		this->addChild(player);
      
        CCPoint a  =  this->getPosition();
        Plane* mainplayer = Plane::create(k_Plane_Type_Player);
         //mainplayer->create(k_Plane_Type_Player);
        this->setPlayer(mainplayer);
        mainplayer->setTag(99);
        mainplayer->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + mainplayer->getPlaneSprite()->getContentSize().height / 2 * mainplayer->getPlaneSprite()->getScale() + 20));
        this->addChild(mainplayer);
        this->schedule( schedule_selector(HelloWorld::updateGame) );
         // 增加敌机
		this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );

		this->setTouchEnabled(true);

		_targets = new CCArray;
		_projectiles = new CCArray;

		// use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
		// see http://www.cocos2d-x.org/boards/6/topics/1478
       // 增加导弹
        CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("Missile.png");
        this->addChild(batchNode);
        this->setBatchNode(batchNode);
        this->schedule(schedule_selector(HelloWorld::addMissile), 0.5);
        
        //碰撞检测
             //

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);
		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    CCDirector::sharedDirector()->end();
#endif
}


// cpp with cocos2d-x
void HelloWorld::addTarget()
{
    
	CCSprite *target = CCSprite::create("Enemy.png", CCRectMake(0,0,400,400) );
     int count = target->retainCount();
    int width = target->getContentSize().width;
    target->setScale(0.15);
    width = target->getContentSize().width;
    count = target->retainCount();
	// Determine where to spawn the target along the Y axis
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	//float minY = target->getContentSize().height/2;
	//float maxY = winSize.height -  target->getContentSize().height/2;
	//int rangeY = (int)(maxY - minY);
   // srand( TimGetTicks() );
	//int actualY = ( rand() % rangeY ) + (int)minY;

    float minX = target->getContentSize().width/2;
    count = target->retainCount();
    float maxX = winSize.width - target->getContentSize().width/2;
    int rangeX = (int)(maxX - minX);
    //srand( TimGetTicks() );
    //srand(Timeg)
    
    int actualX = (rand() % rangeX) + (int)minX;
    
    
	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated
	//target->setPosition(
	//	ccp(winSize.width + (target->getContentSize().width/2),
      //      CCDirector::sharedDirector()->getVisibleOrigin().y + actualY) );
	
    target->setPosition(ccp(CCDirector::sharedDirector()->getVisibleOrigin().x + actualX, winSize.height + (target->getContentSize().height/2)));

    count = target->retainCount();
    CCFiniteTimeAction* flipYAction = CCFlipY::create(true);
    target->runAction(flipYAction);
    count = target->retainCount();
    this->addChild(target);
    count = target->retainCount();

	// Determine speed of the target
	int minDuration = (int)2.0;
	int maxDuration = (int)12.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	//CCFiniteTimeAction* actionMove = CCMoveTo::create( (float)actualDuration,
      //                                      ccp(0 - target->getContentSize().width/2,  3) );//actualY
	CCFiniteTimeAction* actionMove = CCMoveTo::create((float)actualDuration,
                                                      ccp(actualX, 0 - target->getContentSize().height/2));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this,
                                            callfuncN_selector(HelloWorld::spriteMoveFinished));
	target->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );
    target->setTag(200);
   count = target->retainCount();
	// Add to targets array
	//target->setTag(1);
	_targets->addObject(target);
    count = target->retainCount();
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
    
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
    _targets->removeObject(sprite);
    //sprite->release();
    
//	if (sprite->getTag() == 1)  // target
//	{
//		_targets->removeObject(sprite);
//        
//		GameOverScene *gameOverScene = GameOverScene::create();
//		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
//		CCDirector::sharedDirector()->replaceScene(gameOverScene);
//
//	}
//	else if (sprite->getTag() == 2) // projectile
//	{
//		_projectiles->removeObject(sprite);
//	}
}

void HelloWorld::gameLogic(float dt)
{
	this->addTarget();
}


void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    if (pTouches->count() == 1) {
        CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
        CCPoint location = touch->getLocation();
        location = CCDirector::sharedDirector()->convertToGL(location);
        //CCSprite* sprite =  (CCSprite*)(this->getChildByTag(99));
        Plane* plane = this->getPlayer();
        CCSprite* sprite =  plane->getPlaneSprite();
        /*
         CCPoint location = touch->getLocation();
         
         int x = touch->getLocation().x;
         int y = touch->getLocation().y;
         
         // 和我们的精灵比较
         CCSprite* sprite =  (CCSprite*)(this->getChildByTag(99));
         
         // 看看位置是否在图片上
         if  (
         (abs(x - sprite->getPositionX()) < sprite->getContentSize().width / 2) &&
         (abs(y - sprite->getPositionY()) < sprite->getContentSize().height / 2)
         )
         {
         m_SelectSprite = sprite;
         }
         */
        if (m_SelectSprite) {
            
            CCLog("++++++++after  x:%f, y:%f", location.x, location.y);
            CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
            
            if (location.x < sprite->getContentSize().width/2) {
                location.x = sprite->getContentSize().width/2;
            }
            if (location.y < sprite->getContentSize().height/2) {
                location.y = sprite->getContentSize().height/2;
            }
            if (location.y > winSize.height - sprite->getContentSize().height/2) {
                location.y = winSize.height - sprite->getContentSize().height/2;
            }
            
            m_SelectSprite->setPosition(touch->getLocation());
            CCPoint a = m_SelectSprite->getPosition();
            CCPoint b = m_SelectSprite->getPosition();
            
        }
    } else {
        ;
    }
    

   }


void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    m_SelectSprite = NULL;
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    
    int x = touch->getLocation().x;
    int y = touch->getLocation().y;
    
    // 和我们的精灵比较
    //CCSprite* sprite =  (CCSprite*)(this->getChildByTag(99)->getp);
    Plane* plane = this->getPlayer();
   CCSprite* sprite =  this->getPlayer()->getPlaneSprite();
    //CCPoint a = sprite->getPosition();
    
    // 看看位置是否在图片上
    if  (
         (abs(x - plane->getPositionX()) < sprite->getContentSize().width / 2 ) &&
         (abs(y - plane->getPositionY()) < sprite->getContentSize().height / 2 )
         )
    {
        m_SelectSprite = plane;
    }
    
    
    CCLOG("THelloWorld::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
}
void HelloWorld::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
       //CCLOG("THelloWorld::onTouchEnded id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    //m_SelectSprite = NULL;
     m_SelectSprite = NULL;
}
void HelloWorld::releaseMissile(CCNode *pSender)
{
    this->getBatchNode()->removeChild(pSender, true);
    _projectiles->removeObject(pSender);
   // pSender->release();
    int count = pSender->retainCount();
    pSender->stopAllActions();
    pSender->setVisible(false);
}

void HelloWorld::addMissile(float dt)
{
    //增加子弹
    CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    //CCSprite *player = (CCSprite*)(this->getChildByTag(99));
     CCSprite *player = this->getPlayer()->getPlaneSprite();
        CCSprite * sprite = CCSprite::create("Missile.png");
        this->getBatchNode()->addChild(sprite);
        CCPoint p = player->getAnchorPoint();
    int wid = player->getContentSize().width;
    wid = player->getPositionX();
    //+ player->getContentSize().width * 0.4 * player->getScale()
        sprite->setPosition(ccp(this->getPlayer()->getPositionX() , this->getPlayer()->getPositionY() + player->getContentSize().height * player->getScale()));
        sprite->setScale(0.3);
        sprite->setRotation(-90);
        CCMoveTo* moveTo = CCMoveTo::create(2,ccp(this->getPlayer()->getPositionX(),winSize.width));
        
        CCCallFuncN* callfunc = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::releaseMissile));
        
        CCFiniteTimeAction* seq = CCSequence::create(moveTo, callfunc, NULL);
        
        sprite->runAction(seq);
        sprite->setTag(10000);
        _projectiles->addObject(sprite);
        int count = sprite->retainCount();
        count = 0;
}

void HelloWorld::updateGame(float dt)
{
	//CCArray *projectilesToDelete = CCArray::create();
    CCArray *projectilesToDelete = new CCArray;
    CCObject* it = NULL;
    CCObject* jt = NULL;
    
    //CCArray* targetsToDelete = CCArray::create();
    CCArray* targetsToDelete = new CCArray;
	// for (it = _projectiles->begin(); it != _projectiles->end(); it++)
    CCARRAY_FOREACH(_projectiles, it)
	{
		CCSprite *projectile = dynamic_cast<CCSprite*>(it);
		CCRect projectileRect = CCRectMake(
			projectile->getPosition().x - (projectile->getContentSize().width/2 * projectile->getScale()),
			projectile->getPosition().y - (projectile->getContentSize().height/2 * projectile->getScale()),
			projectile->getContentSize().width * projectile->getScale(),
			projectile->getContentSize().height * projectile->getScale());

        CCARRAY_FOREACH(_targets, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			CCRect targetRect = CCRectMake(
				target->getPosition().x - (target->getContentSize().width/2 * target->getScale()),
				target->getPosition().y - (target->getContentSize().height/2  * target->getScale()),
				target->getContentSize().width * target->getScale(),
				target->getContentSize().height * target->getScale());

			// if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
            if (projectileRect.intersectsRect(targetRect))
			{
				targetsToDelete->addObject(target);
			}
		}

		// for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
        CCARRAY_FOREACH(targetsToDelete, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			_targets->removeObject(target);
			this->removeChild(target, true);

            int count = target->retainCount();
            
			_projectilesDestroyed++;
//			if (_projectilesDestroyed >= 5)
//			{
//				GameOverScene *gameOverScene = GameOverScene::create();
//				gameOverScene->getLayer()->getLabel()->setString("You Win!");
//				CCDirector::sharedDirector()->replaceScene(gameOverScene);
//			}
		}

		if (targetsToDelete->count() > 0)
		{
			projectilesToDelete->addObject(projectile);
		}
	}
   
    
    if (this->getPlayer()) {
        CCSprite* mainplayer = this->getPlayer()->getPlaneSprite();
        int wd = this->getPlayer()->getPosition().x;
        CCRect mainplayerRect = CCRectMake(this->getPlayer()->getPosition().x - (mainplayer->getContentSize().width/2 * mainplayer->getScale()),
                                           this->getPlayer()->getPosition().y - (mainplayer->getContentSize().height/2 * mainplayer->getScale()),
                                           mainplayer->getContentSize().width* mainplayer->getScale(),
                                           mainplayer->getContentSize().height* mainplayer->getScale());
        CCARRAY_FOREACH(_targets, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			CCRect targetRect = CCRectMake(
                                           target->getPosition().x - (target->getContentSize().width/2 * target->getScale()),
                                           target->getPosition().y - (target->getContentSize().height/2  * target->getScale()),
                                           target->getContentSize().width * target->getScale(),
                                           target->getContentSize().height * target->getScale());
            
			// if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
            if (mainplayerRect.intersectsRect(targetRect))
			{
				targetsToDelete->addObject(target);
                CCFiniteTimeAction* actiongameover = CCCallFuncN::create( this,
                                                                         callfuncN_selector(HelloWorld::gameover));
                mainplayer->runAction( actiongameover);

			}
		}
    }
    
    
    CCARRAY_FOREACH(projectilesToDelete, it)
	{
		CCSprite* projectile = dynamic_cast<CCSprite*>(it);
		_projectiles->removeObject(projectile);
        this->getBatchNode()->removeChild(projectile, true);
	}
    targetsToDelete->release();
	projectilesToDelete->release();
}
void HelloWorld::gameover(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
    
    GameOverScene *gameOverScene = GameOverScene::create();
    gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
    CCDirector::sharedDirector()->replaceScene(gameOverScene);

}
void HelloWorld::registerWithTouchDispatcher()
{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
