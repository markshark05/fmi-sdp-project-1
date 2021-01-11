#include "CommandExit.h"

CommandExit::CommandExit(IStoppableLoop& loop) :
    Command("exit", 0, "exit - exists the program"),
    _loop(&loop)
{
}

void CommandExit::execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args)
{
    _loop->stop();
    out << "Exiting the program..." << std::endl;
}
