#include "Command.h"

Command::Command(const std::string& name, int minArgsCount, const std::string& helpMessage) :
    name(name),
    minArgsCount(minArgsCount),
    helpMessage(helpMessage)
{
}

const std::string& Command::getName() const
{
    return name;
}

int Command::getMinArgsCount() const
{
    return minArgsCount;
}

const std::string& Command::getHelpMessage() const
{
    return helpMessage;
}

bool Command::authorize()
{
    return true;
}

bool Command::fileRequirement()
{
    return true;
}

std::string Command::promptLine(std::istream& in, std::ostream& out, const std::string& prompt)
{
    std::string str;
    out << prompt << ": ";
    std::getline(in, str);
    return str;
}
