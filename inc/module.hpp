#ifndef MODULE_HPP
#define MODULE_HPP

#include <algorithm>
#include <array>
#include <execution>
#include <fmt/ranges.h>
#include <functional>
#include <numeric>
#include <string>


template<class T, int N> using State = std::array<T, N>;
template<class T, int N> using View = std::array<T, N>;

template<class T> struct Step {
	State<T, 1> state{};
	View<T, 1> view{};

	void print() {
		fmt::print("{}", fmt::join(state, ","));
		fmt::print(",{}", fmt::join(view, ","));
	}
};

template<class T>
Step<T> operator+(Step<T> const &l, Step<T> const &r) noexcept {
	Step<T> c{};
	std::transform(std::execution::par_unseq,
	  l.state.cbegin(),
	  l.state.cend(),
	  r.state.cbegin(),
	  c.state.begin(),
	  std::plus<T>());
	return c;
}

template<class ForwardIt, class OutputIt, class Function>
void integrate(Function f, ForwardIt first, ForwardIt last, OutputIt o_first) {
	std::accumulate(
	  first, last, Step<float>{}, [&f, &o_first](auto state_prev, auto t) {
		  auto next = state_prev + f(t);
		  *o_first = next;
		  o_first++;
		  return next;
	  });
}


#endif
