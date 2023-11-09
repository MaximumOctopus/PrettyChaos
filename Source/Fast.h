//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
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
}