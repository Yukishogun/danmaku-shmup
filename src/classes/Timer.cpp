#include "Timer.h"
#include <SDL.h>

Timer::Timer()
: timePassed(0), deadline(0)
{
}

Timer::~Timer()
{
}

void Timer::update(float timeStep)
{
    timePassed += timeStep*1000.f;
}

void Timer::wait(int interval) {
    timeInterval = interval;
    timePassed = 0;
    deadline = timeInterval;
}

bool Timer::hasPassedDeadline() {
    return timePassed >= deadline;
}

void Timer::repeat()
{
    timePassed = 0;
    deadline = timeInterval;
}


