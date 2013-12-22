//
//  HelloWorldScene.cpp
//  BoxCollTest
//
//  Created by 龙灵修 on 13-12-21.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "HelloWorldScene.h"
#include <vector>
using namespace std;
#include "SimpleAudioEngine.h"
#include "Gear4Ceshi.h"
#include "Gear4Wall.h"
#include "Gear4Bullet.h"
using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}

HelloWorld::HelloWorld()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    // init physics
    this->initPhysics();

    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("blocks.png", 100);
    m_pSpriteTexture = parent->getTexture();

    addChild(parent, 0, kTagParentNode);


    addNewSpriteAtPosition(ccp(s.width/2, s.height/2));

    CCLabelTTF *label = CCLabelTTF::create("Tap screen", "Marker Felt", 32);
    addChild(label, 0);
    label->setColor(ccc3(0,0,255));
    label->setPosition(ccp( s.width/2, s.height-50));
    
    scheduleUpdate();
}

HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
    
    //delete m_debugDraw;
}

void HelloWorld::initPhysics()
{

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);

//     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
//     world->SetDebugDraw(m_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //m_debugDraw->SetFlags(flags);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom

    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    
    Gear4Bullet* b = Gear4Bullet::createWithFather( this );
    this->addChild( b );
    b2BodyDef bf;
    bf.position.Set( 100/PTM_RATIO, 100/PTM_RATIO);
    bf.userData = b;
    
    b2Body* body = world->CreateBody( &bf );
    
    b2CircleShape shape;
    shape.m_radius = 10 / PTM_RATIO;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    
    body->CreateFixture(&fd);
    
    
    
    Gear4Wall* w = Gear4Wall::create();
    this->addChild( w );
    b2BodyDef ok;
    ok.position.Set( 100/PTM_RATIO, 100/PTM_RATIO);
    ok.userData = w;
    
    b2Body* nbody = world->CreateBody( &ok );
    
    b2FixtureDef _fd;
    _fd.shape = &shape;
    _fd.density = 1.0f;
    
    nbody->CreateFixture(&_fd);
    
    
    
    
    //------
    Gear4Ceshi* ceshi = Gear4Ceshi::create();
    this->addChild( ceshi );
    b2BodyDef bbd;
    bbd.position.Set( 100/PTM_RATIO, 100/PTM_RATIO);
    bbd.userData = ceshi;
    
    b2Body* xnbody = world->CreateBody( &bbd );
    
    b2FixtureDef _afd;
    _afd.shape = &shape;
    _afd.density = 1.0f;
    
    xnbody->CreateFixture(&_afd);

}

void HelloWorld::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
}

void HelloWorld::addNewSpriteAtPosition(CCPoint p){}


void HelloWorld::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    
    vector<b2Body*> destoryVector;
    
    //Iterate over the bodies in the physics world
    b2Body* b = world->GetBodyList();
    
    while ( b ) {
        
       if (b->GetUserData() != NULL) {
           
            Gear4Bullet* g = (Gear4Bullet*)b->GetUserData();
            if ( g  != NULL) {
                g->showLog();
                if ( g->killBody()) {
                    /**
                    g->removeFromParentAndCleanup( true );
                    
                    g = NULL;
                    
                    world->DestroyBody( b );
                     **/
                    g->kill();
                    destoryVector.push_back( b );
                    
                }
                
            }
                   
               }
        
        b = b->GetNext();
    }
    

    //  是用于删除刚体 其他的我不关
    vector<b2Body*>::iterator it = destoryVector.begin();
    
    while ( it != destoryVector.end() ) {
        
        b2Body* b = *it;
        
        world->DestroyBody( b );
        
        CCLog("销毁 ");
    
        it++;
    }
    destoryVector.clear();
    
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        addNewSpriteAtPosition( location );
    }
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
