#pragma once
#include "XmlNode.h"

/**
 * @brief An XMLNode that contains just text 
 */
class XmlTextNode : public XmlNode
{
private:
    const std::string value;
public:
    /**
     * @brief Construct an XmlTextNode with given text value
     * @param value the text value
     */
    XmlTextNode(std::string value);

    virtual std::string getName() const override;
    virtual void write(std::ostream& os) const override;
};
