#pragma once
#include <ostream>
#include <vector>

#include "HtmlDocument.h"
#include "HtmlElementNode.h"
#include "GanttTask.h"

class GanttHtml
{
private:
    const std::vector<GanttTask>& tasks;
    const int taskCols;
public:
    GanttHtml(const std::vector<GanttTask>& tasks);
    void generate(std::ostream& out);
private:
    static int calculate_taskCols(const std::vector<GanttTask>& tasks);
    HtmlElementNode* generate_style(HtmlDocument& document);
    HtmlElementNode* generate_thead(HtmlDocument& document);
    HtmlElementNode* generate_tbody(HtmlDocument& document);
};
