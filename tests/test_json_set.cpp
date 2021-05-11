// Copyright (c) 2020 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json_set.hpp"
#include "rapidjsoncpp/to_json_set.hpp"
#include "gtest/gtest.h"

TEST(jsoncontainers, VerifySeralizationNamedSet)
{
	const std::set<int> numbers = {0, 1, 2, 3, 4, 5};

	const std::string json = rapidjson::to_json("std::set<int>", numbers);

	std::set<int> results;
	rapidjson::from_json(json, "std::set<int>", results);

	EXPECT_EQ(numbers, results);

	results.clear();

	// trigger a failure missing key
	rapidjson::from_json(json, "This should not exist", results);
	EXPECT_NE(numbers, results);
}

TEST(jsoncontainers, VerifySeralizationNakedSet)
{
	const std::set<int> numbers   = {0, 1, 2, 3, 4, 5};
	const std::string   jsonArray = rapidjson::to_json(numbers);
	std::set<int>       results;
	results.clear();
	rapidjson::from_json(jsonArray, results);
	EXPECT_EQ(numbers, results);
}
