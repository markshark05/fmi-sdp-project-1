#include "Task.h"

Task::Task() :
    min_start_day(-1),
    max_start_day(std::numeric_limits<int>::max()),
    duration(0),
    resources(0.0f)
{
}
