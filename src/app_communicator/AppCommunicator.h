#ifndef APP_COMMUNICATOR_H
#define APP_COMMUNICATOR_H

#include "command_handler/CommandHandler.h"
#include "serial_controller/SerialController.h"

class AppCommunicator {
    public:
        AppCommunicator(CommandHandler& commandHandler, SerialController& serialController);
        void sendCommand();

    private:
        CommandHandler& commandHandler;
        SerialController& serialController;
};

#endif