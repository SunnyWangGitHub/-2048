#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.hpp"
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
    
    //加入手势识别的事件
    virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    //上下左右的方法
    bool doLeft();
    bool doRight();
    bool doup();
    bool doDown();
    //自动卡片的生成
    void autoCreateCardNumber();
    //判断游戏是否还能继续运行下去
    void doCheckGameOver();
private:
    //点击的元素
    int fristX,fristY,EndX,EndY;
    //定义一个二维数组
    CardSprite *cardArr[4][4];
    //创建卡片
    void createCardSprite(cocos2d::Size size);
    
    //整体游戏的分数
    int score;
    //定义显示数据的控件
    cocos2d::LabelTTF *labTTFCardNumber;
    
};

#endif // __HELLOWORLD_SCENE_H__
