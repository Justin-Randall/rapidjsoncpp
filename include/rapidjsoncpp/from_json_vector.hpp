// Copyright (c) 2021 Justin Randall / Playscale PTE LTD
// Released under the MIT license. See LICENSE included with this
// source package for details.

#ifndef _INCLUDED_from_json_vector_hpp
#define _INCLUDED_from_json_vector_hpp

#include "rapidjsoncpp/from_json.hpp"
#include "rapidjsoncpp/from_json_sequence.hpp"
#include <vector>

namespace rapidjson
{
	template <typename ValueType>
	void read(const Document & doc, const std::string & key,
	          std::vector<ValueType> & values)
	{
		readSequence<std::vector<ValueType>, ValueType>(doc, key, values);
	}
} // namespace rapidjson

#endif //_INCLUDED_from_json_vector_hpp