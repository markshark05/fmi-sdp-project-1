#include <fstream>

#include "Application.h"
#include "CLILoop.h"
#include "CommandHelp.h"
#include "CommandExit.h"
#include "CommandGenerate.h"

void Application::run(std::istream& in, std::ostream& out)
{
    std::vector<Command*> commands
    {
        new CommandGenerate{},
    };

    CLILoop cmdloop{ in, out, commands };

    commands.push_back(new CommandHelp{ cmdloop });
    commands.push_back(new CommandExit{ cmdloop });

    cmdloop.start();

    for (Command*& c : commands) delete c;
}
