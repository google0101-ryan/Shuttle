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

const char* Time::GetTimeString(uint64_t baseMS)
{
    using namespace std::chrono;
    static char buf[1024];

    tp_t curEnd = paused ? pauseTime : clock_t::now();
    duration_t elapsed = (curEnd - base) - pausedSeconds;

    auto elapsedMS = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    elapsedMS += milliseconds(baseMS);

    auto secs = duration_cast<seconds>(elapsedMS);
    elapsedMS -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);
    auto hour = duration_cast<hours>(mins);
    mins -= duration_cast<minutes>(hour);
    auto day = duration_cast<days>(hour);
    hour -= duration_cast<hours>(day);
    
    sprintf(buf, "%03ld/%02ld:%02ld:%02ld", day.count(), hour.count(), mins.count(), secs.count());
    return buf;
}

double Time::GetTimeMS()
{
    tp_t curEnd = paused ? pauseTime : clock_t::now();
    duration_t elapsed = (curEnd - base) - pausedSeconds;

    auto elapsedMS = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    double t = elapsedMS.count();

    return t;
}
