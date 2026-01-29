#pragma once
/*
    TEST UTILS
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>

class Timer
{
    bool started;
    bool running;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;

public:
    Timer() : started(false), running(false) {}

    void start()
    {
        start_time = std::chrono::system_clock::now();
        started = true;
        running = true;
    }

    void stop()
    {
        end_time = std::chrono::system_clock::now();
        running = false;
    }

    template <class duration>
    long long time() const
    {
        return std::chrono::duration_cast<duration>(((running) ? std::chrono::system_clock::now() : end_time) - start_time).count();
    }

    long long nanoseconds() const
    {
        return time<std::chrono::nanoseconds>();
    }

    long long milliseconds() const
    {
        return time<std::chrono::milliseconds>();
    }

    long long seconds() const
    {
        return time<std::chrono::seconds>();
    }
};

// Calibrate function for performance tests
long long calibrate(size_t N)
{
    // Calibrate the timer
    int a = 0;
    int b = 1;
    Timer timer;
    timer.start();
    for (int i = 0; i < N; i++)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    timer.stop();
    return timer.nanoseconds();
}

// Overload operator<< for std::vector<T>
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "{";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

// So you can use commas as well as left-shifts to print to an ostream
// (so our __VA_ARGS__ expansion works in NOISY)
template <typename T>
std::ostream &operator,(std::ostream &out, const T &t)
{
    out << t;
    return out;
}

std::vector<void (*)(int)> tests;
void register_test(void (*test)(int))
{
    tests.push_back(test);
}

struct FailedTest
{
};
struct PartialTest
{
    double fraction_earned;
    PartialTest(double fraction_earned) : fraction_earned(fraction_earned) {}
};

#define TEST(name, points_possible)                                                                                                          \
    void _##name();                                                                                                                          \
    void name(int which)                                                                                                                     \
    {                                                                                                                                        \
        std::cout << std::endl                                                                                                               \
                  << "TEST #" << which << "|" << #name << "|" << #points_possible << std::endl;                                              \
        try                                                                                                                                  \
        {                                                                                                                                    \
            _##name();                                                                                                                       \
            std::cout << "RESULT|PASSED|" << #name << "|" << #points_possible << "|" << #points_possible << std::endl;                       \
        }                                                                                                                                    \
        catch (PartialTest pt)                                                                                                               \
        {                                                                                                                                    \
            std::cout << "RESULT|FAILED|" << #name << "|" << #points_possible << "|" << (pt.fraction_earned * points_possible) << std::endl; \
        }                                                                                                                                    \
        catch (FailedTest)                                                                                                                   \
        {                                                                                                                                    \
            std::cout << "RESULT|FAILED|" << #name << "|" << #points_possible << "|" << 0 << std::endl;                                      \
        }                                                                                                                                    \
    }                                                                                                                                        \
    struct name##_registrar                                                                                                                  \
    {                                                                                                                                        \
        name##_registrar() { register_test(name); }                                                                                          \
    } name##_registrar_instance;                                                                                                             \
    void _##name()

#define PARTIAL_CREDIT(fraction_earned) throw PartialTest(fraction_earned);
#define FAIL throw FailedTest();

#define CONCAT_DETAIL(x, y) x##y
#define CONCAT(x, y) CONCAT_DETAIL(x, y)
#define NOISY(obj, method, ...)                                \
    std::cout << #obj << "." << #method << "(", ##__VA_ARGS__; \
    cout << ");" << std::endl;                                 \
    obj.method(__VA_ARGS__);

#define ASSERT(expr, ...)                                                 \
    std::cout << "ASSERT: " << #expr << std::endl;                        \
    if (!(expr))                                                          \
    {                                                                     \
        std::cout << "ERROR: " << #expr << " was false! ", ##__VA_ARGS__; \
        std::cout << std::endl;                                           \
        throw FailedTest();                                               \
    }

#define ASSERT_EQ(expr, val, ...)                                   \
    auto CONCAT(_val, __LINE__) = expr;                             \
    std::cout << "ASSERT: " << #expr << " == " << val << std::endl; \
    if (CONCAT(_val, __LINE__) != val)                              \
    {                                                               \
        std::cout << "ERROR: " << CONCAT(_val, __LINE__)            \
                  << " != " << val << " ",                          \
            ##__VA_ARGS__;                                          \
        std::cout << std::endl;                                     \
        throw FailedTest();                                         \
    }

#define ASSERT_VEQ(obs, exp)                                          \
    ASSERT_EQ(obs.size(), exp.size());                                \
    for (size_t i = 0; i < exp.size(); i++)                           \
    {                                                                 \
        if (obs[i] != exp[i])                                         \
        {                                                             \
            std::cout << "ERROR: mismatch at position " << i << ": "; \
            std::cout << obs[i] << " != " << exp[i] << std::endl;     \
            throw FailedTest();                                       \
        }                                                             \
    }

#define DO_VALGRIND(val_points)

#define TEST_MAIN()                                   \
    int main(int argc, char *argv[])                  \
    {                                                 \
        if (argc < 2 || strcmp("all", argv[1]) == 0)  \
        {                                             \
            for (size_t i = 0; i < tests.size(); i++) \
            {                                         \
                tests[i](i);                          \
            }                                         \
        }                                             \
        else                                          \
        {                                             \
            int which = atoi(argv[1]);                \
            tests[which](which);                      \
        }                                             \
    }

/*
    END TEST UTILS
*/