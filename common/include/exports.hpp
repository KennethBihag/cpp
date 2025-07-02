#ifndef EXPORTS_HPP
#define EXPORTS_HPP

#ifdef SHARED
#ifdef _WIN32
#ifdef EXP_BUILD
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif // EXP_BUILD
#else
#define COMMON_API
#endif
#else
#define COMMON_API
#endif

#endif