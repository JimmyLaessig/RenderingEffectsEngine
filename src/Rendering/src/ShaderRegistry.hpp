#ifndef REEF_RENDERING_SHADERMANAGER_HPP
#define REEF_RENDERING_SHADERMANAGER_HPP

#include <Coral/Util/RAII.hpp>

#include <slang.h>

#include <string_view>

namespace Reef::Rendering
{
class Renderer;

template<typename T>
struct SlangDeleter
{
    void operator()(T* obj)
    {
        obj->release();
    }
};

template<typename T>
using SlangPtr = std::unique_ptr<T, SlangDeleter<T>>;

/*!
 *
 */
class ShaderManager
{
public:

    ShaderManager(Renderer& renderer);

	void registerModule(std::string_view name, std::span<const uint8_t> slangSource);

    void registerShader(std::string_view name, std::span<const uint8_t> slangSource);

private:

    SlangPtr<slang::IGlobalSession> mGlobalSession;
    SlangPtr<slang::ISession> mSession;

}; // class ShaderManager

} // namespace Reef::Rendering

#endif // !REEF_RENDERING_SHADERMANAGER_HPP
