#pragma once
#include "Command.h"

class CommandGenerate :
    public Command
{
public:
    /**
     * @brief Construct a new CommandGenerate object
     *
     */
    CommandGenerate();
    void execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args) override;
};
