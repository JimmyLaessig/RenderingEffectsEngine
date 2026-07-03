#include <Editor/Inspector.hpp>

#include <Engine/Core/Singleton.hpp>

#include <unordered_map>

using namespace Reef;


class Inspectors : public Singleton<Inspectors>
{
public:

	PropertyInspector* findInspector(const Type& type)
	{
		for (auto t = &type; t != nullptr; t = t->parent())
		{
			auto iter = mRegisteredInspectors.find(type);
			if (iter != mRegisteredInspectors.end())
			{
				return iter->second.get();
			}
		}

		return nullptr;
	}

	bool registerInspector(std::unique_ptr<PropertyInspector>&& inspector)
	{
		return mRegisteredInspectors.emplace(inspector->inspectedType(), std::forward<std::unique_ptr<PropertyInspector>&&>(inspector)).second;
	}

private:

	std::unordered_map<Type, std::unique_ptr<PropertyInspector>> mRegisteredInspectors;
};


PropertyInspector*
PropertyInspector::findInspector(const Type& type)
{
	return Inspectors::instance().findInspector(type);
}


bool
PropertyInspector::registerInspector(std::unique_ptr<PropertyInspector>&& inspector)
{
	return Inspectors::instance().Inspectors::registerInspector(std::forward<std::unique_ptr<PropertyInspector>&&>(inspector));
}
