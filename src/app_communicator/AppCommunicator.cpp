#include "AppCommunicator.h"
#include "CommandConverter.h"

AppCommunicator::AppCommunicator(CommandHandler& commandHandler, SerialController& serialController, VolumeController& volumeController)
    : commandHandler(commandHandler), serialController(serialController), volumeController(volumeController) {}

void AppCommunicator::sendCommand() {
    CommandType commandType = commandHandler.getCommandType();

    if (commandType != CommandType::NONE) {
        serialController.writeToSerial(COMMAND_PREFIX + CommandConverter::toString(commandType));
    }
}

void AppCommunicator::sendVolume() {
    int volume = volumeController.getVolume();
    serialController.writeToSerial(VOLUME_PREFIX + String(volume));
}