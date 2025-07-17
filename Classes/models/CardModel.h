#ifndef CARD_MODEL_H
#define CARD_MODEL_H

#include "configs/CardResConfig.h"

class CardModel
{
public:
	// 构造函数
	CardModel(CardResConfig::CardFaceType face, CardResConfig::CardSuitType suit, bool faceUp = true)
	:_face(face), _suit(suit), _faceUp(faceUp), _selected(false) { }

	// 获取卡牌值
	CardResConfig::CardFaceType getFace() const { return _face; }

	// 设置卡牌值
	void setFace(CardResConfig::CardFaceType face) { _face = face; }

	// 获取花色
	CardResConfig::CardSuitType getSuit() const { return _suit; }

	// 设置花色
	void setSuit(CardResConfig::CardSuitType suit) { _suit = suit; }

	// 是否正面朝上
	bool isFaceUp() const { return _faceUp; }

	// 设置正面朝上状态
	void setFaceUp(bool faceUp) { _faceUp = faceUp; }

	// 是否被选中
	bool isSelected() const { return _selected; }

	// 设置选中状态
	void setSelected(bool selected) { _selected = selected; }

	// 卡牌是否可移动
	bool isMovable() const { return _movable; }

	// 设置可移动状态
	void setMovable(bool movable) { _movable = movable; }

	// 卡牌是否在牌堆中
	bool isInPile() const { return _inPile; }

	// 设置牌堆状态
	void setInPile(bool inPile) { _inPile = inPile; }

	// 卡牌是否可被选择
	bool isSelectable() const { return _selectable; }

	// 设置可选择状态
	void setSelectable(bool selectable) { _selectable = selectable; }

	// 获取卡牌唯一ID
	int getCardId() const { return _cardId; }

	// 获取卡牌位置
	const Vec2& getPosition() const { return _position; }

	// 设置卡牌位置
	void setPosition(const Vec2& pos) { _position = pos; }

	~CardModel() {};

private:
	CardResConfig::CardFaceType _face; // 卡牌值
	CardResConfig::CardSuitType _suit; // 花色
	bool _faceUp; // 是否正面朝上
	bool _selected; // 是否被选中
	bool _movable = true; // 是否可移动
	bool _inPile = false; // 是否在牌堆中
	bool _selectable = true; // 是否可被选择
	Vec2 _position = Vec2::ZERO; // 卡牌位置

	// 卡牌唯一标识符
	int _cardId = -1;
};

#endif // !CARD_MODEL_H
