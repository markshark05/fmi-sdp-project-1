#pragma once
#include <string>

/**
 * @brief The output task with defined start time
 */
class GanttTask
{
private:
    const std::string name;
    const int startOffset;
    const int length;
public:
    /**
     * @brief Construct a GanttTask object
     * 
     * @param name the name/identifer of the task
     * @param startOffset the resolved start time
     * @param length the duration of the task
     */
    GanttTask(std::string name, int startOffset, int length);
    std::string getName() const;
    int getStartOffset() const;
    int getLength() const;
};
