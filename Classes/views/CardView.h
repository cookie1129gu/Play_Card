#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include "cocos2d.h"
#include "configs/CardResConfig.h"

USING_NS_CC;

// 前置声明
class CardModel;
class CardController;

class CardView : public Sprite {
public:
	// 创建卡牌视图
	static CardView* create(const CardModel* model, const CardController* controller = nullptr);
	
	// 初始化卡牌视图
	bool initWithModel(const CardModel* model, const CardController* controller);

	// 更新视图
	void updateView();

	// 设置新模型
	void setModel(const CardModel* model);

	// 设置控制器
	void setController(CardController* controller);

	// 获取卡牌模型
	//const CardModel* getModel() const { return _model; }
	const CardModel* getModel() const { return _model; }

private:
	// 渲染卡牌正面
	void renderCardFront();

private:
	const CardModel* _model; // 卡牌数据模型
	const CardController* _controller; // 卡牌控制器
};

#endif // CARD_VIEW_H
