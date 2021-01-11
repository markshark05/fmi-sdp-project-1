#pragma once
#include <string>
#include <unordered_map>

#include "XmlNode.h"

/**
 * @brief An XmlElementNode
 */
class XmlElementNode : public XmlNode
{
private:
    const std::string tagName;
    std::unordered_map<std::string, std::string> attributes;
    std::vector<XmlNode*> children;
public:
    /**
     * @brief Construct an XmlElementNode object with given tag name
     * @param tagName the tagName of the element
     */
    XmlElementNode(std::string tagName);

    virtual std::string getAttr(std::string attrName) const override;
    /**
     * @brief Set the value of the attribute with given name
     * @param attrName the name of the attribute
     * @param attrVal the updated value of the attribute
     */
    void setAttr(std::string attrName, std::string attrVal);

    virtual std::vector<XmlNode*> getChildren() const override;
    /**
     * @brief adds a child node of the current Element
     * @param el the child node
     */
    void appendChild(XmlNode* el);

    virtual std::string getName() const override;
    virtual void write(std::ostream& os) const override;
};
