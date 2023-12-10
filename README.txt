client server app that handles get and put requests to an in-memory key-value store

Build project:
	cd build/
	cmake ..
	make

SERVER:
- accept client connections over unix domain sockets (AF_UNIX)
- accept client connections in the Internet domain (AF_INET)
- accept input from multiple clients concurrently
- detect client connection and disconnection and log the message to the console
- gracefully shutdown (with e.g. SIGINT, SIGTERM)


CLIENT:
- allow connecting to an echo server in the Internet domain (AF_INET) 
- allow connecting to an server in the unix domain (AF_UNIX)
- allow selecting to which server to connect

=====================================================================================================================================
Example of usage help:

./client --help
./server --help

=====================================================================================================================================

EXAMPLE: (echo_server and echo_client use INET connection by dafault "127.0.0.1:8080" if no argument is given)


	run server: ./server
	run client: ./client
	
	put answer 42
    put greeting hello world

    get answer  //outcome: 42

    run other client: ./client
    get greeting //outcome: hello world

