#pragma once
#include <istream>
#include <stack>
#include "XmlDocument.h"

/**
 * @brief An XmlDocument created from an istream
 */
class XmlParserDocument : public XmlDocument
{
private:
    std::istream& ss;
    std::stack<XmlElementNode*> stack;
public:
    /**
     * @brief Construct an XmlDocument from an istream
     * @param ss the istram to use
     */
    XmlParserDocument(std::istream& ss);
private:
    void parse();
    void parse_startNode(std::string& name, std::unordered_map<std::string, std::string>& attrs);
    void parse_endNode(std::string& name);
    void parse_text(std::string& txt);
};
