#ifndef ENGINE_CORE_VIEWPORT_HPP
#define ENGINE_CORE_VIEWPORT_HPP


#include <glm/glm.hpp>

namespace Reef
{

struct Viewport
{
	// Pixel offset of the viewport
	glm::vec2 offset;

	// Resolution of the viewport in pixel
	glm::uvec2 resolution;
};

} // namespace Reef

#endif //!ENGINE_CORE_VIEWPORT_HPP