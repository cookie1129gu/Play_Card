#include "UndoModel.h"

void UndoModel::addAction(const UndoAction& action) {
    _actions.push_back(action);
}

bool UndoModel::hasActions() const {
    return !_actions.empty();
}

UndoAction UndoModel::popLastAction() {
    if (_actions.empty()) {
        return UndoAction();
    }

    UndoAction action = _actions.back();
    _actions.pop_back();
    return action;
}

void UndoModel::clear() {
    _actions.clear();
}

int UndoModel::getCount()
{
    return _actions.size();
}
