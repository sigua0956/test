//
//  Plane.cpp
//  SimpleGame
//
//  Created by xiaohua.si on 14-5-14.
//
//

#include "Plane.h"
USING_NS_CC;
enum{
    k_Action_Animate = 0,
    k_Action_MoveTo
};
Plane* Plane::create(PlaneType type)
{
    Plane* plane = new Plane();
    if (plane) {
        plane->init(type);
        plane->autorelease();
    }

    return plane;
}

bool Plane::init(PlaneType type)
{
    bool bRet = false;
    if ((bRet = CCNode::init()))
    {
        _type = type;
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        if (type == k_Plane_Type_Player) {
            _PlaneSprite = CCSprite::create("Airplane.png");
            int width = _PlaneSprite->getContentSize().width;
            _PlaneSprite->setScale(0.4);
            //_PlaneSprite->cocos2d::CCNode::setPosition(ccp(origin.x + visibleSize.width/2,origin.y + _PlaneSprite->getContentSize().height/2 ));
            this->setPosition(ccp(0,0));
        } else {
            _PlaneSprite = CCSprite::create("Enemy.png");
        }
        this->addChild(_PlaneSprite);
        bRet = true;
    }
    return bRet;
//   // CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), _type);
//    CCAnimation* fishAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
//    CCAnimate* fishAnimate = CCAnimate::create(fishAnimation);
//    fishAnimate->setTag(k_Action_Animate);
//    _fishSprite = CCSprite::create();
//    this->addChild(_fishSprite);
//    _fishSprite->runAction(CCRepeatForever::create(fishAnimate));
}
//void Plane::setPosition(const CCPoint& pos)
//{
//    CCNode::setPosition(pos);
//    _PlaneSprite->setPosition(pos);
//}
CCRect Plane::getCollisionArea()
{
    CCAssert(this->getParent(), "You Should Call This After Add it as a child");
    CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
    CCSize size = _PlaneSprite->getContentSize();
    return CCRectMake(origin.x-size.width*0.5, origin.y-size.height*0.5, size.width, size.height);
}
//void Plane::beCaught()
//{
//    this->stopActionByTag(k_Action_MoveTo);
//    CCDelayTime* delayTime = CCDelayTime::create(1.0);
//    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Fish::beCaught_CallFunc));
//    CCFiniteTimeAction* seq = CCSequence::create(delayTime, callFunc, NULL);
//    
//    CCBlink* blink = CCBlink::create(1.0, 8);
//    CCFiniteTimeAction *spawn = CCSpawn::create(seq, blink, NULL);
//    this->runAction(spawn);
//}
//void Fish::beCaught_CallFunc()
//{
//    this->getParent()->removeChild(this, false);
//}
//void Fish::moveTo(CCPoint destination)
//{
//    CCPoint start = this->getParent()->convertToWorldSpace(this->getPosition());
//    float speed = ccpDistance(destination, start) / 200;
//    CCMoveTo* moveTo = CCMoveTo::create(speed ,destination);
//    CCCallFunc* callfunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));
//    
//    CCFiniteTimeAction* seq = CCSequence::create(moveTo, callfunc, NULL);
//    seq->setTag(k_Action_MoveTo);
//    this->runAction(seq);
//}
//void Fish::reset()
//{
//    this->setRotation(0);
//    this->setVisible(true);
//}
//void Fish::moveEnd()
//{
//    this->getParent()->removeChild(this, false);
//}
