#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <Reef/Util/Hive.hpp>

using namespace Reef::Util;

class TestObjectBase
{
public:
	size_t mIndex;
};


class TestObjectDerived: public TestObjectBase
{
public:

	std::string mDescription;
};


class Factory : public Hive<TestObjectBase>::Factory
{
public:

	size_t elementByteSize() const override
	{ 
		return sizeof(TestObjectDerived);
	}

	void constructAt(void* address) 
	{ 
		std::construct_at<TestObjectDerived>(reinterpret_cast<TestObjectDerived*>(address));
	}
};

TEST_CASE("Test Hive")
{
	Hive<TestObjectBase> hive(std::make_unique<Factory>());

	CHECK(hive.begin() == hive.end());
	CHECK(hive.size() == 0);
	CHECK(hive.empty());

	SECTION("Test inseration and removal of components")
	{
		std::vector<TestObjectDerived*> components;

		for (size_t i = 0; i < 1000; ++i)
		{
			components.push_back(static_cast<TestObjectDerived*>(hive.emplace()));
			components.back()->mIndex = i;
			components.back()->mDescription = std::string("Description ") + std::to_string(i);
			CHECK(hive.size() == i + 1);
		}

		{
			std::set<TestObjectBase*> visited;
			for (auto c : hive)
			{
				visited.insert(c);
			}
			CHECK(visited.size() == hive.size());

			for (auto c : components)
			{
				CHECK(visited.contains(c));
			}
		}

		std::erase_if(components, [&](auto component)
		{
			if (component->mIndex % 2 == 0)
			{
				hive.erase(component);
				return true;
			}
			return false;
		});

		{
			std::set<TestObjectBase*> visited;
			for (auto c : hive)
			{
				visited.insert(c);
			}
			CHECK(visited.size() == hive.size());

			for (auto c : components)
			{
				CHECK(visited.contains(c));
			}
		}
	}
}
