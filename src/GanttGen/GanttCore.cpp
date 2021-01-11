#include "GanttCore.h"
#include <functional>

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

GanttCore::TaskManager::TaskManager(const std::vector<Task*>& tasks) :
    day(0)
{
    for (Task* const& t : tasks)
    {
        pending.insert(t);
    }
}

void GanttCore::TaskManager::moveDay()
{
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

void GanttCore::TaskManager::start(Task* task)
{
    pending.erase(task);
    running.insert(task);
    task_start_map.insert_or_assign(task, day);
}

std::unordered_set<Task*> GanttCore::TaskManager::getAvailable()
{
    std::unordered_set<Task*> filtered;

    // check if any task has passed it's max start day
    if (std::any_of(pending.begin(), pending.end(),
        [&](Task* t) { return t->max_start_day > day; }))
    {
        throw std::runtime_error("GanttCore: impossible max_start_day detected on day:" + day);
    }

    // filter by previous_tasks
    filtered = filter(pending,
        [&](Task* t)
        {
            return
                std::all_of(t->previous_tasks.begin(), t->previous_tasks.end(),
                    [&](Task* pt) { return completed.count(pt) > 0; });
        });

    // check for cycles
    if (filtered.empty() && running.empty())
        throw std::runtime_error("GanttCore: Dependency cycle detected on day:" + day);

    // filter by min/max_start_day
    filtered = filter(filtered,
        [&](Task* t)
        {
            return
                (t->min_start_day == -1 || t->min_start_day <= day) &&
                (t->max_start_day == -1 || t->max_start_day >= day);
        });

    // filter by dependent_tasks
    filtered = filter(filtered,
        [&](Task* t)
        {
            return
                std::none_of(pending.begin(), pending.end(),
                    [&](Task* pt) { return pt->dependent_tasks.count(t); });
        });

    return filtered;
}

std::vector<GanttTask> GanttCore::createTasks(Project& proj, OPT opt)
{
    std::vector<GanttTask> tasks;
    std::unordered_map<Task*, int> task_start_map = process(proj, opt);
    for (Task* const& task : proj.tasks)
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

Task* GanttCore::take_best(const std::unordered_set<Task*>& tasks)
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
            throw std::runtime_error("GanttCore: task " + task->name + " exceeds peak resource");
        }
    }

    if (total_res > proj.max_resource)
    {
        throw std::runtime_error("GanttCore: total task resource exceeds project limit");
    }
}

std::unordered_map<Task*, int> GanttCore::process(Project& proj, OPT opt)
{
    validate_proj_resource(proj);

    TaskManager manager{ proj.tasks };

    while (!manager.pending.empty())
    {
        std::unordered_set<Task*> availableTasks = manager.getAvailable();

        if (!availableTasks.empty())
        {
            if (opt == OPT::MIN_PEAK_RES)
            {
                if (manager.running.empty() && !availableTasks.empty())
                {
                    Task* task = take_best(availableTasks);
                    manager.start(task);
                }
            }
            else if (opt == OPT::MIN_TIME)
            {
                while (
                    !availableTasks.empty() &&
                    (calc_resource(manager.running) +
                        take_best(availableTasks)->resources <=
                        proj.max_peak_resource))
                {
                    Task* task = take_best(availableTasks);
                    manager.start(task);

                    availableTasks = manager.getAvailable();
                }
            }
            else throw std::runtime_error("GanttCore: Unsupported otion");
        }

        manager.moveDay();
    }

    return manager.task_start_map;
}
