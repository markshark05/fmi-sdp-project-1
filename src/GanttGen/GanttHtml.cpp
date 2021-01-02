#include <iostream>
#include <fstream>

#include "GanttHtml.h"
#include "GanttTask.h"
#include "XmlNode.h"
#include "XmlDocument.h"
#include "XmlElementNode.h"
#include "XmlTextNode.h"

GanttHtml::GanttHtml(const std::vector<GanttTask>& tasks) :
    tasks(tasks),
    taskCols(calculate_taskCols(tasks))
{
}

void GanttHtml::generate(std::ostream& out)
{
    HtmlDocument document;

    XmlElementNode* style = generate_style(document);
    document.getHead()->appendChild(style);

    XmlElementNode* table = document.createElement("table");
    table->setAttr("class", "gantt");
    table->setAttr("cellspacing", "0");
    table->setAttr("cellpadding", "0");

    XmlElementNode* thead = generate_thead(document);
    table->appendChild(thead);

    XmlElementNode* tbody = generate_tbody(document);
    table->appendChild(tbody);

    document.getBody()->appendChild(table);

    out << document;
}

int GanttHtml::calculate_taskCols(const std::vector<GanttTask>& tasks)
{
    int taskCols = 0;
    for (GanttTask const& task : tasks)
    {
        int end = task.getStartOffset() + task.getLength();
        if (end > taskCols) taskCols = end;
    }
    return taskCols;
}

XmlElementNode* GanttHtml::generate_style(HtmlDocument& document)
{
    XmlTextNode* styleText = document.createTextNode
    (
        "body{font-family:sans-serif;}"
        ".gantt td{font-weight:normal;padding:1.5em;border-right:1px solid #c7c7c7;}"
        ".gantt tr:nth-child(even) .gantt-task{background-color:#444;}"
        ".gantt tr:nth-child(odd) .gantt-task{background-color:#666;}"
    );
    XmlElementNode* style = document.createElement("style");
    style->appendChild(styleText);

    return style;
}

XmlElementNode* GanttHtml::generate_thead(HtmlDocument& document)
{
    XmlElementNode* thead = document.createElement("thead");
    XmlElementNode* tr = document.createElement("tr");
    XmlElementNode* td = document.createElement("td");
    tr->appendChild(td);
    for (int i = 0; i < taskCols; i++)
    {
        XmlTextNode* txt = document.createTextNode("Day " + std::to_string(i + 1));
        td = document.createElement("td");
        td->appendChild(txt);
        tr->appendChild(td);
    }
    thead->appendChild(tr);

    return thead;
}

XmlElementNode* GanttHtml::generate_tbody(HtmlDocument& document)
{
    XmlElementNode* tbody = document.createElement("tbody");
    for (GanttTask const& task : tasks)
    {
        XmlElementNode* tr = document.createElement("tr");
        XmlElementNode* td = document.createElement("td");
        XmlTextNode* txt = document.createTextNode(task.getName());
        td->appendChild(txt);
        tr->appendChild(td);
        for (int i = 0; i < taskCols; i++)
        {
            td = document.createElement("td");
            if (i == task.getStartOffset())
            {
                td->setAttr("class", "gantt-task");
                td->setAttr("colspan", std::to_string(task.getLength()));
                i += task.getLength() - 1;
            }
            tr->appendChild(td);
        }
        tbody->appendChild(tr);
    }

    return tbody;
}
