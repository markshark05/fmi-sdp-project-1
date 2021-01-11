#include <algorithm>
#include "Project.h"

Project::RawTask::RawTask() :
    min_start_day(-1),
    max_start_day(std::numeric_limits<int>::max()),
    duration(0),
    resources(0.0f)
{
}

Project::RawProject::RawProject() :
    max_resource(0),
    max_peak_resource(0)
{
}

Project::Project(const XmlDocument& document) :
    Project(parseRawProject(document))
{
}

Project::~Project()
{
    for (Task* const& t : tasks)
    {
        delete t;
    }
}

Project::Project(const RawProject& proj) :
    max_resource(proj.max_resource),
    max_peak_resource(proj.max_peak_resource),
    tasks(parseTasks(proj.tasks))
{
}

Project::RawProject Project::parseRawProject(const XmlDocument& document)
{
    RawProject project;

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
        throw std::runtime_error("project parser: project node not present");
    }

    project.max_resource = std::stof(projectNode->getAttr("max-resource"));
    project.max_peak_resource = std::stof(projectNode->getAttr("max-peak-resource"));

    std::vector<RawTask> tasks;
    std::vector<XmlNode*> taskNodes = projectNode->getChildren();
    for (XmlNode*& taskNode : taskNodes)
    {
        if (taskNode->getName() != "task")
        {
            throw std::runtime_error("project parser: unexpected node in project node");
        }

        RawTask task;
        task.name = taskNode->getAttr("name");
        if (task.name.empty())
        {
            throw std::runtime_error("project parser: task name cannot be empty");
        }

        for (RawTask& existingTask : tasks)
        {
            if (existingTask.name == task.name)
            {
                throw std::runtime_error("project parser: task name must be uniqe");
            }
        }

        std::string min_start_day{ taskNode->getAttr("min-start-day") };
        if (!min_start_day.empty())
        {
            task.min_start_day = std::stoi(min_start_day);
        }

        std::string max_start_day{ taskNode->getAttr("max-start-day") };
        if (!max_start_day.empty())
        {
            task.max_start_day = std::stoi(max_start_day);
        }

        if (task.min_start_day > task.max_start_day)
        {
            throw std::runtime_error("project parser: min_start_day cannot be greater than max_start_day");
        }

        std::string duration{ taskNode->getAttr("duration") };
        if (duration.empty())
        {
            throw std::runtime_error("project parser: duration cannot be empty");
        }
        task.duration = std::stoi(duration);

        std::string resources{ taskNode->getAttr("resources") };
        if (duration.empty())
        {
            throw std::runtime_error("project parser: resources cannot be empty");
        }
        task.resources = std::stof(resources);

        for (XmlNode*& subTaskNode : taskNode->getChildren())
        {
            if (subTaskNode->getName() != "sub-task")
            {
                throw std::runtime_error("project parser: unexpected subtask");
            }

            std::string subtaskName{ subTaskNode->getAttr("name") };
            if (subtaskName.empty())
            {
                throw std::runtime_error("project parser: subtask name cannot be empty");
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
                throw std::runtime_error("project parser: unexpected subtask type");
            }
        }

        tasks.push_back(task);
    }

    project.tasks = tasks;

    return project;
}

void updateSubTasks(
    const std::string& rawTaskName,
    const std::vector<std::string>& rawTaskNames,
    const std::vector<Task*>& outputTasks,
    std::unordered_set<Task*>& outputSubTasks)
{
    for (std::string const& name : rawTaskNames)
    {
        if (name == rawTaskName)
        {
            throw std::runtime_error("project parser: task cannot refer to itself");
        }

        Task* found = nullptr;
        for (Task* const& task : outputTasks)
        {
            if (name == task->name)
            {
                found = task;
            }
        }
        if (!found)
        {
            throw std::runtime_error("project parser: task cannot refer to undefined task");
        }

        outputSubTasks.insert(found);
    }
}

std::vector<Task*> Project::parseTasks(const std::vector<RawTask>& rawTasks)
{
    std::vector<Task*> tasks;
    for (const RawTask& rawTask : rawTasks)
    {
        Task* task = new Task;
        task->name = rawTask.name;
        task->min_start_day = rawTask.min_start_day;
        task->max_start_day = rawTask.max_start_day;
        task->duration = rawTask.duration;
        task->resources = rawTask.resources;

        tasks.push_back(task);
    }

    for (size_t i = 0; i < tasks.size(); i++)
    {
        const RawTask& rawTask = rawTasks[i];
        Task* task = tasks[i];

        updateSubTasks(rawTask.name, rawTask.dependent_tasks, tasks, task->dependent_tasks);
        updateSubTasks(rawTask.name, rawTask.previous_tasks, tasks, task->previous_tasks);
        updateSubTasks(rawTask.name, rawTask.parallel_tasks, tasks, task->parallel_tasks);
    }

    return tasks;
}
