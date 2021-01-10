#pragma once
#include <algorithm>
#include <numeric>
#include <unordered_map>

#include "Project.h"
#include "GanttTask.h"

class GanttCore
{
public:
    enum class OPT
    {
        MIN_PEAK_RES,
        MIN_TIME,
    };

    static std::vector<GanttTask> createTasks(Project& proj, OPT opt);
private:
    static float calc_resource(const std::unordered_set<Task*>& tasks);
    static Task* take_min_res(const std::unordered_set<Task*>& tasks);
    static void validate_proj_resource(Project& proj);
    static std::unordered_map<Task*, int> process(Project& proj, OPT opt);
};
