#include "module.hpp"
#include <ctre.hpp>
#include <fmt/core.h>
#include <spdlog/spdlog.h>


int main(int const argc, char *argv[]) {

	if (test()) fmt::print("Hello There!\n");
	return 0;
}
