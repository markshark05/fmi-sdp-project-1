#include <algorithm>
#include "TaskParser.h"

void TaskParser::parse(XmlDocument& document)
{
    XmlNode* projectNode = nullptr;
    std::vector<XmlNode*> nodes = document.rootNode->getChildren();
    for (XmlNode*& n : nodes)
    {
        if (n->getName() == "project")
        {
            projectNode = n;
            break;
        }
    }
    if (!projectNode)
    {
        throw std::exception("project document: project node not present");
    }

    std::vector<RawTask> tasks;
    std::vector<XmlNode*> taskNodes = projectNode->getChildren();
    for (XmlNode*& taskNode : taskNodes)
    {
        if (taskNode->getName() != "task")
        {
            throw std::exception("project document: unexpected node in project node");
        }

        RawTask task;
        task.name = taskNode->getAttr("name");
        if (task.name.empty())
        {
            throw std::exception("project document: task name cannot be empty");
        }

        task.duration = std::stoi(taskNode->getAttr("duration"));

        std::string min_start_day{ taskNode->getAttr("min-start-day") };
        task.min_start_day = std::stoi(min_start_day.empty() ? "-1" : min_start_day);

        std::string max_start_day{ taskNode->getAttr("max-start-day") };
        task.max_start_day = std::stoi(max_start_day.empty() ? "-1" : max_start_day);

        task.resources = std::stof(taskNode->getAttr("resources"));

        for (XmlNode*& subTaskNode : taskNode->getChildren())
        {
            if (subTaskNode->getName() != "sub-task")
            {
                throw std::exception("project document: unexpected subtask");
            }

            std::string subtaskName{ subTaskNode->getAttr("name") };
            if (subtaskName.empty())
            {
                throw std::exception("project document: subtask name cannot be empty");
            }

            std::string subtaskType{ subTaskNode->getAttr("type") };
            if (subtaskType == "previous")
            {
                task.previous_tasks.push_back(subtaskName);
            }
            else if (subtaskType == "dependent")
            {
                task.dependent_tasks.push_back(subtaskName);
            }
            else if (subtaskType == "parallel")
            {
                task.parallel_tasks.push_back(subtaskName);
            }
            else
            {
                throw std::exception("project document: unexpected subtask type");
            }
        }

        tasks.push_back(task);
    }
}
