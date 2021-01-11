#pragma once
#include <algorithm>
#include <numeric>
#include <unordered_map>

#include "Project.h"
#include "GanttTask.h"

/**
 * @brief GanttCore cotnains the core task scheduling  algorithm.\n
 * It takes a reference to a project with tasks and outputs a vector of ordered tasks with their optimal start day.
 */
class GanttCore
{
private:
    /**
     * @brief Private helper struct for managing task statuses
     */
    struct TaskManager
    {
        int day;
        std::unordered_set<Task*> completed;
        std::unordered_set<Task*> running;
        std::unordered_set<Task*> pending;
        std::unordered_map<Task*, int> task_start_map;
        
        TaskManager(const std::vector<Task*>& tasks);

        void moveDay();
        void start(Task* task);
        std::unordered_set<Task*> getAvailable();
    };

public:
    enum class OPT
    {
        MIN_PEAK_RES,
        MIN_TIME,
    };

    /**
     * @brief Returns the vector of tasks with the optimal start time based on opt
     * @param proj The source project
     * @param opt The optimization option
     * @return std::vector<GanttTask>
     */
    static std::vector<GanttTask> createTasks(Project& proj, OPT opt);
private:
    static float calc_resource(const std::unordered_set<Task*>& tasks);
    static Task* take_best(const std::unordered_set<Task*>& tasks);
    static void validate_proj_resource(Project& proj);
    static std::unordered_map<Task*, int> process(Project& proj, OPT opt);
};
