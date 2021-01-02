#pragma once
#include <vector>
#include <string>
#include <ostream>

class XmlNode
{
public:
    XmlNode() = default;
    XmlNode(const XmlNode&) = delete;

    virtual void write(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const XmlNode& dt);
};
