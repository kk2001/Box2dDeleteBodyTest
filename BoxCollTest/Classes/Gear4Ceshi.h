//
//  Gear4Ceshi.h
//  BoxCollTest
//
//  Created by 龙灵修 on 13-12-22.
//
//

#ifndef __BoxCollTest__Gear4Ceshi__
#define __BoxCollTest__Gear4Ceshi__

#include "Gear4Wall.h"

class Gear4Ceshi :public Gear4Wall{
    
    
public:
   
       virtual void binderSprite(CCSprite* sp ){
        
        
    }
 
    virtual bool init(){
        
        return true;
    }
    
    CREATE_FUNC( Gear4Ceshi);
    
    virtual void getBinderSprite(CCSprite* sp ) {}
    
    virtual void showLog(){
        
        CCLog("我是测试");
    }
    virtual bool killBody(){
        
        return  true;
    }
    
    virtual void kill(){
        
        CCLog("ceshi kill ");
        this->removeFromParentAndCleanup( true );
    }
};

#endif /* defined(__BoxCollTest__Gear4Ceshi__) */
