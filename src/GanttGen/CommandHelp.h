#pragma once
#include "Command.h"
#include "ICommandsLoop.h"

/**
 * @brief help - prints this information
 * 
 */
class CommandHelp :
    public Command
{
private:
    const ICommandsLoop* _loop;
public:
    /**
     * @brief Construct a new CommandHelp object
     * 
     * @param commandLoop the loop containing the commands
     */
    CommandHelp(const ICommandsLoop& commandLoop);
    void execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args) override;
};
