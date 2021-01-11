#include <fstream>

#include "CommandGenerate.h"
#include "Application.h"
#include "GanttTask.h"
#include "GanttHtml.h"
#include "XmlParserDocument.h"
#include "Project.h"
#include "GanttCore.h"

CommandGenerate::CommandGenerate() :
    Command("generate", 3, "generate [<source>.xml] [<output>.html] [MIN_PEAK | MIN_TIME]")
{
}

GanttCore::OPT convert(const std::string& opt)
{
    if (opt == "MIN_PEAK") return GanttCore::OPT::MIN_PEAK_RES;
    if (opt == "MIN_TIME") return GanttCore::OPT::MIN_TIME;
    throw std::runtime_error("CommandGenerate: invalid option " + opt);
}

void CommandGenerate::execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args)
{
    const std::string& source = args[0];
    const std::string& output = args[1];
    const std::string& option = args[2];

    try
    {
        std::ifstream fi{ source };
        XmlParserDocument doc{ fi };

        Project proj{ doc };
        std::vector<GanttTask> tasks = GanttCore::createTasks(proj, convert(option));
        GanttHtml htmlGenerator{ tasks };

        std::ofstream f{ output, std::ios::out | std::ios::trunc };
        htmlGenerator.generate(f);

        out << "Output generated." << std::endl;
    }
    catch (std::exception e)
    {
        out << "error: " << e.what() << std::endl;
    }
}
