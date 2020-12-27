#pragma once
#include <string>
class GanttTask
{
    std::string name;
    int startOffset;
    int length;
public:
    GanttTask(std::string name, int startOffset, int length);
    std::string getName() const;
    int getStartOffset() const;
    int getLength() const;
};
