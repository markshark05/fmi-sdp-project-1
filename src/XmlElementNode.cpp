#include "XmlElementNode.h"

XmlElementNode::XmlElementNode(std::string tagName) :
    tagName(tagName)
{
}

std::string XmlElementNode::getAttr(std::string attrName) const
{
    if (attributes.count(attrName) > 0)
    {
        return attributes.at(attrName);
    }
    return std::string{};
}

void XmlElementNode::setAttr(std::string attrName, std::string attrVal)
{
    attributes.insert_or_assign(attrName, attrVal);
}

std::vector<XmlNode*> XmlElementNode::getChildren() const
{
    return children;
}

void XmlElementNode::appendChild(XmlNode* el)
{
    children.push_back(el);
}

void XmlElementNode::write(std::ostream& os) const
{
    // opening tag
    os << "<" << tagName;
    for (auto& attr : attributes)
    {
        os << " " << attr.first << "=\"" << attr.second << "\"";
    }
    os << ">";

    // children
    for (XmlNode* const& child : children)
    {
        os << *child;
    }

    // closing tag
    os << "</" << tagName << ">";
}

std::string XmlElementNode::getName() const
{
    return tagName;
}
