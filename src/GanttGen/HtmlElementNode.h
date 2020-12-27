#pragma once
#include <string>
#include <unordered_map>

#include "HtmlNode.h"

class HtmlElementNode : public HtmlNode
{
private:
    std::string tagName;
    std::unordered_map<std::string, std::string> attributes;
    std::vector<HtmlNode*> children;
public:
    HtmlElementNode(std::string tagName);
    void setAttr(std::string attrName, std::string attrVal);
    void appendChild(HtmlNode* el);

    virtual void write(std::ostream& os) const override;
};
