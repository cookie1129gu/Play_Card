#include "CardView.h"
#include "models/CardModel.h"
#include "controllers/CardController.h"


// 创建函数
CardView* CardView::create(const CardModel* model, const CardController* controller) {
	CardView* card = new (std::nothrow) CardView();
	if (card && card->initWithModel(model, controller)) {
		card->autorelease();
		return card;
	}
	CC_SAFE_DELETE(card);
	return nullptr;
}

// 初始化函数
bool CardView::initWithModel(const CardModel* model, const CardController* controller) {
	// 保存模型和控制器的引用
	_model = model;
	_controller = controller;

	// 加载卡牌背景
	if (!Sprite::initWithFile(CardResConfig::getCardBackgroundResource())) {
		return false;
	}

	// 设置卡牌初始状态
	updateView();

	return true;
}

// 更新视图函数
void CardView::updateView() {
	// 移除所有子节点（重新渲染）
	this->removeAllChildren();

	if (_model->isFaceUp()) {
		// 正面朝上，显示卡牌内容
		renderCardFront();
	} 
}

// 设置新模型
void CardView::setModel(const CardModel* model) {
	_model = model;
	updateView();
}

// 设置控制器
void CardView::setController(CardController* controller) {
	_controller = controller;
}

// 实现渲染卡牌正面
void CardView::renderCardFront() {
	Size cardSize = getContentSize(); // 卡牌背景大小

	// 左上角小数值
	auto smallValue = Sprite::create(
		CardResConfig::getSmallNumberResource(_model->getFace(), _model->getSuit())
	);
	if (smallValue) {
		smallValue->setPosition(Vec2(
			cardSize.width * 0.166f,
			cardSize.height * 0.833f
		));
		addChild(smallValue);
	}

	// 右上角花色
	auto topSuit = Sprite::create(
		CardResConfig::getSuitResource(_model->getSuit())
	);
	if (topSuit) {
		topSuit->setPosition(Vec2(
			cardSize.width * 0.833f,
			cardSize.height * 0.833f
		));
		addChild(topSuit);
	}

	//中间大数值
	auto bigValue = Sprite::create(
		CardResConfig::getBigNumberResource(_model->getFace(), _model->getSuit())
	);
	if (bigValue) {
		bigValue->setPosition(Vec2(
			cardSize.width * 0.5f,
			cardSize.height * 0.45f
		));
		addChild(bigValue);
	}

	//// 添加阴影效果
	//addShadowEffect();
}
