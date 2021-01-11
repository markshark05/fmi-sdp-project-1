#pragma once
#include <vector>

#include "XmlDocument.h"
#include "XmlNode.h"
#include "XmlElementNode.h"
#include "XmlTextNode.h"

/**
 * @brief An HTMLDocument with head and body
 */
class HtmlDocument : public XmlDocument
{
private:
    std::vector<XmlNode*> ownedNodes;
    XmlElementNode* const head;
    XmlElementNode* const body;
public:
    /**
     * @brief Construct an HtmlDocument object
     * 
     */
    HtmlDocument();

    /**
     * @brief Get the Head element
     * 
     * @return XmlElementNode* 
     */
    XmlElementNode* getHead() const;
    /**
     * @brief Get the Body element
     * 
     * @return XmlElementNode* 
     */
    XmlElementNode* getBody() const;

    virtual void write(std::ostream& os) const override;
};
