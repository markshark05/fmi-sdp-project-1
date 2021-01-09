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

    std::vector<GanttTask> createTasks(Project& proj, OPT opt)
    {
        std::vector<GanttTask> tasks;
        std::unordered_map<Task*, int> task_start_map = process(proj, opt);
        for (auto& t_s : task_start_map)
        {
            Task* task = t_s.first;
            int start = t_s.second;

            GanttTask t{ task->name, start, task->duration };
            tasks.push_back(t);
        }
        return tasks;
    }

    int calc_resource(const std::unordered_set<Task*>& running)
    {
        return
            std::accumulate(running.begin(), running.end(), 0,
                [](Task* a, Task* b) { return a->resources + b->resources; });
    }

    std::unordered_map<Task*, int> process(Project& proj, OPT opt)
    {
        std::unordered_map<Task*, int> task_start_map;

        std::unordered_set<Task*> completed;
        std::unordered_set<Task*> running;
        std::unordered_set<Task*> pending;

        int day = 0;
        while (!pending.empty())
        {
            std::unordered_set<Task*> prev_satisfied;
            std::copy_if(pending.begin(), pending.end(), prev_satisfied,
                [&](Task* t)
                {
                    return
                        std::all_of(t->previous_tasks.begin(), t->previous_tasks.end(),
                            [&](Task* pt) { return completed.count(pt); });
                });

            if (prev_satisfied.empty())
                throw std::exception("No task can be started due to dependency cycle, day:" + day);

            std::unordered_set<Task*> time_satisfied;
            std::copy_if(prev_satisfied.begin(), prev_satisfied.end(), time_satisfied,
                [&](Task* t)
                {
                    return
                        (t->min_start_day == -1 || t->min_start_day >= day) &&
                        (t->max_start_day == -1 || t->max_start_day <= day);
                });

            if (!time_satisfied.empty())
            {
                std::unordered_set<Task*> dep_satisfied;
                std::copy_if(time_satisfied.begin(), time_satisfied.end(), dep_satisfied,
                    [&](Task* t)
                    {
                        return std::none_of(pending.begin(), pending.end(),
                            [&](Task* pt) { return pt->dependent_tasks.count(t); });
                    });

                if (opt == OPT::MIN_PEAK_RES)
                {
                    if (running.empty())
                    {
                        if (!dep_satisfied.empty())
                        {
                            Task* first = *dep_satisfied.begin();
                            pending.erase(first);
                            running.insert(first);
                            task_start_map.insert_or_assign(first, day);
                        }
                    }
                }
                else if (opt == OPT::MIN_TIME)
                {
                    float currentResources = calc_resource(running);
                    while (currentResources <= proj.max_peak_resource)
                    {
                        //...
                    }
                }
                else throw std::exception("Unsupported otion");
            }

            for (auto it = running.begin(); it != running.end();)
            {
                if (task_start_map.at(*it) + (*it)->duration >= day - 1)
                {
                    completed.insert(*it);
                    it = running.erase(it);
                }
                else it++;
            }

            day++;
        }

        return task_start_map;
    }
};
