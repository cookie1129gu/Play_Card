#include "GameController.h"

USING_NS_CC;

GameController::GameController(GameModel* model)
    : _model(model), _undoManager(model) {
    // 参数校验
    CCASSERT(model != nullptr, "GameModel is null");
}

bool GameController::handlePlayfieldCardClick(int cardIndex) {
    // 1. 参数检查
    if (cardIndex < 0 || cardIndex >= _model->getPlayfieldCardCount()) {
        log("index Invalid: %d", cardIndex);
        return false;
    }

    // 2. 获取顶部牌
    const CardModel* topStackCard = _model->getTopStackCard();
    if (!topStackCard) {
        log("There are no available top cards in the pile area");
        return false;
    }

    // 3. 检查匹配
    const CardModel* card1 = _model->getTopStackCard(); // 原来的顶牌model
    const CardModel& clickedCard = _model->getPlayfieldCard(cardIndex); // 新顶牌model

    log("cardIndex: %d", cardIndex);
    log("clickedCard,Px = %.2f, Py = %.2f", clickedCard.getPosition().x, clickedCard.getPosition().y);

    if (_model->isMatch(clickedCard, *topStackCard)) {
        // 记录操作
        _undoManager.recordMoveToStack(cardIndex, *card1, clickedCard.getPosition());
        // 4. 执行移动（通过模型方法修改状态）
        const_cast<GameModel*>(_model)->moveCardToStack(cardIndex);

        
        return true;
    }

    log("Card is not match: %d and %d",
        static_cast<int>(clickedCard.getFace()),
        static_cast<int>(topStackCard->getFace()));
    return false;
}

bool GameController::handleStackCardClick(int cardIndex) {
    // 1. 参数检查
    if (cardIndex < 0 || cardIndex >= _model->getStackCardCount()) {
        log("stack index Invalid: %d", cardIndex);
        return false;
    }

    // 2. 检查是否已经是顶部牌
    if (cardIndex == _model->getStackCardCount() - 1) {
        log("This card is already the top card");
        return false;
    }

    // 记录操作
    const CardModel* card1 = _model->getTopStackCard(); // 原来的顶牌model
    const CardModel& clickedCard = _model->getStackCard(cardIndex); // 新顶牌model
    _undoManager.recordPromoteToTop(cardIndex, *card1, clickedCard.getPosition());

    // 3. 执行提升操作（通过模型方法修改状态）
    const_cast<GameModel*>(_model)->promoteCardToTop(cardIndex);

    return true;
}

bool GameController::handleUndo()
{
    return _undoManager.undo();
}

bool GameController::emptyUndo() 
{
    return !_undoManager.ifUndo();
}