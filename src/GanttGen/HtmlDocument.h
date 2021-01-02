#pragma once
#include <vector>

#include "XmlDocument.h"
#include "XmlNode.h"
#include "XmlElementNode.h"
#include "XmlTextNode.h"

class HtmlDocument : public XmlDocument
{
private:
    std::vector<XmlNode*> ownedNodes;
    XmlElementNode* const head;
    XmlElementNode* const body;
public:
    HtmlDocument();

    XmlElementNode* getHead() const;
    XmlElementNode* getBody() const;

    virtual void write(std::ostream& os) const override;
};
