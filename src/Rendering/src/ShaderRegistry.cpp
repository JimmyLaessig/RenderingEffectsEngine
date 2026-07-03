#include "ShaderRegistry.hpp"

#include "Shaders/Transform_slang.hpp"
#include "Shaders/Camera_slang.hpp"
#include "Shaders/SimpleVertexShader_slang.hpp"
#include "Shaders/SimpleFragmentShader_slang.hpp"

#include <iostream>

using namespace Reef::Rendering;

ShaderManager::ShaderManager(Renderer& renderer)
{
    SlangPtr<slang::IGlobalSession> globalSession;
    slang::createGlobalSession(std::out_ptr(mGlobalSession));

    slang::TargetDesc targetDesc = {};
    targetDesc.format            = SLANG_SPIRV;
    targetDesc.profile           = mGlobalSession->findProfile("spirv_1_5");
    targetDesc.flags             = 0;

    slang::SessionDesc sessionDesc       = {};
    sessionDesc.targets                  = &targetDesc;
    sessionDesc.targetCount              = 1;
    sessionDesc.compilerOptionEntryCount = 0;
    sessionDesc.defaultMatrixLayoutMode  = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR;

    mGlobalSession->createSession(sessionDesc, std::out_ptr(mSession));


    registerModule("Camera", { Shaders::Camera_slang.data(), Shaders::Camera_slang.size() });
    registerModule("Transform", { Shaders::Transform_slang.data(), Shaders::Transform_slang.size() });
}


void
ShaderManager::registerModule(std::string_view name, std::span<const uint8_t> slangSource)
{
    //slang::IModule* slangModule = nullptr;
    //{
    //    SlangPtr<slang::IBlob> diagnosticsBlob;

    //    slangModule = mSession->loadModuleFromSourceString("Shader",
    //        nullptr,
    //        slangSource.c_str(),
    //        std::out_ptr(diagnosticsBlob));

    //    if (!slangModule)
    //    {
    //        if (diagnosticsBlob)
    //        {
    //            std::cerr << diagnosticsBlob->getBufferPointer() << std::endl;
    //        }
    //        return {};
    //    }
    //}
}
