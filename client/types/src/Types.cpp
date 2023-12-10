#include "Types.h"

std::ostream& operator<<(std::ostream& os, const ConnectionType& type)
{
    switch(type)
    {
        case ConnectionType::INET:
            os << "AF_INET" << std::endl;
            break;
        case ConnectionType::UNIX:
            os << "AF_UNIX" << std::endl;
            break;
        default:
            os << "Unexpected ConnectionType: " << static_cast<int>(type) << std::endl;       
    }

    return os;
}