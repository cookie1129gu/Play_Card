#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H

#include "cocos2d.h"
#include "CardResConfig.h"

USING_NS_CC;

/*
关卡配置类
负责存储从配置文件中读取的关卡数据
*/
class LevelConfig{
public:
	/**
	 * @struct CardConfig
	 * @brief 单张卡牌的配置信息
	*/
	struct CardConfig
	{
		CardResConfig::CardFaceType cardFace; // 卡牌正面类型
		CardResConfig::CardSuitType cardSuit; // 花色类型
		Vec2 position; // 卡牌在场景中的位置
		bool faceUp = true; // 默认正面朝上

		/**
		* @brief 构造函数
		* @param face 正面类型枚举值
		* @param suit 花色类型枚举值
		* @param pos 位置坐标
		* @param up 正面状态
		*/
		CardConfig(CardResConfig::CardFaceType face,
			CardResConfig::CardSuitType suit, 
			const Vec2& pos,
			bool up = true)
			: cardFace(face), cardSuit(suit), position(pos), faceUp(up){ }
	};

	/**
	 * @brief 获取主牌区卡牌配置列表
	 * @return 主牌区卡牌配置向量
	*/
	const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }

	/**
	 * @brief 获取堆牌区卡牌配置列表
	 * @return 堆牌区卡牌配置向量
	*/
	const std::vector<CardConfig>& getStackCards() const { return _stackCards; }

private:
	std::vector<CardConfig> _playfieldCards; // 主牌区卡牌设置
	std::vector<CardConfig> _stackCards; // 堆牌区卡牌设置

	// 禁止默认构造函数，需通过Loader创建实例
	LevelConfig() = default;

	// 允许Loader访问私有构造
	friend class LevelConfigLoader;
};

#endif

