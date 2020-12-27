#include "HtmlTextNode.h"

HtmlTextNode::HtmlTextNode(std::string value) :
    value(value)
{
}

void HtmlTextNode::write(std::ostream& os) const
{
    os << value;
}
