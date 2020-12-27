#pragma once
#include <string>
#include <ostream>

class HtmlNode
{
public:
    virtual void write(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const HtmlNode& dt);
};
