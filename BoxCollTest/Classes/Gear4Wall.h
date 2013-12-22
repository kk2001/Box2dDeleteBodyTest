//
//  Gear4Wall.h
//  BoxCollTest
//
//  Created by 龙灵修 on 13-12-21.
//
//

#ifndef __BoxCollTest__Gear4Wall__
#define __BoxCollTest__Gear4Wall__

#include "GameHeaders.h"

class Gear4Wall : public CCNode , public BoxDelegate{
    
    
public:
    virtual void binderSprite(CCSprite* sp ){
        
        
    }
    
    virtual bool init(){
        
        return true;
    }
    
    CREATE_FUNC( Gear4Wall);
    
    virtual void getBinderSprite(CCSprite* sp ) {}
    
    virtual void showLog(){
        
        CCLog("我是墙");
    }
    virtual bool killBody(){
        
        return  true;
    }
       virtual void kill(){
        
        CCLog("wall kill ");
        this->removeFromParentAndCleanup( true );
       }
    

};

#endif /* defined(__BoxCollTest__Gear4Wall__) */
