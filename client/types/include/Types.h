#pragma once

#include <ostream>

enum class ConnectionType
{
    INET,
    UNIX
};

std::ostream& operator<<(std::ostream& os, const ConnectionType& type);