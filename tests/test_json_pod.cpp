// Copyright (c) 2020 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json.hpp"
#include "rapidjsoncpp/to_json.hpp"
#include "gtest/gtest.h"

void testPod(const std::string & podTypeName, const char * const literal)
{
	const std::string result = rapidjson::to_json(podTypeName, literal);
	std::string       check;

	rapidjson::from_json(result, podTypeName, check);
	EXPECT_EQ(std::string(literal), check);
}

template <typename ValueType>
void testPod(const std::string & podTypeName, const ValueType podValue)
{
	const std::string result = rapidjson::to_json(podTypeName, podValue);
	ValueType         check;

	rapidjson::from_json(result, podTypeName, check);
	EXPECT_EQ(podValue, check);

	ValueType nonexistent;
	rapidjson::from_json(result, "shold not exist", nonexistent);
	EXPECT_NE(podValue, nonexistent);
}

TEST(jsonpod, VerifySeralizationPlainOldDataTypes)
{
	testPod("unsigned char", unsigned char(222));
	testPod("char", char(-100));
	testPod("unsigned short", uint16_t(65000));
	testPod("short", int16_t(-30000));
	testPod("uint32_t", uint32_t(3000000000));
	testPod("int32_t", int32_t(-2000000000));
	testPod("uint64_t", uint64_t(100000000000));
	testPod("int64_t", int64_t(-100000000000));
	testPod("float", 3.1415f);
	testPod("double", 1.000000000001);
	testPod("bool", true);

	testPod("const char * const", "this is a string literal");
	testPod("std::string", std::string("this is an stl string"));
}

TEST(jsonpod, MultiplePodSerialization)
{
	const std::string json =
	    rapidjson::to_json("one", 1, "two", "two", "three", 3.14f, "four",
	                       4.444444444444, "five", true);

	int         one;
	std::string two;
	float       three;
	double      four;
	bool        five;

	rapidjson::from_json(json, "one", one, "two", two, "three", three, "four",
	                     four, "five", five);

	EXPECT_EQ(one, 1);
	EXPECT_EQ(two, std::string("two"));
	EXPECT_EQ(three, 3.14f); // yes, can be different....
	EXPECT_EQ(four, 4.444444444444);
	EXPECT_EQ(five, true);
}
