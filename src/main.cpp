#include <algorithm>
#include <array>
#include <numeric>

#include "module.hpp"

int main(int const argc, char *argv[]) {
	std::array<float, 100000> time{};
	std::array<Step<float>, time.size()> data{};
	std::generate(time.begin(), time.end(), [x = 0.f]() { return x + .1f; });


	auto df = [](auto t) {
		Step<float> delta = { { 2.f * t }, { 0.f } };
		return delta;
	};

	integrate(df, time.cbegin(), time.cend(), data.begin());

	std::for_each(data.begin(), data.end(), [](auto step) {
		step.print();
		fmt::print("\n");
	});


	return 0;
}
