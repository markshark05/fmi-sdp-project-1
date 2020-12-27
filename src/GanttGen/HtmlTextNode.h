#pragma once
#include "HtmlNode.h"

class HtmlTextNode : public HtmlNode
{
private:
    const std::string value;
public:
    HtmlTextNode(std::string value);

    virtual void write(std::ostream& os) const override;
};
