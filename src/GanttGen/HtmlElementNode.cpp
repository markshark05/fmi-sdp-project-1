#include "HtmlElementNode.h"

HtmlElementNode::HtmlElementNode(std::string tagName) :
    tagName(tagName)
{
}

void HtmlElementNode::setAttr(std::string attrName, std::string attrVal)
{
    attributes.insert_or_assign(attrName, attrVal);
}

void HtmlElementNode::appendChild(HtmlNode* el)
{
    children.push_back(el);
}

void HtmlElementNode::write(std::ostream& os) const
{
    // opening tag
    os << "<" << tagName;
    for (auto& attr : attributes)
    {
        os << " " << attr.first << "=\"" << attr.second << "\"";
    }
    os << ">";

    // children
    for (HtmlNode* const& child : children)
    {
        os << *child;
    }

    // closing tag
    os << "</" << tagName << ">";
}
