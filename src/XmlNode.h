#pragma once
#include <vector>
#include <string>
#include <ostream>

/**
 * @brief A base class for any XMLNode
 */
class XmlNode
{
public:
    /**
     * @brief Construct an XmlNode object
     *
     */
    XmlNode() = default;
    XmlNode(const XmlNode&) = delete;

    /**
     * @brief Get the value of the attribute with given name
     * @param attrName the name of the attribute
     * @return std::string the value of the attribute if empty
     */
    virtual std::string getAttr(std::string attrName) const;
    /**
     * @brief Get the Children of the current xmlNode
     * @return std::vector<XmlNode*> the children of the xmlNode
     */
    virtual std::vector<XmlNode*> getChildren() const;

    /**
     * @brief Get the tagName of the node
     * @return std::string the tagName
     */
    virtual std::string getName() const = 0;
    /**
     * @brief writes the current node with all attributes and children to the ostream
     * @param os the ostream to write the node to
     */
    virtual void write(std::ostream& os) const = 0;

    /**
     * @brief operator<< for wriring the node to ostream\n
     * Equivalent to write()
     * @param os the ostream to write the node to
     * @param dt the node
     * @return std::ostream& the same os
     */
    friend std::ostream& operator<<(std::ostream& os, const XmlNode& dt);
};
