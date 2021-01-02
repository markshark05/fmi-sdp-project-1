#pragma once
#include <ostream>
#include <vector>

#include "HtmlDocument.h"
#include "XmlElementNode.h"
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
    XmlElementNode* generate_style(HtmlDocument& document);
    XmlElementNode* generate_thead(HtmlDocument& document);
    XmlElementNode* generate_tbody(HtmlDocument& document);
};
