#include "Application.h"

#include <iostream>
#include <fstream>

#include "GanttTask.h"
#include "HtmlDocument.h"
#include "XmlElementNode.h"
#include "XmlTextNode.h"
#include "GanttHtml.h"
#include "XmlParserDocument.h"

void Application::run(std::istream& in, std::ostream& out)
{
    std::vector<GanttTask> tasks
    {
        GanttTask {"Task One",   1, 2},
        GanttTask {"Task Two",   2, 3},
        GanttTask {"Task Three", 5, 3},
    };

    std::ifstream fi{ "project.xml" };
    XmlParserDocument doc{ fi };

    GanttHtml generator{ tasks };
    std::ofstream f{ "example.html", std::ios::out | std::ios::trunc };
    generator.generate(f);
}
