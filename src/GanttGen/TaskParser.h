#pragma once
#include "XmlDocument.h"

class TaskParser
{
private:
    struct RawTask
    {
        std::string name;
        int min_start_day;
        int max_start_day;
        int duration;
        float resources;
        std::vector<std::string> previous_tasks;
        std::vector<std::string> dependent_tasks;
        std::vector<std::string> parallel_tasks;
    };
public:
    void parse(XmlDocument& document);
};
