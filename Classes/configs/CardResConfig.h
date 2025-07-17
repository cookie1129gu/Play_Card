// 卡牌ui资源配置类
#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include "cocos2d.h"

USING_NS_CC;

class CardResConfig {
public:
	// 花色类型
	enum CardSuitType
	{
		CST_NONE = -1,
		CST_CLUBS,      // 梅花
		CST_DIAMONDS,   // 方块
		CST_HEARTS,     // 红桃
		CST_SPADES,     // 黑桃
		CST_NUM_CARD_SUIT_TYPES
	};

	// 正面类型
	enum CardFaceType
	{
		CFT_NONE = -1,
		CFT_ACE,
		CFT_TWO,
		CFT_THREE,
		CFT_FOUR,
		CFT_FIVE,
		CFT_SIX,
		CFT_SEVEN,
		CFT_EIGHT,
		CFT_NINE,
		CFT_TEN,
		CFT_JACK,
		CFT_QUEEN,
		CFT_KING,
		CFT_NUM_CARD_FACE_TYPES
	};

	// 获取花色资源路径
	static std::string getSuitResource(CardSuitType suit) {
		std::string path = "res/suits/";
		
		switch (suit) {
			case CST_CLUBS: return path + "club.png";
			case CST_DIAMONDS: return path + "diamond.png";
			case CST_HEARTS:   return path + "heart.png";
			case CST_SPADES:   return path + "spade.png";
			default:     return "";
		}
	}

	// 获取花色颜色
	static Color3B getSuitColor(CardSuitType suit) {
		return (suit == CST_DIAMONDS || suit == CST_HEARTS) ? Color3B::RED : Color3B::BLACK;
	}

	// 获取大数值图片资源路径
	static std::string getBigNumberResource(CardFaceType face, CardSuitType suit) {
		std::string color = (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
		return "res/number/big_" + color + "_" + faceToString(face) + ".png";
	}
	// 获取小数值图片资源路径
	static std::string getSmallNumberResource(CardFaceType face, CardSuitType suit) {
		std::string color = (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
		return "res/number/small_" + color + "_" + faceToString(face) + ".png";
	}
	// 获取卡牌背景图片资源路径
	static std::string getCardBackgroundResource() {
		return "res/card_general.png";
	}

private:
	// 将卡牌值转换为字符串表示
	static std::string faceToString(CardFaceType face) {
		switch (face) {
			case CFT_ACE:   return "A";
			case CFT_JACK:  return "J";
			case CFT_QUEEN: return "Q";
			case CFT_KING:  return "K";
			default: {
				// 处理数字牌（2-10）
				int value = static_cast<int>(face) + 1; // CFT_TWO对应2，以此类推
				if (value >= 2 && value <= 10) {
					return std::to_string(value);
				}
				return ""; // 未知情况默认返回空字符串
			}
		}
	}

};

#endif
