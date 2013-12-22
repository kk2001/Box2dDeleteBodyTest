//
//  GameHeaders.h
//  BoxCollTest
//
//  Created by 龙灵修 on 13-12-21.
//
//

#ifndef BoxCollTest_GameHeaders_h
#define BoxCollTest_GameHeaders_h

#include "cocos2d.h"
using namespace cocos2d;

class BoxDelegate  {
    
    
public:
   
    virtual void binderSprite(CCSprite* sp ) = 0;

   virtual void getBinderSprite(CCSprite* sp ) = 0;
    
    virtual void showLog() = 0 ;
    virtual bool killBody() = 0;
    
    virtual void kill() = 0 ;
    
    
};



#endif
