#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.hpp"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSzie = Director::getInstance()->getVisibleSize();
    
    //加入游戏背景
    auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
    this->addChild(layerColorBG);
    
    //在上方加入游戏分数
    
    auto labTTFCardNumberName =LabelTTF::create("Sunny's分数","HirakakuProN-W6",15);
    labTTFCardNumberName->setPosition(Point(215,visibleSzie.height-30));
    addChild(labTTFCardNumberName);
    
    labTTFCardNumber =LabelTTF::create("0","HirakakuProN-W6",20);
    labTTFCardNumber->setPosition(Point(180+100,visibleSzie.height-30));
    addChild(labTTFCardNumber);
    //加入游戏的手势识别监听事件，进行绑定
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan , this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded , this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //调用生成卡片的方法
    createCardSprite(visibleSzie);
    //调用生成随机数
    autoCreateCardNumber();
    autoCreateCardNumber();
    
    return true;
}


//创建卡片
void HelloWorld::createCardSprite(cocos2d::Size size){
    //求出单元格的宽度和高度
    int lon = (size.width-28)/4;
    
    //4*4的单元格
    for(int j=0;j<4;j++)
    {
        for(int i=0;i<4;i++)
        {
            CardSprite *card = CardSprite::createCardSprite(0,lon,lon,lon*j+165
                                                            , lon*i+size.height/6+20);
            addChild(card);
            
            //添加卡片到二位数组中
            cardArr[j][i] = card;
        }
    }
}



//加入手势识别的事件
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event){
    Point touchPO=touch->getLocation();
    
    fristX=touchPO.x;
    fristY=touchPO.y;
    
    return true ;
    
}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event){
    //获取x轴和y轴的移动范围
     Point touchPO=touch->getLocation();
    
    EndX=fristX-touchPO.x;
    EndY=fristY-touchPO.y;
    
    //判断X轴和Y轴的移动范围，如果X轴的绝对值大于Y轴，则左右移动，否则上下移动
    if(abs(EndX)>abs(EndY)){
        //左右
        if (EndX+5>0) {
            if(doLeft()){
                autoCreateCardNumber();
                doCheckGameOver();
            }
        }else{
            if(doRight()){
                autoCreateCardNumber();
                doCheckGameOver();
            }
        }
    }
    else{
        //上下
        if (EndY+5<0) {
            if(doup()){
                autoCreateCardNumber();
                doCheckGameOver();
            }
        }else{
            if(doDown()){
                autoCreateCardNumber();
                doCheckGameOver();
            }
        }
    }
    
}
//上下左右的方法
bool  HelloWorld::doLeft(){
    bool isdo = false;
    
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++){
            for (int x1=x+1; x1<4; x1++) {
                if(cardArr[x1][y]->getNumber()>0){
                    if(cardArr[x][y]->getNumber()<=0){
                        cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
                        cardArr[x1][y]->setNumber(0);
                        
                        x--;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        
                        //设置分数
                        score+=cardArr[x][y]->getNumber();
                        labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
                        
                        
                        cardArr[x1][y]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool  HelloWorld::doRight(){
    bool isdo = false;
    
    for(int y=0;y<4;y++){
        for(int x=3;x>=0;x--){
            for (int x1=x-1; x1>=0; x1--) {
                if(cardArr[x1][y]->getNumber()>0){
                    if(cardArr[x][y]->getNumber()<=0){
                        cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
                        cardArr[x1][y]->setNumber(0);
                        
                        x++;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        
                        //设置分数
                        score+=cardArr[x][y]->getNumber();
                        labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
                        cardArr[x1][y]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool  HelloWorld::doup(){
    bool isdo = false;
    
    for(int x=0;x<4;x++){
        for(int y=3;y>=0;y--){
            for (int y1=y-1; y1>=0; y1--) {
                if(cardArr[x][y1]->getNumber()>0){
                    if(cardArr[x][y]->getNumber()<=0){
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                        cardArr[x][y1]->setNumber(0);
                        
                        y++;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        
                        //设置分数
                        score+=cardArr[x][y]->getNumber();
                        labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
                        cardArr[x][y1]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool  HelloWorld::doDown(){
    bool isdo = false;
    
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            for (int y1=y+1; y1<4; y1++) {
                if(cardArr[x][y1]->getNumber()>0){
                    if(cardArr[x][y]->getNumber()<=0){
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                        cardArr[x][y1]->setNumber(0);
                        
                        y--;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        
                        //设置分数
                        score+=cardArr[x][y]->getNumber();
                        labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
                        
                        cardArr[x][y1]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}

//自动生成卡片
void HelloWorld::autoCreateCardNumber(){
    int i = CCRANDOM_0_1()*4;
    int j = CCRANDOM_0_1()*4;
    
    //判断是否是已经存在的位置
    if(cardArr[i][j]->getNumber()>0){
        autoCreateCardNumber();
    }else{
        cardArr[i][j]->setNumber(CCRANDOM_0_1()*10<1?4:2);
    }
}

//判断游戏是否还能继续运行下去
void HelloWorld::doCheckGameOver(){
    bool isGameOver = true;
    
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++){
            if(cardArr[x][y]->getNumber()==0||
               (x>0&&cardArr[x][y]->getNumber()==cardArr[x-1][y]->getNumber())||
               (x<3&&cardArr[x][y]->getNumber()==cardArr[x+1][y]->getNumber())||
               (y>0&&cardArr[x][y]->getNumber()==cardArr[x][y-1]->getNumber())||
               (y<3&&cardArr[x][y]->getNumber()==cardArr[x][y+1]->getNumber())){
                isGameOver = false;
                
            }
        }
    }
    if(isGameOver==true){
        Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
    }
}








