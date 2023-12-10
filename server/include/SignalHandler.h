#pragma once

#include <iostream>
#include <signal.h>

#include "Server.h"

class SignalHandler
{
public:
    SignalHandler(Server& server);

    static void handleSignal(int signum);

private:
    Server& m_server;
    static SignalHandler* m_instance;
};