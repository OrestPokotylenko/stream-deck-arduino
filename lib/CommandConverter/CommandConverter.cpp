#include "CommandConverter.h"

String CommandConverter::toString(CommandType commandType) {
    switch (commandType)
    {
    case CommandType::NEXT_TRACK:
        return String("NEXT_TRACK");

    case CommandType::PREVIOUS_TRACK:
        return String("PREVIOUS_TRACK");
        
    default:
        return String("PLAY_PAUSE");
    }
}