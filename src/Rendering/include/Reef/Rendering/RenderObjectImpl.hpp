#ifndef REEF_RENDERING_RENDEROBJECTIMPL_HPP
#define REEF_RENDERING_RENDEROBJECTIMPL_HPP

#include <Reef/Rendering/RenderObject.hpp>
#include <atomic>

namespace Reef::Rendering
{

class RenderObjectImpl : public RenderObject
{
public:
    RenderObjectImpl();
    ~RenderObjectImpl() override;

    uint64_t id() const override;

    const glm::mat4& localToWorldMatrix() const override;

    void setLocalToWorldMatrix(const glm::mat4& matrix) override;

    bool isVisible() const override;

    void setVisible(bool visible) override;

    void setMesh(std::shared_ptr<const IndexedGeometry> mesh) override;

    std::shared_ptr<const IndexedGeometry> mesh() const override;

private:

    uint64_t mId{ 0 };
    bool mVisible{ false };
    glm::mat4 mLocalToWorldMatrix{ 1.f };
    std::shared_ptr<const IndexedGeometry> mMesh;

}; // class RenderObjectImpl

} // namespace Reef::Rendering

#endif // REEF_RENDERING_RENDEROBJECTIMPL_HPP
