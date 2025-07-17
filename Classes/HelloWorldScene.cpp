#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const std::string kLevelConfigPath = "res/level_01.json";

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    if (!Scene::init()) return false;

    // 1. 初始化场景
    setupGameAreas();
    setupUI();

    // 2. 初始化模型和控制器
    _model = new GameModel();
    auto levelConfig = LevelConfigLoader::loadConfig(kLevelConfigPath);
    _model->loadLevel(levelConfig);
    _controller = new GameController(_model);

    // 3. 创建卡牌视图
    initializeCards();

    // 4. 设置事件监听
    setupCardEventListeners();

    return true;
}

void HelloWorld::setupUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto undoLabel = Label::createWithTTF("back", "fonts/Marker Felt.ttf", 90);

    _undoButton = MenuItemLabel::create(undoLabel, CC_CALLBACK_1(HelloWorld::onUndoClicked, this));
#if 1
    _undoButton->setPosition(Vec2(
        origin.x + visibleSize.width - 100,
        origin.y + visibleSize.height - 1700));
#endif
    auto menu = Menu::create(_undoButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void HelloWorld::setupGameAreas() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 主牌区背景
    auto playfield = LayerColor::create(Color4B(170, 121, 66, 255),
        1080, 1500);
    playfield->setPosition(origin.x, origin.y + visibleSize.height - 1500);
    addChild(playfield, 0);

    // 堆牌区背景
    auto stackArea = LayerColor::create(Color4B(148, 33, 146, 255),
        1080, 580);
    stackArea->setPosition(origin);
    addChild(stackArea, 0);
}

void HelloWorld::initializeCards() {
    // 创建主牌区卡牌
    for (size_t i = 0; i < _controller->getModel()->getPlayfieldCardCount(); ++i) {
        auto cardView = CardView::create(&_controller->getModel()->getPlayfieldCard(i), nullptr);
        cardView->setPosition(_controller->getModel()->getPlayfieldCard(i).getPosition());
        _playfieldCards.push_back(cardView);
        addChild(cardView, 1);
    }

    // 创建堆牌区卡牌
    for (size_t i = 0; i < _controller->getModel()->getStackCardCount(); ++i) {
        auto cardView = CardView::create(&_controller->getModel()->getStackCards()[i], nullptr);
        cardView->setPosition(_controller->getModel()->getStackCards()[i].getPosition());
        _stackCards.push_back(cardView);
        addChild(cardView, 1);
    }
}

void HelloWorld::setupCardEventListeners() {
    // 主牌区卡牌事件 - 使用迭代器
    for (auto it = _playfieldCards.begin(); it != _playfieldCards.end(); ++it) {
        auto cardView = *it;

        setupPlayfieldCardEventListeners(cardView);
    }
    
    // 堆牌区卡牌事件
    for (auto it = _stackCards.begin(); it != _stackCards.end(); ++it) {
        log("AAA: _stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());
        auto cardView = *it;

        setupStackCardEventListeners(cardView);
    }
    
}

void HelloWorld::setupPlayfieldCardEventListeners(CardView* cardView) 
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<CardView*>(event->getCurrentTarget());
        return target->getBoundingBox().containsPoint(touch->getLocation());
        };

    listener->onTouchEnded = [this, cardView](Touch* touch, Event* event) {
        // 动态查找卡牌在当前容器中的索引
        auto it = std::find(_playfieldCards.begin(), _playfieldCards.end(), cardView);
        if (it == _playfieldCards.end()) return; // 卡牌已被移除
        size_t index = std::distance(_playfieldCards.begin(), it);

        if (_stackCards.empty()) return;
        auto beforeTopCard = _stackCards.back();
        auto targetPos = beforeTopCard->getPosition();
        
        bool isNext = _controller->handlePlayfieldCardClick(static_cast<int>(index));
        
        
        
        if (isNext) {

            test();

            // 创建新卡牌并执行动画
            auto newCardView = CardView::create(_controller->getModel()->getTopStackCard(), nullptr);
            newCardView->setPosition(cardView->getPosition());
            newCardView->setVisible(false);
            addChild(newCardView, 1);

            newCardView->setVisible(true);
            newCardView->runAction(Sequence::create(
                MoveTo::create(0.3f, targetPos),
                CallFunc::create([this, cardView, newCardView, index]() {
                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    // 查找当前卡牌在容器中的位置
                    auto it = std::find(_playfieldCards.begin(), _playfieldCards.end(), cardView);
                    if (it != _playfieldCards.end()) {
                        _eventDispatcher->removeEventListenersForTarget(cardView);
                        removeChild(cardView);
                        _playfieldCards.erase(it);
                    }

                    // 更新堆牌区
                    if (!_stackCards.empty()) {
                        _stackCards.pop_back();
                    }
                    _stackCards.push_back(newCardView);

                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    CCLOG("Card moved successfully. Stack now has %zu cards", _stackCards.size());
                    }),
                nullptr
            ));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardView);
}

void HelloWorld::setupStackCardEventListeners(CardView* cardView)
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<CardView*>(event->getCurrentTarget());
        return target->getBoundingBox().containsPoint(touch->getLocation());
        };

    listener->onTouchEnded = [this, cardView](Touch* touch, Event* event) {
        // 动态查找卡牌在当前容器中的索引
        auto it = std::find(_stackCards.begin(), _stackCards.end(), cardView);
        if (it == _stackCards.end()) return; // 卡牌已被移除
        size_t index = std::distance(_stackCards.begin(), it);

        if (_stackCards.empty()) return;
        auto beforeTopCard = _stackCards.back();
        auto targetPos = beforeTopCard->getPosition();

        if (_controller->handleStackCardClick(index)) {
            auto newCardView = CardView::create(_controller->getModel()->getTopStackCard(), nullptr);
            newCardView->setPosition(cardView->getPosition());
            newCardView->setVisible(false);
            addChild(newCardView, 1);

            newCardView->setVisible(true);


            newCardView->runAction(Sequence::create(
                MoveTo::create(0.3f, targetPos),
                CallFunc::create([this, cardView, newCardView, index]() {
                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    // 更新堆牌区
                    if (!_stackCards.empty()) {
                        _eventDispatcher->removeEventListenersForTarget(cardView);
                        removeChild(cardView); 
                        _stackCards.pop_back(); // 去掉旧顶牌

                        _stackCards.erase(_stackCards.begin() + index); // 去掉原来的新顶牌
         
                    }
                    _stackCards.push_back(newCardView); // 加入新顶牌

                    log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

                    log("Stacking area card %zu promoted to the top", index);
                    }),
                nullptr
            ));
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardView);
}

void HelloWorld::onUndoClicked(cocos2d::Ref* sender)
{
    log("Undo Click!");
    
    if (!_controller->emptyUndo()) {
        // 执行视图动画
        animateUndo();
    }
    else {
        log("Undo is null");
    }
}

void HelloWorld::animateUndo() {
    // 获取最后一个操作
    const UndoAction& action = *_controller->getUndoManager()->getLastAction();


    // 根据操作类型执行不同的动画
    switch (action.type) {
        case UndoAction::MOVE_TO_STACK: {
            log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

            // 从堆牌区移回主牌区
            auto card1 = _stackCards.back();
            Vec2 pos = card1->getPosition();

            card1->runAction(MoveTo::create(0.3f, action.originalPosition)); // 位移到原来的位置

            _playfieldCards.push_back(card1);
            _stackCards.pop_back();

            // 添加被覆盖的原顶牌
            auto newCardView = CardView::create(&(action.cardState), nullptr);
            newCardView->setPosition(pos);
            _stackCards.push_back(newCardView);

            // 设置触摸监听
            setupPlayfieldCardEventListeners(newCardView);

            addChild(newCardView, 1);
            log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

            break;
        }
        case UndoAction::PROMOTE_TO_TOP: {
            auto card1 = _stackCards.back();

            Vec2 pos = card1->getPosition();

            card1->runAction(MoveTo::create(0.3f, action.originalPosition)); // 位移到原来的位置

            // 添加被覆盖的原顶牌
            auto newCardView = CardView::create(&(action.cardState), nullptr);
            newCardView->setPosition(pos);
            _stackCards.push_back(newCardView);

            // 设置触摸监听
            setupStackCardEventListeners(newCardView);

            addChild(newCardView, 1);
            log("_stackCards.size = %d, _playfieldCards.size = %d", _stackCards.size(), _playfieldCards.size());

            break;
        }
    }

    _controller->handleUndo();
}

void HelloWorld::test() {
    log("_playfieldCards:");
    for (CardModel cardView : _controller->getModel()->getPlayfieldCards()) {
        if (1){
            log("Card Face: %d, Position: (%.2f, %.2f)",
                cardView.getFace(),
                cardView.getPosition().x,
                cardView.getPosition().y);
        }
    }
}