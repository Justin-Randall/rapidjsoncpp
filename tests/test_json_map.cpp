// Copyright (c) 2021 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json_map.hpp"
#include "rapidjsoncpp/to_json_map.hpp"
#include "gtest/gtest.h"

TEST(jsonpod, VerifySeralizationMap)
{
	const std::map<int, float> arrayContainer = {
	    {0, 0.1f}, {1, 1.2f}, {2, 2.3f}, {3, 3.4f}, {4, 4.5f}, {5, 5.6f}};

	const std::string arrayJson =
	    rapidjson::to_json("std::map<int, float>", arrayContainer);

	std::map<int, float> arrayResults;
	rapidjson::from_json(arrayJson, "std::map<int, float>", arrayResults);
	EXPECT_EQ(arrayContainer, arrayResults);

	const std::map<std::string, int> container = {{"zero", 0}, {"one", 1},
	                                              {"two", 2},  {"three", 3},
	                                              {"four", 4}, {"five", 5}};

	const std::string json =
	    rapidjson::to_json("std::map<std::string, int>", container);

	std::map<std::string, int> results;
	rapidjson::from_json(json, "std::map<std::string, int>", results);
	EXPECT_EQ(container, results);

	results.clear();

	rapidjson::from_json(json, "this should not exist", results);
	EXPECT_NE(container, results);
}
