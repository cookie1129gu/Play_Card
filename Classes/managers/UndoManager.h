#pragma once
#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "models/UndoModel.h"
#include "models/GameModel.h"

class UndoManager
{
public:
	explicit UndoManager(GameModel* model);
	
	// 记录移动卡牌到堆牌区的操作
	void recordMoveToStack(int playfieldIndex, const CardModel& card, const cocos2d::Vec2& originalPos);

	// 记录提升卡牌到顶部的操作
	void recordPromoteToTop(int stackIndex, const CardModel& card, const cocos2d::Vec2& originalPos);

	// 执行回退操作
	bool undo();

	// 检查是否有动作
	bool ifUndo();

	// 获取最后一个动作
	const UndoAction* getLastAction() const {
		return _undoModel.hasActions() ? &_undoModel.peekLastAction() : nullptr;
	}

private:
	GameModel* _model;
	UndoModel _undoModel;
};

#endif // UNDO_MANAGER_H

