#ifdef DEBUG

#include <iostream>
#define TRACE(...) std::cerr << "TRACE line: " << __LINE__; \
    if (sizeof...(args) > 0) { std::cerr << ": " << __VA_ARGS__; } \
    std::cerr << std::endl;
#define TRACK(x) std::cerr << "TRACK line: " << __LINE__ << "; " << #x << " is " << x << std::endl;

#else

#define TRACE(...)
#define TRACK(x)

#endif