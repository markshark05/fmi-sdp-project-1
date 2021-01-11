#include "XmlTextNode.h"

XmlTextNode::XmlTextNode(std::string value) :
    value(value)
{
}

std::string XmlTextNode::getName() const
{
    return "#text";
}

void XmlTextNode::write(std::ostream& os) const
{
    os << value;
}
