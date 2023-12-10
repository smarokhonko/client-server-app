
#pragma once

#include <iostream>
#include <signal.h>

#include "Client.h"

class SignalHandler
{
public:
    SignalHandler(Client& client);

    static void handleSignal(int signum);

private:
    Client& m_client;
    static SignalHandler* m_instance;
};
