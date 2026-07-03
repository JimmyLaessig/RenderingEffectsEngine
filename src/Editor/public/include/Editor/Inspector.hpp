#ifndef REEF_EDITOR_INSPECTOR_H
#define REEF_EDITOR_INSPECTOR_H

#include <Editor/System.hpp>

#include <Engine/Core/Property.hpp>
#include <Engine/Core/Type.hpp>

#include <imgui.h>

#include <memory>


namespace Reef
{

class EDITOR_API PropertyInspector
{
public:

	virtual Type inspectedType() const = 0;

	virtual void inspect(const Property& property) = 0;

	static PropertyInspector* findInspector(const Type& type);

	static bool registerInspector(std::unique_ptr<PropertyInspector>&& inspector);

};


template<typename T>
concept HasClassType = requires(T t)
{
	{T::classType() }-> std::same_as<const Type&>;
};


template<typename T>
class EDITOR_API PropertyInspectorBase : public PropertyInspector
{
public:

	Type inspectedType() const override
	{
		if constexpr (HasClassType<T>)
		{
			return T::classType();
		}
		else
		{
			return Type::create<T>();
		}
	}

	void inspect(const Property& property) override
	{
		ImGui::PushID(property.value());
		inspect(property, *(T*)property.value());
		ImGui::PopID();
	}

protected:

	virtual void inspect(const Property&, T& value) = 0;

};

} // namespace Reef

#endif // !REEF_EDITOR_INSPECTOR_H
