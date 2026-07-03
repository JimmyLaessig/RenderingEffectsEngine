#ifndef REEF_EDITOR_STRINGINSPECTOR_H

#include <Editor/Inspector.hpp>

#include <string>

namespace Reef
{

class EDITOR_API StringInspector : public PropertyInspectorBase<std::string>
{
protected:

	void inspect(const Property& property, std::string& value) override;

};

} // namespace Reef

#endif // !REEF_EDITOR_STRINGINSPECTOR_H
