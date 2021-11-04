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
	static const unsigned char uc   = 222;
	static const char          c    = -100;
	static const uint16_t      ui16 = 65000;
	static const int16_t       i16  = -30000;
	static const uint32_t      ui32 = 3000000000;
	static const int32_t       i32  = -2000000000;
	static const uint64_t      ui64 = 100000000000;
	static const int64_t       i64  = -100000000000;
	static const float         f    = 3.1415f;
	static const double        d    = 1.000000000001;
	static bool                b    = true;
	static const char * const  cc   = "this is a string literal";
	static const std::string   ss   = "this is an stl string";

	testPod("unsigned char", cc);
	testPod("char", c);
	testPod("unsigned short", ui16);
	testPod("short", i16);
	testPod("uint32_t", ui32);
	testPod("int32_t", i32);
	testPod("uint64_t", ui64);
	testPod("int64_t", i64);
	testPod("float", f);
	testPod("double", d);
	testPod("bool", b);

	testPod("const char * const", cc);
	testPod("std::string", ss);
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
