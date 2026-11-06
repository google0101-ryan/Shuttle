#pragma once

#include <chrono>
#include <string>

class Time
{
public:
    void Init(bool up = true);
    void Unpause();

    std::string GetTimeString();
    double GetTimeMS();
    double GetTimeS() { return GetTimeMS() / 1000; }
private:
    using clock_t = std::chrono::steady_clock;
    using tp_t = std::chrono::time_point<clock_t>;
    using duration_t = std::chrono::duration<double>;

    bool paused;
    bool up;
    tp_t base;
    tp_t pauseTime;
    duration_t pausedSeconds;
};