#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H

#include "LevelConfig.h"
#include "cocos2d.h"
#include "rapidjson/document.h"


class LevelConfigLoader {
public:
    /**
     * @brief 加载关卡配置文件
     * @param filename JSON文件名（位于res目录下）
     * @return 解析后的LevelConfig实例，失败返回nullptr
     */
    static LevelConfig* loadConfig(const std::string& filename);

private:
    /**
     * @brief 解析卡牌配置数据
     * @param doc JSON文档对象
     * @param config 目标LevelConfig实例
     * @return 是否解析成功
     */
    static bool parseCardConfigs(const rapidjson::Value& doc, LevelConfig* config);

    // 解析卡牌数组
    static bool parseCardArray(const rapidjson::Value& array, 
        std::vector<LevelConfig::CardConfig>& outCards);

    // 解析单张卡牌
    static LevelConfig::CardConfig parseSingleCard(const rapidjson::Value& item);

    /**
     * @brief 禁止构造函数（静态工具类）
     */
    LevelConfigLoader() = delete;
};

#endif
