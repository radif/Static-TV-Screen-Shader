#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
    int _timeUniformLocation;
    float _totalTime;
    cocos2d::CCArray * _uniformSprites;
    void addStaticTVEffectToSprite(cocos2d::CCSprite * spr);
    virtual void update(float dt);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
protected:
    virtual ~HelloWorld();
};

#endif // __HELLOWORLD_SCENE_H__
