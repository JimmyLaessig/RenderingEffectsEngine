#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include <Reef/Util/Visitor.hpp>


TEST_CASE("Test Vistor")
{
	std::variant<std::string, int, float> v;
	
	SECTION("void visitors")
	{
		bool called{ false };


		SECTION("float value")
		{
			v = 1.f;

			Reef::Util::visit(v, Reef::Util::Visitor
				{
					[](auto) { CHECK(false); },
					[&](float f) { CHECK(f == 1.f); called = true; },
				});
		}

		SECTION("int value")
		{
			v = 1;

			Reef::Util::visit(v, Reef::Util::Visitor
				{
					[](auto) { CHECK(false); },
					[&](int i) { CHECK(i == 1); called = true; },
				});
		}

		SECTION("string value")
		{
			v = "abc";

			Reef::Util::visit(v, Reef::Util::Visitor
				{
					[&](const std::string& s) { CHECK(s == "abc"); called = true; },
					[](auto) { CHECK(false); },
				});
		}

		CHECK(called);
	}

	SECTION("Visitor with return value")
	{
		SECTION("float value")
		{
			v = 1.f;

			auto res = Reef::Util::visit(v, Reef::Util::Visitor
				{
					[](auto) { return 0.0f; },
					[&](float f) { return 1.f; },
				});

			CHECK(res == 1.f);
		}

		SECTION("int value")
		{
			v = 1;

			auto res = Reef::Util::visit(v, Reef::Util::Visitor
				{
					[](auto) { return 0.0f; },
					[&](int f) { return 1.f; },
				});

			CHECK(res == 1.f);
		}

		SECTION("string value")
		{
			v = "abc";

			auto res = Reef::Util::visit(v, Reef::Util::Visitor
				{
					[](auto) { return size_t(0); },
					[&](const std::string& s) { return s.size(); },
				});

			CHECK(res == 3u);
		}
	}
}
