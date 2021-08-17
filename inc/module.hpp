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
	T time;
	State<T, 1> state{};
	View<T, 1> view{};

	void print() {
		fmt::print("{},", time);
		fmt::print("{}", fmt::join(state, ","));
		fmt::print(",{}", fmt::join(view, ","));
	}
};

template<class T>
Step<T> operator+(Step<T> const &l, Step<T> const &r) noexcept {
	Step<T> c{ r };
	std::transform(std::execution::par_unseq,
	  l.state.cbegin(),
	  l.state.cend(),
	  r.state.cbegin(),
	  c.state.begin(),
	  std::plus<T>());
	return c;
}

template<class T> Step<T> operator*(T a, Step<T> const &r) noexcept {
	auto y = r;
	std::transform(
	  r.state.cbegin(), r.state.cend(), y.state.begin(), [&a](auto s) {
		  return a * s;
	  });
	return y;
}

template<class T> Step<T> operator*(Step<T> const &l, T a) noexcept {
	return a * l;
}


template<class T, class ForwardIt, class Function>
void integrate(Function f, ForwardIt first, ForwardIt last, T const dt) {
	std::accumulate(first,
	  last,
	  Step<T>{},
	  [&f, &dt, i = first](auto prev, auto step) mutable {
		  auto next = prev + dt * f(step);
		  *i++ = next;
		  return next;
	  });
}


#endif
