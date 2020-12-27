#include "HtmlNode.h"

std::ostream& operator<<(std::ostream& os, const HtmlNode& dt)
{
    dt.write(os);
    return os;
}
