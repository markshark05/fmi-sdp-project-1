#pragma once
#include "XmlDocument.h"
#include "Task.h"

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
    Project(const XmlDocument& document);
    ~Project();
private:
    Project(const RawProject& proj);
public:
    const std::vector<Task*> tasks;
    const float max_resource;
    const float max_peak_resource;
private:
    static RawProject parseRawProject(const XmlDocument& document);
    static std::vector<Task*> parseTasks(const std::vector<RawTask>& rawTasks);
};
