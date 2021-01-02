#pragma once
#include <vector>
#include <string>
#include <ostream>

class XmlNode
{
public:
    XmlNode() = default;
    XmlNode(const XmlNode&) = delete;

    virtual std::string getAttr(std::string attrName) const;
    virtual std::vector<XmlNode*> getChildren() const;
    
    virtual std::string getName() const = 0;
    virtual void write(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const XmlNode& dt);
};
