#ifndef APP_COMMUNICATOR_H
#define APP_COMMUNICATOR_H

#include "command_handler/CommandHandler.h"
#include "serial_controller/SerialController.h"
#include "volume_controller/VolumeController.h"

class AppCommunicator {
    public:
        AppCommunicator(CommandHandler& commandHandler, SerialController& serialController, VolumeController& volumeController);
        void sendCommand();
        void sendVolume();

    private:
        static constexpr const char* COMMAND_PREFIX = "COMMAND: ";
        static constexpr const char* VOLUME_PREFIX = "VOLUME: ";

        CommandHandler& commandHandler;
        SerialController& serialController;
        VolumeController& volumeController;
};

#endif