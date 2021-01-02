#include "XmlNode.h"

std::ostream& operator<<(std::ostream& os, const XmlNode& dt)
{
    dt.write(os);
    return os;
}
