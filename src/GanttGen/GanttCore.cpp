#include "GanttCore.h"
#include <functional>

std::vector<GanttTask> GanttCore::createTasks(Project& proj, OPT opt)
{
    std::vector<GanttTask> tasks;
    std::unordered_map<Task*, int> task_start_map = process(proj, opt);
    for (Task*const& task : proj.tasks)
    {
        GanttTask t{ task->name, task_start_map[task], task->duration };
        tasks.push_back(t);
    }
    return tasks;
}

float GanttCore::calc_resource(const std::unordered_set<Task*>& tasks)
{
    return
        std::accumulate(tasks.begin(), tasks.end(), 0.0f,
            [](float a, Task* b) { return a + b->resources; });
}

Task* GanttCore::take_min_res(const std::unordered_set<Task*>& tasks)
{
    return
        *std::min_element(tasks.begin(), tasks.end(),
            [&](Task* a, Task* b)
            {
                return a->resources < b->resources;
            });
}

void GanttCore::validate_proj_resource(Project& proj)
{
    float total_res = 0.0f;
    for (Task* const& task : proj.tasks)
    {
        total_res += task->resources;
        if (task->resources > proj.max_peak_resource)
        {
            throw std::exception(std::string("GanttCore: task " + task->name + " exceeds peak resource").c_str());
        }
    }

    if (total_res > proj.max_resource)
    {
        throw std::exception("GanttCore: total task resource exceeds project limit");
    }
}

std::unordered_set<Task*> filter(std::unordered_set<Task*> tasks, std::function<bool(Task*)> pred)
{
    std::unordered_set<Task*> res;
    for (Task* const& t : tasks)
    {
        if (pred(t))
        {
            res.insert(t);
        }
    }
    return res;
}

std::unordered_map<Task*, int> GanttCore::process(Project& proj, OPT opt)
{
    std::unordered_set<Task*> completed;
    std::unordered_set<Task*> running;
    
    std::unordered_set<Task*> pending;
    for (Task* const& t : proj.tasks)
    {
        pending.insert(t);
    }
    
    validate_proj_resource(proj);

    std::unordered_map<Task*, int> task_start_map;
    int day = 0;
    while (!pending.empty())
    {
        std::unordered_set<Task*> prev_satisfied = filter(pending,
            [&](Task* t)
            {
                return
                    std::all_of(t->previous_tasks.begin(), t->previous_tasks.end(),
                        [&](Task* pt) { return completed.count(pt) > 0; });
            });

        if (prev_satisfied.empty() && running.empty())
            throw std::exception("GanttCore: No task can be started due to dependency cycle, day:" + day);

        std::unordered_set<Task*> time_satisfied = filter(prev_satisfied,
            [&](Task* t)
            {
                return
                    (t->min_start_day == -1 || t->min_start_day <= day) &&
                    (t->max_start_day == -1 || t->max_start_day >= day);
            });

        if (!time_satisfied.empty())
        {
            std::unordered_set<Task*> dep_satisfied = filter(time_satisfied,
                [&](Task* t)
                {
                    return
                        std::none_of(pending.begin(), pending.end(),
                            [&](Task* pt) { return pt->dependent_tasks.count(t); });
                });

            if (opt == OPT::MIN_PEAK_RES)
            {
                if (running.empty() && !dep_satisfied.empty())
                {
                    Task* task = take_min_res(dep_satisfied);
                    pending.erase(task);
                    running.insert(task);
                    task_start_map.insert_or_assign(task, day);
                }
            }
            else if (opt == OPT::MIN_TIME)
            {
                while (
                    !dep_satisfied.empty() &&
                    calc_resource(running) +
                    take_min_res(dep_satisfied)->resources <=
                    proj.max_peak_resource
                    )
                {
                    Task* task = take_min_res(dep_satisfied);
                    pending.erase(task);
                    dep_satisfied.erase(task);
                    running.insert(task);
                    task_start_map.insert_or_assign(task, day);
                }
            }
            else throw std::exception("GanttCore: Unsupported otion");
        }

        for (auto it = running.begin(); it != running.end();)
        {
            if (day >= task_start_map.at(*it) + (*it)->duration - 1)
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
