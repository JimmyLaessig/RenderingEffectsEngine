#ifndef REEF_PLATFORM_ENTRYPOINT
#define REEF_PLATFORM_ENTRYPOINT
#include <Reef/Platform/Application.hpp>

namespace Reef
{

extern "C++" void onApplicationCreated(Application& application);

} // namespace Reef


int
main(int argc, char** argv)
{
	Reef::CommandLineArguments arguments(static_cast<size_t>(argc), argv);

	auto app = Reef::createApplication(arguments);
	if (!app)
	{
		return EXIT_FAILURE;
	}

	onApplicationCreated(*app);
	return static_cast<int>(app->run());
}

#endif // !REEF_PLATFORM_ENTRYPOINT
