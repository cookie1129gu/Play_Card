#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <configs/LevelConfig.h>
#include <configs/LevelConfigLoader.h>
#include <models/GameModel.h>
#include <controllers/GameController.h>
#include <views/CardView.h>

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    void setupUI();

    void setupGameAreas();

    void initializeCards();
    
    void setupCardEventListeners();
    
    void setupPlayfieldCardEventListeners(CardView* cardView);
    
    void setupStackCardEventListeners(CardView* cardView);

    void onUndoClicked(cocos2d::Ref* sender);

    void animateUndo();

    void test();

    void setupCardEventListenersForCard(CardView* cardView);

    GameModel* _model;
    GameController* _controller;
    std::vector<CardView*> _playfieldCards;
    std::vector<CardView*> _stackCards;

    cocos2d::MenuItemLabel* _undoButton;
};

#endif // __HELLOWORLD_SCENE_H__
