#include "HtmlDocument.h"

HtmlDocument::HtmlDocument() :
    XmlDocument(this->createElement("html")),
    head(this->createElement("head")),
    body(this->createElement("body"))
{
    rootNode->appendChild(head);
    rootNode->appendChild(body);
}

XmlElementNode* HtmlDocument::getHead() const
{
    return head;
}

XmlElementNode* HtmlDocument::getBody() const
{
    return body;
}

void HtmlDocument::write(std::ostream& os) const
{
    os << "<!doctype html>";
    XmlDocument::write(os);
}
