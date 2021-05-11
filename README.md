# RapidJSON C++ Helpers

This takes [TenCent's RapidJSON](https://github.com/Tencent/rapidjson) and adds a number of helpers to simplify its usage while adding capabilities for add-hoc serialization.

## Examples

Serializing structs and classes:

```cpp
#include "rapidjsoncpp/from_json.hpp"
#include "rapidjsoncpp/to_json.hpp"
#include <cstdio>

struct SimpleStruct {
    SimpleStruct(){};
    SimpleStruct(const std::string & name, unsigned short age)
      : _name(name)
      , _age(age)
    {
    }
};

namespace rapidjson
{
    template <typename WriterType>
    void write(WriterType & w, const SimpleStruct & source)
    {
        w.StartObject();
        write(w, "_name", source._name);
        write(w, "_age", source._age);
        w.EndObject();
    }

    void read(const Value & v, SimpleStruct & target)
    {
        read(v, "_name", target._name);
        read(v, "_age", target._age);
    }

} // namespace rapidjson

int main(int, char **)
{
    SimpleStruct alice("alice", 22);
    const auto aliceJson = rapidjson::to_json(alice);
    std::cout << aliceJson;

    SimpleStruct aliceDupe;
    rapidjson::from_json(aliceJson, aliceDupe);
    return 0;
}
```

Imagine you are writing a logger that should output json for use with an
[Elastic Stack](https://www.elastic.co/elastic-stack), and want to
construct log entries from an arbitrary number of sources:

```cpp
#include "rapidjsoncpp/from_json.hpp"
#include "rapidjsoncpp/to_json.hpp"
#include <cstdio>

int main(int, char **)
{
    const std::string json =
        rapidjson::to_json("one", 1, "two", "two", "three", 3.14f, "four",
                            4.444444444444, "five", true);

    std::cout << json;
    int         one;
    std::string two;
    float       three;
    double      four;
    bool        five;

    rapidjson::from_json(json, "one", one, "two", two, "three", three, "four",
                            four, "five", five);

    return 0;
}
```

It also works with standard containers:

```cpp
#include "rapidjsoncpp/from_json_vector.hpp"
#include "rapidjsoncpp/to_json_vector.hpp"

int main(int, char **)
{
    const std::vector<int> numbers = {0, 1, 2, 3, 4, 5};
    const std::string json = rapidjson::to_json("std::vector<int>", numbers);

    std::cout << json;
    std::vector<int> results;
    rapidjson::from_json(json, "std::vector<int>", results);

    return 0;
}
```
