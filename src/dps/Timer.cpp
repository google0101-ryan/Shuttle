#include "Timer.h"

#include <string>
#include <sstream>
#include <iomanip>

void Time::Init(bool up)
{
    base = clock_t::now();

    this->up = up;
    paused = true;

    pauseTime = base;
    pausedSeconds = duration_t(0);
}

void Time::Unpause()
{
    pausedSeconds += clock_t::now() - pauseTime;
    paused = false;
}

std::string Time::GetTimeString()
{
    std::stringstream ss;

    tp_t curEnd = paused ? pauseTime : clock_t::now();
    duration_t elapsed = (curEnd - base) - pausedSeconds;

    auto elapsedMS = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    double t = elapsedMS.count();

    int day = t / 86400000;
    t -= (day * 86400000);
    
    int hour = t / 3600000;
    t -= (hour * 3600000);

    int minute = t / 60000;
    t -= (minute * 60000);

    double second = t / 1000;
    
    ss << std::setfill('0') << std::setw(3) << day
        << "/" << std::setw(2) << hour << ":" << std::setw(2) << minute <<
        ":" << std::setw(2) << (int)second;

    return ss.str();
}

double Time::GetTimeMS()
{
    tp_t curEnd = paused ? pauseTime : clock_t::now();
    duration_t elapsed = (curEnd - base) - pausedSeconds;

    auto elapsedMS = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    double t = elapsedMS.count();

    return t;
}
