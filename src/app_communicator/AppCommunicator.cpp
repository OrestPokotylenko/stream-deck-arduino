#include "AppCommunicator.h"
#include "CommandConverter.h"

AppCommunicator::AppCommunicator(CommandHandler& commandHandler, SerialController& serialController)
    : commandHandler(commandHandler), serialController(serialController) {}

void AppCommunicator::sendCommand() {
    CommandType commandType = commandHandler.getCommandType();

    if (commandType != CommandType::NONE) {
        serialController.writeToSerial(CommandConverter::toString(commandType));
    }
}