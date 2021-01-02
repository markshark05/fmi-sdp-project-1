#pragma once
#include "XmlNode.h"

class XmlTextNode : public XmlNode
{
private:
    const std::string value;
public:
    XmlTextNode(std::string value);

    virtual void write(std::ostream& os) const override;
};
