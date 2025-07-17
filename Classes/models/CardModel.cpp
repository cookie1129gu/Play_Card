#include "models/CardModel.h"

CardModel::CardModel(int value, CardResConfig::Suit suit, bool faceUp)
    : _value(value)
    , _suit(suit)
    , _faceUp(faceUp)
    , _selected(false)
    , _movable(true)
    , _inPile(false)
    , _selectable(true)
    , _cardId(-1) {
    // 可以在此处生成唯一ID
}

int CardModel::getValue() const { return _value; }

CardResConfig::Suit CardModel::getSuit() const { return _suit; }

bool CardModel::isFaceUp() const { return _faceUp; }

void CardModel::setFaceUp(bool faceUp) { _faceUp = faceUp; }

bool CardModel::isSelected() const { return _selected; }

void CardModel::setSelected(bool selected) { _selected = selected; }

bool CardModel::isMovable() const { return _movable; }

void CardModel::setMovable(bool movable) { _movable = movable; }

bool CardModel::isInPile() const { return _inPile; }

void CardModel::setInPile(bool inPile) { _inPile = inPile; }

bool CardModel::isSelectable() const { return _selectable; }

void CardModel::setSelectable(bool selectable) { _selectable = selectable; }

int CardModel::getCardId() const { return _cardId; }