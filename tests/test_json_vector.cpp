// Copyright (c) 2021 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json_vector.hpp"
#include "rapidjsoncpp/to_json_vector.hpp"
#include "gtest/gtest.h"

TEST(jsonpod, VerifySeralizationVector)
{
	const std::vector<int> numbers = {0, 1, 2, 3, 4, 5};

	const std::string json = rapidjson::to_json("std::vector<int>", numbers);

	std::vector<int> results;
	rapidjson::from_json(json, "std::vector<int>", results);

	EXPECT_EQ(numbers, results);

	results.clear();

	rapidjson::from_json(json, "this should not exist", results);
	EXPECT_NE(numbers, results);
}
