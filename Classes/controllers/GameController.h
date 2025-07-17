#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "cocos2d.h"

class GameController {
public:
    // 使用const模型指针初始化
    explicit GameController(GameModel* model);

    // 处理主牌区卡牌点击
    bool handlePlayfieldCardClick(int cardIndex);

    // 处理堆牌区卡牌点击
    bool handleStackCardClick(int cardIndex);

    // 回退功能
    bool handleUndo();

    // 检查当前是否可以回退
    bool emptyUndo();

    // 获取模型引用
    const GameModel* getModel() const { return _model; }

    // 获取回退模型
    UndoManager* getUndoManager() { return &_undoManager; }

private:
    const GameModel* _model;
    UndoManager _undoManager;
};

#endif // GAME_CONTROLLER_H
