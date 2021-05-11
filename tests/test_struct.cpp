// Copyright (c) 2020 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#include "rapidjsoncpp/from_json.hpp"
#include "rapidjsoncpp/from_json_map.hpp"
#include "rapidjsoncpp/from_json_set.hpp"
#include "rapidjsoncpp/to_json.hpp"
#include "rapidjsoncpp/to_json_map.hpp"
#include "rapidjsoncpp/to_json_set.hpp"
#include "gtest/gtest.h"
#include <map>
#include <string>

struct SimpleStruct {
	SimpleStruct(){};
	SimpleStruct(const std::string & name, unsigned short age)
	    : _name(name)
	    , _age(age)
	    , _friends()
	{
	}

	const bool operator==(const SimpleStruct & rhs) const
	{
		if (_name != rhs._name)
			return false;
		if (_age != rhs._age)
			return false;
		for (const auto f : _friends) {
			if (rhs._friends.count(f) == 0)
				return false;
		}
		return true;
	}

	const bool operator!=(const SimpleStruct & rhs) const
	{
		return !(rhs == *this);
	}

	void addFriend(SimpleStruct & f)
	{
		_friends.insert(f._name);
		const auto i = f._friends.find(_name);

		if (i == f._friends.end()) {
			f.addFriend(f);
		}
	}

	std::string           _name;
	unsigned short        _age;
	std::set<std::string> _friends;
};

namespace rapidjson
{
	template <typename WriterType>
	void write(WriterType & w, const SimpleStruct & source)
	{
		w.StartObject();
		write(w, "_name", source._name);
		write(w, "_age", source._age);
		write(w, "_friends", source._friends);
		w.EndObject();
	}

	void read(const Value & v, SimpleStruct & target)
	{
		read(v, "_name", target._name);
		read(v, "_age", target._age);
		read(v, "_friends", target._friends);
	}

} // namespace rapidjson
TEST(jsonobject, VerifySeralizationSimpleStruct)
{
	SimpleStruct alice("alice", 22);
	SimpleStruct bob("bob", 24);
	SimpleStruct charlie("charlie", 26);
	SimpleStruct dianne("dianne", 28);

	alice.addFriend(dianne);
	alice.addFriend(bob);

	charlie.addFriend(bob);

	const auto aliceJson = rapidjson::to_json(alice);

	SimpleStruct aliceDupe;
	EXPECT_NE(alice, aliceDupe);

	rapidjson::from_json(aliceJson, aliceDupe);
	EXPECT_EQ(alice, aliceDupe);

	std::map<std::string, SimpleStruct> people{{"alice", alice},
	                                           {"bob", bob},
	                                           {"charlie", charlie},
	                                           {"dianne", dianne}};
	const auto                          peopleJson = rapidjson::to_json(people);

	std::map<std::string, SimpleStruct> deserializedPeople;
	rapidjson::from_json(peopleJson, deserializedPeople);
	const auto & deserializedAlice = deserializedPeople["alice"];
	EXPECT_EQ(deserializedAlice, alice);
}
