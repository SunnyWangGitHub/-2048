//
//  CardSprite.hpp
//  TZFE
//
//  Created by 王超 on 2016/10/2.
//
//

#ifndef CardSprite_hpp
#define CardSprite_hpp

#include <cocos2d.h>

class CardSprite:public cocos2d::Sprite{
    //初始化游戏卡片方法
public:
    static CardSprite *createCardSprite(int numbers,int wight,int height,float CardSpriteX,float CardSpriteY);
    virtual bool  init();
    CREATE_FUNC(CardSprite);
    //设置数字
    void setNumber(int num);
    //获取数字
    int getNumber();
    
private:
    //显示在界面的数字
    int number;
    void enemyinit(int numbers,int wight,int height,float CardSpriteX,float CardSpriteY);
    
    //定义显示数字的控件
    cocos2d::LabelTTF *labTTFCardNumber;
    
    //显示的背景
    cocos2d::LayerColor *layerColorBG;
    
};

#endif /* CardSprite_hpp */
