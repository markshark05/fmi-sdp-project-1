#pragma once
#include <string>
#include <unordered_map>

#include "XmlNode.h"

class XmlElementNode : public XmlNode
{
private:
    const std::string tagName;
    std::unordered_map<std::string, std::string> attributes;
    std::vector<XmlNode*> children;
public:
    XmlElementNode(std::string tagName);

    std::string getAttr(std::string attrName);
    void setAttr(std::string attrName, std::string attrVal);

    std::vector<XmlNode*> getChildren() const;
    void appendChild(XmlNode* el);

    virtual void write(std::ostream& os) const override;
};
