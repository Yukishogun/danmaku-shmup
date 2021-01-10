#pragma once

class Timer {
public:
    Timer();
    ~Timer();

    void update(float timeStep);
    void wait(int ms);
    void repeat();
    bool hasPassedDeadline();

    int timeInterval;

private:
    int deadline;
    float timePassed;
};
