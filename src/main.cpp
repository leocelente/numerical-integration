#include <algorithm>
#include <array>
#include <numeric>

#include "module.hpp"


int main(int const argc, char *argv[]) {
  constexpr auto start = 0.f;
  constexpr auto end = 5.f;
	constexpr auto dt = 0.1f;
	constexpr auto N = static_cast<int>((end - start) / dt);

  std::array<Step<float>, N> data{};
	std::generate(
	  data.begin(), data.end(), [dt, s = Step<float>{}]() mutable {
		  s.time += dt;
		  return s;
	  });

	auto df = [](auto t) {
		Step<float> delta = { t, { 2.f * t }, { 0.f } };
		return delta;
	};

	integrate(df, data.begin(), data.end(), dt);

	std::for_each(data.begin(), data.end(), [](auto step) {
		step.print();
		fmt::print("\n");
	});


	return 0;
}
