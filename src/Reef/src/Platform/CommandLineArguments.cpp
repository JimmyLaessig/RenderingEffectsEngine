#include <Reef/Platform/CommandLineArguments.hpp>

using namespace Reef;


CommandLineArguments::CommandLineArguments(size_t argc, char** argv)
	: mArgv(argv)
	, mArgc(argc)
{
}


std::string_view
CommandLineArguments::get(size_t i) const
{
	return mArgv[i];
}


std::string_view
CommandLineArguments::operator[](size_t i) const
{
	return get(i);
}


size_t
CommandLineArguments::size() const
{
	return mArgc;
}