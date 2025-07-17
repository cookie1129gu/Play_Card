#pragma once
#ifndef GAME_MODEL_H
#define GAME_MODEL_H
#include <configs/LevelConfig.h>
#include "CardModel.h"

class GameModel {
public:
    // 加载关卡配置
    void loadLevel(const LevelConfig* config);

    // 主牌区操作
    void moveCardToStack(int playfieldIndex);
    const CardModel& getPlayfieldCard(int index) const;
    size_t getPlayfieldCardCount() const;
    const std::vector<CardModel>& getPlayfieldCards() const;

    // 堆牌区操作
    void promoteCardToTop(int stackIndex);
    const CardModel* getTopStackCard() const;
    size_t getStackCardCount() const;
    const std::vector<CardModel>& getStackCards() const;

    // 回退操作
    void undoMoveCardToStack(int originalPlayfieldIndex, const CardModel& card, const cocos2d::Vec2& originalPos);
    void undoPromoteCardToTop(int originalStackIndex, const CardModel& card, const cocos2d::Vec2& originalPos);

    // 游戏规则
    bool isMatch(const CardModel& card1, const CardModel& card2) const;

    const CardModel& getStackCard(size_t index) const {
        return _stackCards.at(index);
    }

    void test();

private:
    std::vector<CardModel> _playfieldCards; // 主牌区卡牌
    std::vector<CardModel> _stackCards;     // 堆牌区卡牌, 顶牌是堆牌区的最后一张

};

#endif // !GAME_MODEL_H
