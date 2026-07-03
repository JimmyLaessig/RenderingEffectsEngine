#ifndef REEF_PLATFORM_COMMANDLINEARGUMENTS_HPP
#define REEF_PLATFORM_COMMANDLINEARGUMENTS_HPP

#include <Reef/Export.hpp>

#include <string_view>

namespace Reef
{

class REEF_API CommandLineArguments
{
public:

	CommandLineArguments() = default;

	CommandLineArguments(size_t argc, char** argv);

	std::string_view get(size_t i) const;

	std::string_view operator[](size_t i) const;

	size_t size() const;

private:

	char** mArgv{ nullptr };

	size_t mArgc{ 0 };

}; // class CommandLineArguments

} // namespace Reef

#endif // !REEF_PLATFORM_COMMANDLINEARGUMENTS_HPP
