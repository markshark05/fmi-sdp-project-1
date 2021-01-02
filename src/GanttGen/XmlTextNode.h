#pragma once
#include "XmlNode.h"

class XmlTextNode : public XmlNode
{
private:
    const std::string value;
public:
    XmlTextNode(std::string value);

    virtual std::string getName() const override;
    virtual void write(std::ostream& os) const override;
};
