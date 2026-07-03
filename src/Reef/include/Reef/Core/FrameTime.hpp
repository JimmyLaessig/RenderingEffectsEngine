#ifndef REEF_FRAMETIME_HPP
#define REEF_FRAMETIME_HPP

#include <Reef/Export.hpp>

#include <cstdint>
#include <chrono>


namespace Reef
{

using Timestamp = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds>;

/// Struct encapsulating time information of the current frame
struct REEF_API FrameTime
{
	/// The timestamp of the current frame in nanoseconds
	Timestamp currentFrameTimestamp;

	// The timestamp of the previous frame in nanoseconds
	Timestamp previousFrameTimestamp;

	/// The between the current and the previous frame in seconds
	double deltaTime;
}; // FrameTime

} // namespace Reef

#endif // !REEF_FRAMETIME_HPP
