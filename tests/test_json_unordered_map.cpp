// Copyright (c) 2020 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json_unordered_map.hpp"
#include "rapidjsoncpp/to_json_unordered_map.hpp"
#include "gtest/gtest.h"

TEST(jsoncontainers, VerifySeralizationUnorderedNamedMap)
{
	const std::unordered_map<int, float> arrayContainer = {
	    {0, 0.1f}, {1, 1.2f}, {2, 2.3f}, {3, 3.4f}, {4, 4.5f}, {5, 5.6f}};

	const std::string arrayJson =
	    rapidjson::to_json("std::unordered_map<int, float>", arrayContainer);

	std::unordered_map<int, float> arrayResults;
	rapidjson::from_json(arrayJson, "std::unordered_map<int, float>",
	                     arrayResults);

	EXPECT_EQ(arrayContainer, arrayResults);

	const std::unordered_map<std::string, int> container = {
	    {"zero", 0},  {"one", 1},  {"two", 2},
	    {"three", 3}, {"four", 4}, {"five", 5}};

	const std::string json =
	    rapidjson::to_json("std::unordered_map<std::string, int>", container);

	std::unordered_map<std::string, int> results;
	rapidjson::from_json(json, "std::unordered_map<std::string, int>", results);

	EXPECT_EQ(container, results);

	results.clear();
	rapidjson::from_json(json, "this should not exist", results);
	EXPECT_NE(container, results);
}

TEST(jsoncontainers, VerifySeralizationUnorderedNakedMap)
{
	const std::unordered_map<int, float> arrayContainer = {
	    {0, 0.1f}, {1, 1.2f}, {2, 2.3f}, {3, 3.4f}, {4, 4.5f}, {5, 5.6f}};

	const std::string arrayJson = rapidjson::to_json(arrayContainer);

	std::unordered_map<int, float> arrayResults;
	rapidjson::from_json(arrayJson, arrayResults);

	EXPECT_EQ(arrayContainer, arrayResults);

	const std::unordered_map<std::string, int> container = {
	    {"zero", 0},  {"one", 1},  {"two", 2},
	    {"three", 3}, {"four", 4}, {"five", 5}};

	const std::string json = rapidjson::to_json(container);

	std::unordered_map<std::string, int> results;
	rapidjson::from_json(json, results);

	EXPECT_EQ(container, results);
}

TEST(jsoncontainers, VerifySerializationUnorderedMapAsArrayNoJson)
{
	std::unordered_map<int, float> arrayResults;
	const std::string              emptyJson;
	rapidjson::from_json(emptyJson, arrayResults);
	EXPECT_TRUE(arrayResults.empty());

	rapidjson::from_json(emptyJson, "this should not exist", arrayResults);
	EXPECT_TRUE(arrayResults.empty());
}

TEST(jsoncontainers, VerifySerializationUnorderedMapNoJson)
{
	std::unordered_map<int, float> results;
	const std::string              emptyJson;
	rapidjson::from_json(emptyJson, results);
	EXPECT_TRUE(results.empty());

	rapidjson::from_json(emptyJson, "this should not exist", results);
	EXPECT_TRUE(results.empty());
}

TEST(jsoncontainers, VerifySeralizationUnorderedNakedMapReadTwice)
{
	const std::unordered_map<int, float> arrayContainer = {
	    {0, 0.1f}, {1, 1.2f}, {2, 2.3f}, {3, 3.4f}, {4, 4.5f}, {5, 5.6f}};

	const std::string arrayJson = rapidjson::to_json(arrayContainer);

	std::unordered_map<int, float> arrayResults;
	rapidjson::from_json(arrayJson, arrayResults);
	EXPECT_EQ(arrayContainer, arrayResults);

	rapidjson::from_json(arrayJson, arrayResults);
	EXPECT_EQ(arrayContainer, arrayResults);

	const std::unordered_map<std::string, int> container = {
	    {"zero", 0},  {"one", 1},  {"two", 2},
	    {"three", 3}, {"four", 4}, {"five", 5}};

	const std::string json = rapidjson::to_json(container);

	std::unordered_map<std::string, int> results;
	rapidjson::from_json(json, results);
	EXPECT_EQ(container, results);

	rapidjson::from_json(json, results);
	EXPECT_EQ(container, results);
}
