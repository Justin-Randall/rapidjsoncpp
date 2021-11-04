#include "rapidjsoncpp/from_json_pair.hpp"
#include "rapidjsoncpp/to_json_pair.hpp"
#include "gtest/gtest.h"

TEST(jsoncontainers, VerifySeralizationPair)
{
	const std::pair<int, int> original     = std::make_pair(1, 2);
	const std::string         originalJson = rapidjson::to_json(original);
	std::pair<int, int>       dupe;
	rapidjson::from_json(originalJson, dupe);
	EXPECT_EQ(original, dupe);

	const std::string   jsonNoKey("{\"value\": 2}");
	std::pair<int, int> brokenJson = std::make_pair(0, 0);
	rapidjson::from_json(jsonNoKey, brokenJson);
	EXPECT_NE(original, brokenJson);

	brokenJson.first  = 0;
	brokenJson.second = 0;
	const std::string jsonNoValue("{\"key\": 1}");
	rapidjson::from_json(jsonNoValue, brokenJson);
	EXPECT_NE(original, brokenJson);
}