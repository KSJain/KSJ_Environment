#pragma once

#include <Arduino.h>

namespace KSJ
{

class IntervalTimer
{
public:
    explicit IntervalTimer(
        uint32_t intervalMs
    )
        : _intervalMs(intervalMs),
          _lastRunMs(0),
          _firstRun(true)
    {
    }

    bool isReady(uint32_t nowMs)
    {
        if (_firstRun)
        {
            _firstRun = false;
            _lastRunMs = nowMs;
            return true;
        }

        if (
            nowMs - _lastRunMs <
            _intervalMs
        )
        {
            return false;
        }

        _lastRunMs = nowMs;
        return true;
    }

    void reset(uint32_t nowMs)
    {
        _lastRunMs = nowMs;
        _firstRun = false;
    }

    void triggerImmediately()
    {
        _firstRun = true;
    }

    void setInterval(
        uint32_t intervalMs
    )
    {
        _intervalMs = intervalMs;
    }

    uint32_t intervalMs() const
    {
        return _intervalMs;
    }

private:
    uint32_t _intervalMs;
    uint32_t _lastRunMs;
    bool _firstRun;
};

}