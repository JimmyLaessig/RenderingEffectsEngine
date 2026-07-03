#ifndef ENGINE_CORE_FACTORY_HPP
#define ENGINE_CORE_FACTORY_HPP

#include <Engine/System.hpp>

#include <concepts>
#include <memory>

namespace Reef
{

/// Base interface of a factory that can construct a new instance of T with the given args
template<typename T, typename ...Args>
class ENGINE_API IFactory
{
public:
	virtual ~IFactory() = default;

	/// Create a new instance of T
	virtual std::unique_ptr<T> create(Args&&... args) = 0;
};

/// Factory to create an object of type T using the default allocator
template<typename T, typename U, typename ...Args>
requires std::derived_from<T, U>
class ENGINE_API DefaultFactory : public IFactory<U, Args...>
{
public:

	/// Create a new instance of T
	std::unique_ptr<U> create(Args&&... args) override
	{
		return std::unique_ptr<U>(new T(args...));
	}
};

} // namespace Reef

#endif // !ENGINE_CORE_FACTORY_HPP
