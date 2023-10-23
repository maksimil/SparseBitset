#pragma once

#include "basic.hpp"
#include <chrono>
#include <ratio>

using TimerClock = std::chrono::high_resolution_clock;
using TimerDurationRep = double;
using TimerDurationRatio = std::micro;
using TimerTimePoint = TimerClock::time_point;
using TimerDuration =
    std::chrono::duration<TimerDurationRep, TimerDurationRatio>;

inline TimerTimePoint timer_now() { return TimerClock::now(); }

class Timer {
private:
  TimerTimePoint start_time;

public:
  Timer() { this->start_time = timer_now(); }

  TimerDurationRep elapsed() {
    TimerTimePoint end_time = timer_now();
    TimerDuration duration = end_time - this->start_time;
    return duration.count();
  }
};

class Benchmark {
private:
  TimerDurationRep total_elapsed = 0.0;
  Index count = 0;

  Timer current_timer;

public:
  Benchmark() {}

  void start() { this->current_timer = Timer(); }

  void end() {
    TimerDurationRep elapsed = this->current_timer.elapsed();
    this->count++;
    this->total_elapsed += elapsed;
  }

  TimerDurationRep average() const { return this->total_elapsed / this->count; }
};
