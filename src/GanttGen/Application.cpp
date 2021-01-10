#include <fstream>

#include "Application.h"
#include "GanttTask.h"
#include "GanttHtml.h"
#include "XmlParserDocument.h"
#include "Project.h"
#include "GanttCore.h"

void Application::run(std::istream& in, std::ostream& out)
{
    std::ifstream fi{ "project1.xml" };
    XmlParserDocument doc{ fi };

    Project proj{ doc };
    std::vector<GanttTask> tasks = GanttCore::createTasks(proj, GanttCore::OPT::MIN_PEAK_RES);
    GanttHtml htmlGenerator{ tasks };
    std::ofstream f{ "chart1.html", std::ios::out | std::ios::trunc };
    htmlGenerator.generate(f);
}
