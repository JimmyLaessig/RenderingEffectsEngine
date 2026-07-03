//#ifndef ENGINE_RENDERING_SHADERIMPL_HPP
//#define ENGINE_RENDERING_SHADERIMPL_HPP
//
//#include <Engine/System.hpp>
//
//#include <Engine/Rendering/Shader.hpp>
//
//#include <Coral/Coral.hpp>
//
//#include <string>
//#include <vector>
//#include <span>
//#include <memory>
//
//namespace Reef::Rendering
//{
//
//class ENGINE_API ShaderImpl : public Shader
//{
//public:
//
//	static std::unique_ptr<ShaderImpl> create(std::string_view name, 
//										      std::span<const std::byte> vertexShaderSource, 
//										      std::span<const std::byte> fragmentShaderSource, 
//											  Coral::Context& context);
//
//	const std::string& name() const override;
//
//	Coral::ShaderModule* vertexShader() const;
//
//	Coral::ShaderModule* fragmentShader() const;
//
//	std::vector<Coral::DescriptorBindingDefinition> descriptorBindingDefinitions() const override;
//
//private:
//
//	ShaderImpl() = default;
//
//	std::string mName;
//
//	Coral::ShaderModulePtr mVertexShader;
//
//	Coral::ShaderModulePtr mFragmentShader;
//};
//
//} // namespace Reef::Rendering
//
//#endif // !ENGINE_RENDERING_SHADERIMPL_HPP
