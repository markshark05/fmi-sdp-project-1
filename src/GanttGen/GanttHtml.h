#pragma once
#include <ostream>
#include <vector>

#include "HtmlDocument.h"
#include "HtmlElementNode.h"
#include "GanttTask.h"

class GanttHtml
{
private:
    std::vector<GanttTask>& tasks;

    HtmlDocument document;
    int taskCols;
public:
    GanttHtml(std::vector<GanttTask>& tasks);
    void generate(std::ostream& out);
private:
    static int calculate_taskCols(std::vector<GanttTask>& tasks);
    HtmlElementNode* generate_style();
    HtmlElementNode* generate_thead();
    HtmlElementNode* generate_tbody();
};
