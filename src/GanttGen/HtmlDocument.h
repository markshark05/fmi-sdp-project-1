#pragma once
#include <vector>

#include "HtmlNode.h"
#include "HtmlElementNode.h"
#include "HtmlTextNode.h"

class HtmlDocument : public HtmlNode
{
private:
    std::vector<HtmlNode*> ownedNodes;
    HtmlElementNode* const documentElement;
    HtmlElementNode* const head;
    HtmlElementNode* const body;
public:
    HtmlDocument();
    HtmlDocument(const HtmlDocument&) = delete;
    ~HtmlDocument();

    HtmlElementNode* createElement(std::string tagName);
    HtmlTextNode* createTextNode(std::string value);
    
    HtmlElementNode* getHead() const;
    HtmlElementNode* getBody() const;

    virtual void write(std::ostream& os) const override;
};
