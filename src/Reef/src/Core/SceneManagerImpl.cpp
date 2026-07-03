#include "SceneManagerImpl.hpp"

#include "../Platform/ApplicationImpl.hpp"

#include "SceneImpl.hpp"

#include <memory>

using namespace Reef;

SceneManagerImpl::SceneManagerImpl(ApplicationImpl& application)
    : mApplication(application)
{}


SceneManagerImpl::~SceneManagerImpl()
{
}


Scene*
SceneManagerImpl::createScene()
{
    return mScenes.insert(std::make_unique<SceneImpl>(mApplication)).first->get();
}


void
SceneManagerImpl::destroyScene(Scene* scene)
{
    std::erase_if(mScenes, [&](const std::unique_ptr<SceneImpl>& s)
    {
        return s.get() == scene;
    });
}


void
SceneManagerImpl::tick(const FrameTime& frameTime)
{
    for (auto& scene : mScenes)
    {
        scene->tick(frameTime);
    }
}
