#pragma once
#include <vector>
#include "Command.h"
#include "IStoppableLoop.h"
#include "ICommandsLoop.h"

/**
 * @brief The CLILoop runns the specified commands using the provided istream and ostream\n 
 * Presnets a prompt to the user, splits the arguments and finds the requested commands.\n 
 * Provides error handling for missing commands, unsatisfied command requirements invalid argument count, etc.
 */
class CLILoop :
    public IStoppableLoop,
    public ICommandsLoop
{
private:
    std::istream* in;
    std::ostream* out;
    std::vector<Command*>* commands;
    bool running;
public:
    /**
     * @brief Construct a new CLILoop object
     * 
     * @param in the input stream
     * @param out the output stream
     * @param commands a vector of Command objects that the loop will support 
     */
    CLILoop(std::istream& in, std::ostream& out, std::vector<Command*>& commands);
    /**
     * @brief Starts execution and blocks untill stop() is called
     * 
     */
    void start();
    /**
     * @brief stops the user prompt
     * 
     */
    void stop();
    /**
     * @brief Get a reference to the supported commands
     * 
     * @return const std::vector\<Command*\>& 
     */
    const std::vector<Command*>& getCommands() const;
private:
    void loop();
    Command* findMatchingCommand(const std::string& lienStr);
    std::vector<std::string> parseArgs(const std::string& lineStr);
};
