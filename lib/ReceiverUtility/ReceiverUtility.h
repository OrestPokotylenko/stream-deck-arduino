#ifndef RECEIVER_UTILITY_H
#define RECEIVER_UTILITY_H

#include <Arduino.h>

class ReceiverUtility
{
public:
    static String getCleanString(String receiverInput);
};

#endif