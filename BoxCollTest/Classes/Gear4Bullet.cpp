//
//  Gear4Bullet.cpp
//  BoxCollTest
//
//  Created by 龙灵修 on 13-12-21.
//
//

#include "Gear4Bullet.h"


bool Gear4Bullet::initWithFahter(cocos2d::CCNode *node){
    
    
    return true;
}


Gear4Bullet* Gear4Bullet::createWithFather(cocos2d::CCNode *node){
    
    Gear4Bullet* g = new Gear4Bullet;
    
    if ( g && g->initWithFahter(node)) {
        g->autorelease();
        return g;
    }
    
    CC_SAFE_DELETE( g );
    return NULL;
}