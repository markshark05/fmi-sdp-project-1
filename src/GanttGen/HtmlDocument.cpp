#include "HtmlDocument.h"

HtmlDocument::HtmlDocument() :
    documentElement(this->createElement("html")),
    head(this->createElement("head")),
    body(this->createElement("body"))
{
    documentElement->appendChild(head);
    documentElement->appendChild(body);
}

HtmlDocument::~HtmlDocument()
{
    for (HtmlNode*& node : ownedNodes)
    {
        delete node;
    }
}

HtmlElementNode* HtmlDocument::createElement(std::string tagName)
{
    HtmlElementNode* node = new HtmlElementNode(tagName);
    ownedNodes.push_back(node);
    return node;
}

HtmlTextNode* HtmlDocument::createTextNode(std::string value)
{
    HtmlTextNode* node = new HtmlTextNode(value);
    ownedNodes.push_back(node);
    return node;
}

HtmlElementNode* HtmlDocument::getHead() const
{
    return head;
}

HtmlElementNode* HtmlDocument::getBody() const
{
    return body;
}

void HtmlDocument::write(std::ostream& os) const
{
    os << "<!doctype html>" << *documentElement;
}
