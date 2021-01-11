#pragma once
#include <string>
#include <unordered_set>

/**
 * @brief a POD object representing the task
 */
struct Task
{
    /**
     * @brief Construct a Task object
     * 
     */
    Task();
    std::string name;
    int min_start_day;
    int max_start_day;
    int duration;
    float resources;
    std::unordered_set<Task*> previous_tasks;
    std::unordered_set<Task*> dependent_tasks;
    std::unordered_set<Task*> parallel_tasks;
};
