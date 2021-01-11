#include <sstream>
#include <algorithm>
#include "XmlParserDocument.h"

XmlParserDocument::XmlParserDocument(std::istream& ss) :
    ss(ss)
{
    stack.push(rootNode);
    parse();
}

void XmlParserDocument::parse_startNode(std::string& name, std::unordered_map<std::string, std::string>& attrs)
{
    XmlElementNode* tmp = createElement(name);
    for (auto& at : attrs)
    {
        tmp->setAttr(at.first, at.second);
    }
    stack.top()->appendChild(tmp);
    stack.push(tmp);
}

void XmlParserDocument::parse_endNode(std::string& name)
{
    stack.pop();
}

void XmlParserDocument::parse_text(std::string& txt)
{
    stack.top()->appendChild(createTextNode(txt));
}

void XmlParserDocument::parse()
{
    std::string str;
    while (std::getline(ss, str, '<'))
    {
        if (str.size() && !std::all_of(str.begin(), str.end(), std::isspace))
        {
            parse_text(str);
        }

        std::getline(ss, str, '>');

        std::istringstream parts{ str };
        std::string name;
        parts >> name;

        std::unordered_map<std::string, std::string> attrs;

        std::string attrPair;
        while (parts >> attrPair)
        {
            size_t eqIdx = attrPair.find_first_of('=');
            std::string attrPart1 = attrPair.substr(0, eqIdx);
            std::string attrPart2 = attrPair.substr(eqIdx + 1);

            attrPart2.erase(0, attrPart2.find_first_not_of('"'));
            attrPart2.erase(attrPart2.find_last_not_of('"') + 1);

            attrs.insert_or_assign(attrPart1, attrPart2);
        }

        if (str[0] == '/')
        {
            parse_endNode(name);
        }
        else
        {
            parse_startNode(name, attrs);
            //self closing tag
            if (str[str.length() - 1] == '/')
            {
                parse_endNode(name);
            }
        }
    }
}
