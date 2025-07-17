#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include "CardModel.h"

struct UndoAction {
    enum ActionType {
        MOVE_TO_STACK,
        PROMOTE_TO_TOP
    };

    ActionType type;
    int cardIndex; // 操作的卡牌索引
    CardModel cardState; // 卡牌状态
    cocos2d::Vec2 originalPosition; // 原始位置

    UndoAction()
        : type(MOVE_TO_STACK),
        cardIndex(-1),
        cardState(CardResConfig::CFT_NONE, CardResConfig::CST_NONE),
        originalPosition(cocos2d::Vec2::ZERO) {
    }
};

class UndoModel {
public:
    void addAction(const UndoAction& action);
    bool hasActions() const;
    UndoAction popLastAction();
    void clear();

    // 获得现有行动数
    int getCount();

    // 查看最后一个操作但不移除
    const UndoAction& peekLastAction() const {
        CCASSERT(!_actions.empty(), "No actions to peek");
        return _actions.back();
    }

private:
    std::vector<UndoAction> _actions;
};

#endif 
