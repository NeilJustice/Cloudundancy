#pragma once

#if defined __linux__

#define NOINLINE __attribute__((noinline))
#define ALWAYSINLINE __attribute__((always_inline)) inline

#define LIKELY(condition)   __builtin_expect(static_cast<bool>(condition), 1)
#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)

#elif _WIN32

#define NOINLINE __declspec(noinline)
#define ALWAYSINLINE __forceinline

#endif
