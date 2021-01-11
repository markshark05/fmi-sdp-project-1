#pragma once
#include <ostream>
#include <vector>

#include "HtmlDocument.h"
#include "XmlElementNode.h"
#include "GanttTask.h"

/**
 * @brief Generates an html representation of the output task vector
 */
class GanttHtml
{
private:
    const std::vector<GanttTask>& tasks;
    const int taskCols;
public:
    /**
     * @brief Construct a GanttHtml object
     *
     * @param tasks the list of source tasks
     */
    GanttHtml(const std::vector<GanttTask>& tasks);
    /**
     * @brief writes the html to the output stream
     *
     * @param out the output stream to write the html to
     */
    void generate(std::ostream& out);
private:
    static int calculate_taskCols(const std::vector<GanttTask>& tasks);
    XmlElementNode* generate_style(HtmlDocument& document);
    XmlElementNode* generate_thead(HtmlDocument& document);
    XmlElementNode* generate_tbody(HtmlDocument& document);
};
