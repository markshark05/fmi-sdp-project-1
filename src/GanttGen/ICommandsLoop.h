#pragma once
#include <vector>
#include "Command.h"

/**
 * @brief Represents an abstract object that provides a list of commands
 * 
 */
class ICommandsLoop
{
public:
    /**
     * @brief a method that returns commands
     * 
     * @return const std::vector\<Command*\>& 
     */
    virtual const std::vector<Command*>& getCommands() const = 0;
};
