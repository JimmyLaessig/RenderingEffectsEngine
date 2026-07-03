#ifndef REEF_RENDERING_RENDEROBJECT_HPP
#define REEF_RENDERING_RENDEROBJECT_HPP

#include <Reef/Rendering/IndexedGeometry.hpp>

#include <cstdint>
#include <memory>

namespace Reef::Rendering
{

/*!
 *
 */
class RENDERING_API RenderObject
{
public:
    virtual ~RenderObject() = default;

    /*!
     * \brief Get the unique identifier of the render object
     */
    virtual uint64_t id() const = 0;

    /*!
     * \brief Get the matrix to transform to render object from local to world space
     * \return Returns a const reference to matrix
     */
    virtual const glm::mat4& localToWorldMatrix() const = 0;

    /*!
     * \brief set the matrix to transform to render object from local to world space
     * \param matrix The new local-to-world matrix
     */
    virtual void setLocalToWorldMatrix(const glm::mat4& matrix) = 0;

    /*!
     * \brief Flag indicating whether the render object is currently visible
     * \return True if the render object is visible, false otherwise
     */
    virtual bool isVisible() const = 0;

    /*!
     * \brief Show/hide the render object
     * \param visible True if the render object should be visible, false otherwise
     */
    virtual void setVisible(bool visible) = 0;

    /*!
     * \brief Set the mesh to be used for rendering this object
     * The render object takes ownership of the mesh.
     * \param mesh A shared pointer to the mesh to be used for rendering this object
     */
    virtual void setMesh(std::shared_ptr<const IndexedGeometry> mesh) = 0;

    /*!
     * \brief Get the mesh to be used for rendering this object
     * \return A shared pointer to the mesh of the render object
     */
    virtual std::shared_ptr<const IndexedGeometry> mesh() const = 0;

}; // class RenderObject

} // namespace Reef::Rendering

#endif // !REEF_RENDERING_RENDEROBJECT_HPP
