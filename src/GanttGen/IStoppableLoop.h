#pragma once

/**
 * @brief Represents an abstract object that can be stopped
 * 
 */
class IStoppableLoop
{
public:
    /**
     * @brief a method that peforms a stop
     * 
     */
    virtual void stop() = 0;
};
