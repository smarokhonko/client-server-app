#include <iostream>
#include <signal.h>

#include "SignalHandler.h"


SignalHandler::SignalHandler(Client& client)
    : m_client(client)
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
            std::cout << "Received SIGINT. Stopping the client..." << std::endl;

            m_instance->m_client.stop();
        }
    }
}

SignalHandler* SignalHandler::m_instance = nullptr;
