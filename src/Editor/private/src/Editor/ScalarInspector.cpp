#include <Editor/ScalarInspector.hpp>

using namespace Reef;

static bool inspectorsRegistered =
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<bool>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<float>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<double>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<uint8_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<uint16_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<uint32_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<uint64_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<int8_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<int16_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<int32_t>())) &
	PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>(new ScalarInspector<int64_t>()));
