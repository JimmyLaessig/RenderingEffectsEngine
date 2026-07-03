#include "RenderObjectImpl.hpp"

using namespace Reef::Rendering;

RenderObjectImpl::RenderObjectImpl()
{
    static std::atomic<uint64_t> sIdCounter{ 0 };

    mId = sIdCounter.fetch_add(1, std::memory_order_relaxed);
}


uint64_t
RenderObjectImpl::id() const
{
    return mId;
}


const glm::mat4&
RenderObjectImpl::localToWorldMatrix() const
{
    return mLocalToWorldMatrix;
}


void
RenderObjectImpl::setLocalToWorldMatrix(const glm::mat4& matrix)
{
    mLocalToWorldMatrix = matrix;
}


bool
RenderObjectImpl::isVisible() const
{
    return mVisible;
}


void
RenderObjectImpl::setVisible(bool visible)
{
    mVisible = visible;
}


void
RenderObjectImpl::setMesh(std::shared_ptr<const IndexedGeometry> mesh)
{
    mMesh = std::move(mesh);
}


std::shared_ptr<const IndexedGeometry>
RenderObjectImpl::mesh() const
{
    return mMesh;
}
