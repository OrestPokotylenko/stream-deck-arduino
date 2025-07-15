#ifndef COMMAND_CONVERTER_H
#define COMMAND_CONVERTER_H

#include <Arduino.h>
#include "enums/CommandType.h"

class CommandConverter {
    public:
        static String toString(CommandType commandType);
};

#endif