//
//  Gear4Bullet.h
//  BoxCollTest
//
//  Created by 龙灵修 on 13-12-21.
//
//

#ifndef __BoxCollTest__Gear4Bullet__
#define __BoxCollTest__Gear4Bullet__

#include "GameHeaders.h"

class Gear4Bullet : public CCNode , public BoxDelegate {
    
    
public:
    
    Gear4Bullet(){
        
        sprite = NULL;
    }
    
    ~Gear4Bullet(){
        
    }
    
    virtual void binderSprite(CCSprite* sp ){
        this->sprite = sp;
    }

    void getBinderSprite(CCSprite* sp ){
        
        
    }
    
    virtual void showLog(){
        
        CCLOG("我是子弹");
    }
    
    virtual bool killBody(){
        
        return true;
    }
    
    virtual void kill(){
        
        CCLog("bullet kill ");
        
        this->scheduleOnce(schedule_selector(Gear4Bullet::callback), 1.0f);
        
    }
 
    void callback( float dt ){
        
        CCLog("子弹执行完动画之后,移除了");
        this->removeFromParentAndCleanup( true );
        
    }
    static Gear4Bullet* createWithFather( CCNode* node );
    bool initWithFahter( CCNode* node );

private:
        CCSprite* sprite;

};


#endif /* defined(__BoxCollTest__Gear4Bullet__) */
