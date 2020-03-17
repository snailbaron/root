#include "timers.hpp"

#include <cmath>

FrameTimer::FrameTimer(int fps)
    : _delta(1.f / fps)
    , _lastFrame(0)
    , _startTime(Clock::now())
    , _frameDuration(std::chrono::duration_cast<Clock::duration>(
        std::chrono::duration<float>(_delta)))
{ }

float FrameTimer::delta() const
{
    return _delta;
}

int FrameTimer::operator()()
{
    auto currentTime = Clock::now();
    auto currentFrame = (currentTime - _startTime) / _frameDuration;
    auto frameDiff = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
    return static_cast<int>(frameDiff);
}

FrameCounter::FrameCounter(float frameDuration)
    : _frameDuration(frameDuration)
{ }

int FrameCounter::update(float delta)
{
    int framesPassed = static_cast<int>(_remainder + delta);
    _remainder = std::fmod(_remainder + delta, _frameDuration);
    return framesPassed;
}
