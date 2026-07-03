//#ifndef ENGINE_RENDERING_POSTPROCESSINGPIPELINE_H_
//#define ENGINE_RENDERING_POSTPROCESSINGPIPELINE_H_
//
////#include <Engine/System.hpp>
//
//#include "ToneMappingTechnique.h"
//#include "GammaCorrectionTechnique.h"
//
//
//
//
//memory>;
// 
//import RenderLib;
//
//namespace Reef
//{
//
//namespace Rendering
//{
//
//struct GBuffer;
//
//
//class PostProcessingPipeline
//{
//public:
//
//	bool init(std::shared_ptr<RenderLib::Context> mContext, 
//			  GBuffer& gBuffer, 
//			  std::shared_ptr<RenderLib::Texture2D> inputTexture, 
//			  uint32_t width, uint32_t height);
//
//	void recordCommandBuffer(RenderLib::CommandQueue& commandQueue);
//
//	std::shared_ptr<RenderLib::Framebuffer> framebuffer();
//
//private:
//
//	/*ToneMapping mToneMapping;
//
//	GammaCorrection mGammaCorrection;*/
//
//	std::shared_ptr<RenderLib::CommandBuffer> mCommandBuffer;
//};
//
//} // namespace Rendering
//
//} // namespace Reef
//
//#endif // !ENGINE_RENDERING_POSTPROCESSINGPIPELINE_H_