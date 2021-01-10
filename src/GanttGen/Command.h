#pragma once
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Represents an abstract command that can be provided to CLILoop
 * 
 */
class Command
{
private:
    std::string name;
    int minArgsCount;
    std::string helpMessage;
public:
    /**
     * @brief Construct a new Command object
     * 
     * @param name the name for the command used in the CLI
     * @param minArgsCount the minimum number of arguments required to execute the command
     * @param helpMessage a message repsenting the command usage
     */
    Command(const std::string& name, int minArgsCount, const std::string& helpMessage);
    
    /**
     * @brief Get the command name
     * 
     * @return const std::string& 
     */
    const std::string& getName() const;
    /**
     * @brief Get the minimum number of arguments
     * 
     * @return int 
     */
    int getMinArgsCount() const;
    /**
     * @brief Get the help message
     * 
     * @return const std::string& 
     */
    const std::string& getHelpMessage() const;

    /**
     * @brief override in a derived class to prevent the command from runnin because of an authorized user
     * 
     * @return true if the user is authorized
     * @return false otherwise
     */
    virtual bool authorize();
    /**
     * @brief override in a derived class to prevent the command from running because of a required file 
     * 
     * @return true if the should be run
     * @return false otherwise
     */
    virtual bool fileRequirement();
    /**
     * @brief Performs the logic of the command
     * 
     * @param in the CLILopp input stream can be used for interactive prompts
     * @param out the CLILoop output stream can be used for outputing status
     * @param args the parsed arguments from the CLILoop split by whitespace
     */
    virtual void execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args) = 0;
protected:
    /**
     * @brief helper method used to prompt the user for a named parameter
     * 
     * @param in input stream
     * @param out output stream
     * @param prompt parameter name
     * @return std::string the user input
     */
    std::string promptLine(std::istream& in, std::ostream& out, const std::string& prompt);
};
