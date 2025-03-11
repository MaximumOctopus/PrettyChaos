//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <cstdint>


namespace Fast
{
    inline int32_t Floor(double fp)
    {
        int32_t i = static_cast<int32_t>(fp);

        return (fp < i) ? (i - 1) : (i);
	}

    // https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b
	inline long double Cos(long double x) noexcept
	{
		constexpr long double tp = 1.0/(2.0 * M_PI);
		x *= tp;
		x -= 0.25 + Floor(x + 0.25);
		x *= 16.0 * (std::abs(x) - 0.5);
//		#if EXTRA_PRECISION
		x += 0.225 * x * (std::abs(x) - 1.0);
//		#endif
		return x;
	}
}