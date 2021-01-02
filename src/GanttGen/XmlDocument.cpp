#include "XmlDocument.h"

XmlDocument::XmlDocument() :
    rootNode(createElement("?xml?"))
{
}

XmlDocument::XmlDocument(XmlElementNode* rootNode) :
    rootNode(rootNode)
{
}

XmlDocument::~XmlDocument()
{
    for (auto& node : ownedNodes)
    {
        delete node;
    }
}

XmlElementNode* XmlDocument::createElement(std::string tagName)
{
    XmlElementNode* node = new XmlElementNode(tagName);
    ownedNodes.push_back(node);
    return node;
}

XmlTextNode* XmlDocument::createTextNode(std::string value)
{
    XmlTextNode* node = new XmlTextNode(value);
    ownedNodes.push_back(node);
    return node;
}

void XmlDocument::write(std::ostream& os) const
{
    os << *rootNode;
}

std::string XmlDocument::getName() const
{
    return "#document";
}
