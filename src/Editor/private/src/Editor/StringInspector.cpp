#include <Editor/StringInspector.hpp>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

using namespace Reef;

void
StringInspector::inspect(const Reef::Property& property, std::string& value)
{
	if (ImGui::InputText(property.name().c_str(), &value))
	{

	}
}


static bool registered = PropertyInspector::registerInspector(std::unique_ptr<Reef::PropertyInspector>(new StringInspector()));