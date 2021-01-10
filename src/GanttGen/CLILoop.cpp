#include <sstream>
#include "CLILoop.h"

CLILoop::CLILoop(std::istream& in, std::ostream& out, std::vector<Command*>& commands) :
    in(&in),
    out(&out),
    running(false),
    commands(&commands)
{
}

void CLILoop::start()
{
    if (!running)
    {
        running = true;
        loop();
    }
}

void CLILoop::stop()
{
    running = false;
}

const std::vector<Command*>& CLILoop::getCommands() const
{
    return *commands;
}

void CLILoop::loop()
{
    std::istream& in{ *this->in };
    std::ostream& out{ *this->out };

    while (running)
    {
        out << "> ";
        std::string line;
        std::getline(in, line);

        if (line.empty())
        {
            continue;
        }

        Command* command = findMatchingCommand(line);
        if (command)
        {
            line.erase(0, command->getName().length());
            std::vector<std::string> args = parseArgs(line);
            
            if (!command->authorize())
            {
                out << "You are not authorized to run this command." << std::endl;
            }
            else if (!command->fileRequirement())
            {
                out << "Command requires an open file." << std::endl;
            }
            else if ((int)args.size() < command->getMinArgsCount())
            {
                out << "Expected " << command->getMinArgsCount() << " argument(s) but got " << args.size() << "." << std::endl;
            }
            else
            {
                command->execute(in, out, args);
            }
        }
        else
        {
            out << "Unknown command." << std::endl;
        }
    }
}

Command* CLILoop::findMatchingCommand(const std::string& lineStr)
{
    Command* bestMatch = nullptr;
    size_t bestMatchLength = 0;
    for (Command*& c : *commands)
    {
        const std::string& commandName = c->getName();
        if (lineStr.compare(0, commandName.length(), commandName) == 0)
        {
            if (commandName.length() >= bestMatchLength)
            {
                bestMatch = c;
                bestMatchLength = commandName.length();
            }
        }
    }
    return bestMatch;
}

std::vector<std::string> CLILoop::parseArgs(const std::string& lineStr)
{
    std::vector<std::string> args;
    
    std::string token;
    std::istringstream linestream{ lineStr };
    while(linestream >> token)
    {
        args.push_back(token);
    }

    return args;
}
