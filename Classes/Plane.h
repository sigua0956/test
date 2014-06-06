//
//  Plane.h
//  SimpleGame
//
//  Created by xiaohua.si on 14-5-14.
//
//

#ifndef __SimpleGame__Plane__
#define __SimpleGame__Plane__

#include "cocos2d.h"
#include <iostream>
typedef enum{
    k_Plane_Type_Player = 0,
    k_Plane_Type_Enemy,
}PlaneType;
class Plane:  public cocos2d::CCNode
{
public:
    static Plane* create(PlaneType type = k_Plane_Type_Enemy);
    bool init(PlaneType type = k_Plane_Type_Enemy);
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _PlaneSprite, PlaneSprite);
    CC_SYNTHESIZE_READONLY(int, _type, Type);
    
    cocos2d::CCRect getCollisionArea();
    //播放被捕捉的动画
    void beCaught();
    //移动鱼到destination
    void moveTo(cocos2d::CCPoint destination);
    //重设鱼的状态
    void reset();
    
    //void setPosition(const cocos2d::CCPoint& pos);
protected:
    void moveEnd();
    void beCaught_CallFunc();
    
};



#endif /* defined(__SimpleGame__Plane__) */
