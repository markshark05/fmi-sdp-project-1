#pragma once
#include <iostream>
#include <vector>

#include "XmlNode.h"
#include "XmlElementNode.h"
#include "XmlTextNode.h"

class XmlDocument : public XmlNode
{
private:
    std::vector<XmlNode*> ownedNodes;
public:
    XmlElementNode* const rootNode;
    
    XmlDocument();
    XmlDocument(XmlElementNode* rootNode);
    ~XmlDocument();

    XmlElementNode* createElement(std::string tagName);
    XmlTextNode* createTextNode(std::string value);

    virtual std::string getName() const override;
    virtual void write(std::ostream& os) const override;
};
