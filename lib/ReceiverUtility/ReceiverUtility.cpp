#include "ReceiverUtility.h"

// Filter printable ASCII range
String ReceiverUtility::getCleanString(String receiverInput) {
    String cleanString = "";

    for (size_t i = 0; i < receiverInput.length(); i++)
    {
        char c = receiverInput[i];
        if (c >= 32 && c <= 126)
        {
            cleanString += c;
        }
    }

    return cleanString;
}