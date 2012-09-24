#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    pSprite->setScale(1.5);

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    //Shader Effects:
    _uniformSprites=CCArray::create();
    _uniformSprites->retain();
    addStaticTVEffectToSprite(pSprite);
    
    CCSprite * sadako=CCSprite::create("sadako.png");
    sadako->setPosition(ccp(size.width/2,size.height/3));
    addChild(sadako);
    CCDelayTime * delay=CCDelayTime::create(1.5);
    CCMoveBy*moveRight=CCMoveBy::create(.01, ccp(15,0));
    CCMoveBy*moveLeft=CCMoveBy::create(.01, ccp(-30,0));
    CCFiniteTimeAction*seq=CCSequence::create(delay, moveRight,moveLeft,moveRight);
    CCRepeatForever*repeat=CCRepeatForever::create((CCSequence *)seq);
    sadako->runAction(repeat);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

HelloWorld::~HelloWorld(){
    CC_SAFE_RELEASE(_uniformSprites);
}

void HelloWorld::addStaticTVEffectToSprite(CCSprite * spr){

    assert(spr);
    CCString * s=CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("StaticTV.fsh"));
    
    const GLchar *  fragmentSource = (GLchar*) s->getCString();
  
    CCGLProgram * program= new CCGLProgram;
    if (program){
        program->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, fragmentSource);
        
        spr->setShaderProgram(program);
        program->release();
        
        program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        program->link();
        program->updateUniforms();
        
        // 3
        _timeUniformLocation = glGetUniformLocation(program->getProgram(), "u_time");
        // 4
        scheduleUpdate();
        // 5
        program->use();
        _uniformSprites->addObject(spr);
    }
   
}
void HelloWorld::update(float dt){
    _totalTime += dt;
    CCObject *o;
    CCARRAY_FOREACH(_uniformSprites, o){
        CCSprite * spr=dynamic_cast<CCSprite *>(o);
        if (spr)
            spr->getShaderProgram()->use();
    }
    glUniform1f(_timeUniformLocation, _totalTime);
}

