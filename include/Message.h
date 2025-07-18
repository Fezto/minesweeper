//
// Created by ayrto on 09/06/2025.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include "enums/Color.h"

namespace Message
{
    inline void warn(std::string_view message)
    {
        std::cerr << Color::Red << '\n'
                  << message << "\n\n"
                  << Color::Reset;
    }
}

#endif // MESSAGE_H
