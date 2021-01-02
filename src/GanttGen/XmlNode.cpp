#include "XmlNode.h"

std::ostream& operator<<(std::ostream& os, const XmlNode& dt)
{
    dt.write(os);
    return os;
}

std::string XmlNode::getAttr(std::string attrName) const
{
    return std::string();
}

std::vector<XmlNode*> XmlNode::getChildren() const
{
    return std::vector<XmlNode*>();
}
