#include <iostream>
#include <signal.h>

#include "SignalHandler.h"
#include "Constants.h"


SignalHandler::SignalHandler(Server& server)
    : m_server(server)
{
    // Set up the SIGINT signal handler
    signal(SIGINT, &SignalHandler::handleSignal);
    signal(SIGTERM, &SignalHandler::handleSignal);

    m_instance = this;
}

void SignalHandler::handleSignal(int signum)
{
    if (signum == SIGINT || signum == SIGTERM)
    {
        if (m_instance != nullptr )
        {
            std::cout << "Received SIGINT. Stopping the server..." << std::endl;

            remove(UNIX_SOCKET_NAME);

            m_instance->m_server.stop();
        }
    }
}

SignalHandler* SignalHandler::m_instance = nullptr;