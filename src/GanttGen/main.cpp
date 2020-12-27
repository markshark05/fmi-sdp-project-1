#include <iostream>
#include <fstream>

#include "GanttTask.h"
#include "HtmlDocument.h"
#include "HtmlElementNode.h"
#include "HtmlTextNode.h"
#include "GanttHtml.h"

int main()
{
    std::vector<GanttTask> tasks
    {
        GanttTask {"Task One",   1, 2},
        GanttTask {"Task Two",   2, 3},
        GanttTask {"Task Three", 5, 3},
    };

    std::ofstream f;
    f.open("example.html", std::ios::out | std::ios::trunc);

    GanttHtml generator{ tasks };
    generator.generate(f);
}
