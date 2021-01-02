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

    virtual std::string getAttr(std::string attrName) const override;
    void setAttr(std::string attrName, std::string attrVal);

    virtual std::vector<XmlNode*> getChildren() const override;
    void appendChild(XmlNode* el);

    virtual std::string getName() const override;
    virtual void write(std::ostream& os) const override;
};
