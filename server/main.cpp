#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>


#include "Server.h"
#include "Types.h"
#include "InputDataHandler.h"
#include "SignalHandler.h"
#include "Constants.h"

int main (int argc, char* argv[])
{
    std::string serverIP = DEFAULT_IP;
    size_t serverPort = DEFAULT_PORT;

    if (argc > 1)
    {
        InputDataHandler inputDataHandler(argc, argv);

        if (!inputDataHandler.parseAndValidateInput())
        {
            return 0;
        }

        serverIP = inputDataHandler.getServerIP();
        serverPort = inputDataHandler.getServerPort();
    }    
    else
    {
        std::cout << "Default connection to: " << DEFAULT_IP << ":" << DEFAULT_PORT << std::endl;
    }

    Server server(serverIP, serverPort);

    // Create the SignalHandler object
    SignalHandler signalHandler(server);

    server.start();

    return 0;
}