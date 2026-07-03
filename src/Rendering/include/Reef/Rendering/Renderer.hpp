 #ifndef REEF_RENDERING_RENDERER_HPP
#define REEF_RENDERING_RENDERER_HPP

#include <Reef/Rendering/Export.hpp>
#include <Reef/Rendering/RenderObject.hpp>

#include <Reef/Util/Camera.hpp>

#include <Coral/Coral.h>

namespace Reef::Rendering
{

struct CameraInfo
{
    Reef::Util::Camera<float> camera;
    glm::mat4 cameraInWorldMatrix{ 1.f };

}; // struct CameraInfo

class RENDERING_API Renderer
{
public:

    /*!
     * \brief Create a new Renderer
     */
    static std::unique_ptr<Renderer> create(void* nativeWindowHandle);

    /*!
     * \brief Destructor
     */
    virtual ~Renderer() = default;

    /*!
     * \brief Create a new render object
     * The lifetime of the render object is bound to the lifetime of the renderer or until the
     * render object is destroyed using destroyRenderObject().
     * \return Returns a pointer to the newly created render object
     */
    virtual RenderObject* createRenderObject() = 0;

    /*!
     * \brief Destroy the render object
     *
     * \param renderObject The render object to be destroyed
     */
    virtual void destroyRenderObject(RenderObject* renderObject) = 0;

    /*!
     * \brief Render the scene using the given camera
     * \param camera The camera to be used for rendering the scene.
     * \param cameraInWorldMatrix The transformation matrix of the camera in world space
     */
    virtual void render(const CameraInfo& camera) = 0;

    /*!
     * \brief Get the Coral context
     * \return Returns a pointer to a handle containing the CoContext object
     */
    virtual CoContext context() = 0;

    /*!
     * \brief Get the Coral context
     * \return Returns a pointer to a handle containing the CoContext object
     */
    virtual const CoContext context() const = 0;

}; // class Renderer

} // namespace Reef::Rendering

#endif // !REEF_RENDERING_RENDERER_HPP
