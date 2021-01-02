#include "XmlTextNode.h"

XmlTextNode::XmlTextNode(std::string value) :
    value(value)
{
}

void XmlTextNode::write(std::ostream& os) const
{
    os << value;
}
