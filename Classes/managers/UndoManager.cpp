#include "UndoManager.h"

UndoManager::UndoManager(GameModel* model):_model(model){}

void UndoManager::recordMoveToStack(int playfieldIndex, const CardModel& card, const cocos2d::Vec2& originalPos)
{
	UndoAction action;
	action.type = UndoAction::MOVE_TO_STACK;
	action.cardIndex = playfieldIndex;
	action.cardState = card;
	action.originalPosition = originalPos;

    log("_undoModel:%d", _undoModel.getCount());
	_undoModel.addAction(action);
    log("_undoModel:%d", _undoModel.getCount());
}

void UndoManager::recordPromoteToTop(int stackIndex, const CardModel& card, const cocos2d::Vec2& originalPos) {
	UndoAction action;
	action.type = UndoAction::PROMOTE_TO_TOP;
	action.cardIndex = stackIndex;
	action.cardState = card;
	action.originalPosition = originalPos;

    log("_undoModel:%d", _undoModel.getCount());
	_undoModel.addAction(action);
    log("_undoModel:%d", _undoModel.getCount());
}

bool UndoManager::undo() {
    if (!_undoModel.hasActions()) {
        return false;
    }

    UndoAction action = _undoModel.popLastAction();

    switch (action.type) {
        case UndoAction::MOVE_TO_STACK:
            // 从堆牌区移回主牌区的逆操作
            _model->undoMoveCardToStack(action.cardIndex, action.cardState, action.originalPosition);
            break;

        case UndoAction::PROMOTE_TO_TOP:
            // 从顶部降级的逆操作
            _model->undoPromoteCardToTop(action.cardIndex, action.cardState, action.originalPosition);
            break;
    }

    return true;
}

bool UndoManager::ifUndo() {
    return _undoModel.hasActions();
}


