module;

#include <chrono>

module Engine.Time;

using namespace Reef;

Timepoint
Time::now()
{
	auto timepoint = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(timepoint.time_since_epoch()).count();
}
