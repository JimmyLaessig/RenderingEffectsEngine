#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <Reef/Util/TypeName.hpp>

#include <string>

struct MyStruct
{

};

class MyClass
{

};

namespace Namespace1
{
	struct MyStruct1
	{

	};

	class MyClass1
	{

	};

	namespace Namespace2
	{
		struct MyStruct2
		{

		};

		class MyClass2
		{

		};
	};
} 


TEST_CASE("Test typeName")
{
	CHECK(Reef::Util::typeName<MyStruct>() == "MyStruct");
	CHECK(Reef::Util::typeName<Namespace1::MyStruct1>() == "Namespace1::MyStruct1");
	CHECK(Reef::Util::typeName<Namespace1::Namespace2::MyStruct2>() == "Namespace1::Namespace2::MyStruct2");

	CHECK(Reef::Util::typeName<MyClass>() == "MyClass");
	CHECK(Reef::Util::typeName<Namespace1::MyClass1>() == "Namespace1::MyClass1");
	CHECK(Reef::Util::typeName<Namespace1::Namespace2::MyClass2>() == "Namespace1::Namespace2::MyClass2");

	// The typename function does not work with alias types or templated types
	CHECK_FALSE(Reef::Util::typeName<size_t>() == "size_t");

	CHECK(Reef::Util::typeName<std::string>() == "std::string");
}
