// Copyright (c) 2020 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json_vector.hpp"
#include "rapidjsoncpp/to_json_vector.hpp"
#include "gtest/gtest.h"

TEST(jsoncontainers, VerifySeralizationNamedVector)
{
	const std::vector<int> numbers = {0, 1, 2, 3, 4, 5};

	const std::string json = rapidjson::to_json("numbers", numbers);

	std::vector<int> results;
	rapidjson::from_json(json, "numbers", results);

	EXPECT_EQ(numbers, results);

	results.clear();

	rapidjson::from_json(json, "this should not exist", results);
	EXPECT_NE(numbers, results);
}

TEST(jsoncontainers, VerifySeralizationVector)
{
	const std::vector<int> numbers = {0, 1, 2, 3, 4, 5};

	const std::string json = rapidjson::to_json(numbers);

	std::vector<int> results;
	rapidjson::from_json(json, results);

	EXPECT_EQ(numbers, results);
}

TEST(jsoncontainers, VerifySeralizationVectorReadTwice)
{
	const std::vector<int> numbers = {0, 1, 2, 3, 4, 5};

	const std::string json = rapidjson::to_json(numbers);

	std::vector<int> results;
	rapidjson::from_json(json, results);
	EXPECT_EQ(numbers, results);

	rapidjson::from_json(json, results);
	EXPECT_EQ(numbers, results);
}

TEST(jsoncontainers, VerifySerializationNamedVectorDoesNotExistInNakedVector)
{
	const std::vector<int> numbers = {0, 1, 2, 3, 4, 5};

	const std::string json = rapidjson::to_json(numbers);

	std::vector<int> results;

	rapidjson::from_json(json, "this should not exist", results);
	EXPECT_NE(numbers, results);
}

TEST(jsoncontainers, VerifySerializationVectorNoJson)
{
	std::vector<int>  results;
	const std::string emptyJson;
	rapidjson::from_json(emptyJson, results);
	EXPECT_TRUE(results.empty());

	rapidjson::from_json(emptyJson, "this should not exist", results);
	EXPECT_TRUE(results.empty());
}
