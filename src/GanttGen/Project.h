#pragma once
#include "XmlDocument.h"
#include "Task.h"

/**
 * @brief Represents a Project containing tasks
 * 
 */
class Project
{
private:
    struct RawTask
    {
        RawTask();
        std::string name;
        int min_start_day;
        int max_start_day;
        int duration;
        float resources;
        std::vector<std::string> previous_tasks;
        std::vector<std::string> dependent_tasks;
        std::vector<std::string> parallel_tasks;
    };

    struct RawProject
    {
        RawProject();
        float max_resource;
        float max_peak_resource;
        std::vector<RawTask> tasks;
    };

public:
    /**
     * @brief Construct a Project object from the source XMLDocument
     * 
     * @param document the source document
     */
    Project(const XmlDocument& document);
    Project(const Project&) = delete;
    ~Project();
private:
    Project(const RawProject& proj);
public:
    /**
     * @brief the project tasks with valid references to other tasks
     */
    const std::vector<Task*> tasks;
    /**
     * @brief the maximum total resource for the project
     */
    const float max_resource;
    /**
     * @brief the maximum peak reasource at any given day for the project
     */
    const float max_peak_resource;
private:
    static RawProject parseRawProject(const XmlDocument& document);
    static std::vector<Task*> parseTasks(const std::vector<RawTask>& rawTasks);
};
