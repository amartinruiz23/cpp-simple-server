# cpp-simple-server

Simple server in C++. Reads a message with the shape `"get <text> <number>"` from a socket and replies with the MD5 hash of the `text` after sleeping `number` miliseconds.

It manages multi-threading using a thread pool, and has a LRU cache. The port for communication and the cache size are parameters of the program.

The server can be closed with the `SIGTERM` signal and the cache emptied with the `SIGUSR1` signal.
