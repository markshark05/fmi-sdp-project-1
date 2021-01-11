#pragma once
#include "Command.h"

/**
 * @brief generate [<source>.xml] [<output>.html] [MIN_PEAK | MIN_TIME]
 *
 */
class CommandGenerate :
    public Command
{
public:
    /**
     * @brief Construct a CommandGenerate object
     *
     */
    CommandGenerate();
    void execute(std::istream& in, std::ostream& out, const std::vector<std::string>& args) override;
};
