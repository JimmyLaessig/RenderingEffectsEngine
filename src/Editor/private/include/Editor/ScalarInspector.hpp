#ifndef REEF_EDITOR_SCALARINSPECTOR_H
#define REEF_EDITOR_SCALARINSPECTOR_H

#include <Editor/Inspector.hpp>

namespace Reef
{

template<typename Scalar>
class EDITOR_API ScalarInspector : public PropertyInspectorBase<Scalar>
{
protected:

	void inspect(const Property& property, Scalar& value) override
	{
		ImGuiDataType dataType = ImGuiDataType_S64;

		if constexpr (std::same_as<Scalar, bool>)
		{
			if (ImGui::Checkbox(property.name().c_str(), &value))
			{

			}

			return;
		}

		else if constexpr (std::same_as<Scalar, uint8_t>)
		{
			dataType = ImGuiDataType_U8;
		}
		else if constexpr (std::same_as<Scalar, uint16_t>)
		{
			dataType = ImGuiDataType_U16;
		}
		else if constexpr (std::same_as<Scalar, uint32_t>)
		{
			dataType = ImGuiDataType_U32;
		}
		else if constexpr (std::same_as<Scalar, uint64_t>)
		{
			dataType = ImGuiDataType_U64;
		}
		else if constexpr (std::same_as<Scalar, int8_t>)
		{
			dataType = ImGuiDataType_S8;
		}
		else if constexpr (std::same_as<Scalar, int16_t>)
		{
			dataType = ImGuiDataType_S16;
		}
		else if constexpr (std::same_as<Scalar, int32_t>)
		{
			dataType = ImGuiDataType_S32;
		}
		else if constexpr (std::same_as<Scalar, int64_t>)
		{
			dataType = ImGuiDataType_S64;
		}
		else if constexpr (std::same_as<Scalar, float>)
		{
			dataType = ImGuiDataType_Float;
		}
		else if constexpr (std::same_as<Scalar, double>)
		{
			dataType = ImGuiDataType_Double;
		}
		else
		{
			static_assert(false);
		}

		if (ImGui::InputScalar(property.name().c_str(), dataType, &value))
		{

		}
	}
};

} // namespace Reef

#endif // !REEF_EDITOR_SCALARINSPECTOR_H
