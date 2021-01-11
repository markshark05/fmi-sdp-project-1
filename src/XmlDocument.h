#pragma once
#include <iostream>
#include <vector>

#include "XmlNode.h"
#include "XmlElementNode.h"
#include "XmlTextNode.h"

/**
 * @brief An XMLDocument representation
 */
class XmlDocument : public XmlNode
{
private:
    std::vector<XmlNode*> ownedNodes;
public:
    /**
     * @brief The root xml node. <?xml ?> if not overriden in a derived classs.
     */
    XmlElementNode* const rootNode;

    /**
     * @brief Construct an XmlDocument object with the default rootNode
     */
    XmlDocument();
    /**
     * @brief Construct an XmlDocument object with given root node
     * @param rootNode the root node for the document
     */
    XmlDocument(XmlElementNode* rootNode);
    /**
     * @brief Destroy the XmlDocument object
     */
    ~XmlDocument();

    /**
     * @brief Creates an ElementNode owned and managed by the Document
     * @param tagName the tag name of the element
     * @return XmlElementNode* the constructed ElementNode
     */
    XmlElementNode* createElement(std::string tagName);
    /**
     * @brief Creates an TextNode owned and managed by the Document
     * @param value the text value of the element
     * @return XmlTextNode* the constructed XmlTextNode
     */
    XmlTextNode* createTextNode(std::string value);

    virtual std::string getName() const override;
    virtual void write(std::ostream& os) const override;
};
