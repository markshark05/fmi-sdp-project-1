#pragma once
#include <istream>
#include <stack>
#include "XmlDocument.h"

class XmlParserDocument : public XmlDocument
{
private:
    std::istream& ss;
    std::stack<XmlElementNode*> stack;
public:
    XmlParserDocument(std::istream& ss);
private:
    void parse();
    void parse_startNode(std::string& name, std::unordered_map<std::string, std::string>& attrs);
    void parse_endNode(std::string& name);
    void parse_text(std::string& txt);
};
