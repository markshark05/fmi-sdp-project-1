#include <iomanip>
#include "CommandHelp.h"

CommandHelp::CommandHelp(const ICommandsLoop& loop) :
    Command("help", 0, "help - prints this information"),
    _loop(&loop)
{
}

void CommandHelp::execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args)
{
    const int COL_NAME = 20;
    const int COL_USAGE = 50;

    out << std::left
        << std::setw(COL_NAME) << "Command"
        << std::setw(COL_USAGE) << "Usage"
        << std::endl;

    const std::vector<Command*>& commands = _loop->getCommands();
    for (Command* const& c : commands)
    {
        out
            << std::setw(COL_NAME) << c->getName()
            << std::setw(COL_USAGE) << c->getHelpMessage()
            << std::endl;
    }
}
