#include "Client.h"
#include "ReadFromConsole.h"
#include "PrintToConsole.h"
#include "SignalHandler.h"
#include "Types.h"
#include "Constants.h"
#include "InputDataHandler.h"

int main (int argc, char *argv[])
{
    std::string serverIP = DEFAULT_IP;
    size_t serverPort = DEFAULT_PORT;

    ConnectionType connectionType = ConnectionType::INET;

    if (argc > 1)
    {
        InputDataHandler inputDataHandler(argc, argv);

        if (!inputDataHandler.parseAndValidateInput())
        {
            return 0;
        }

        serverIP = inputDataHandler.getServerIP();
        serverPort = inputDataHandler.getServerPort();
        connectionType = inputDataHandler.getConnectionType();
    }    
    else
    {
        std::cout << "Default connection to: " << DEFAULT_IP << ":" << DEFAULT_PORT << std::endl;
    }

    Client client(  serverIP.c_str(),
                    serverPort,
                    connectionType,
                    UNIX_COMMUNICATION_FILE_NAME,
                    std::make_unique<ReadFromConsole>(), 
                    std::make_unique<PrintToConsole>()
                );

     // Create the SignalHandler object
    SignalHandler signalHandler(client);
    
    client.start();
    
    return 0;
}