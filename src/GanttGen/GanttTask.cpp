#include "GanttTask.h"

GanttTask::GanttTask(std::string name, int startOffset, int length) :
    name(name),
    startOffset(startOffset),
    length(length)
{
}

std::string GanttTask::getName() const
{
    return name;
}

int GanttTask::getStartOffset() const
{
    return startOffset;
}

int GanttTask::getLength() const
{
    return length;
}
