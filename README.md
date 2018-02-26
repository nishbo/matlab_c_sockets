# Fast MATLAB-C Communication Sockets

The project allows for fast and efficient communication between MATLAB and an external C/C++-based application using custom socket interface. Current implementation contains only Windows sockets.

The communication is handled by a server socket being maintained in a CPP-side, and MATLAB connecting to it when needed. Majority of code is shared between client and server side, which helps remove errors associated with wrong handling of data on both sides.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

This project's code is available on [GitHub](https://github.com/nishbo/matlab_c_sockets).

### Prerequisites

[MATLAB 2017a+](https://www.mathworks.com/products/matlab.html)

C/C++ compiler:

* [Microsoft Visual Studio 2015+](https://www.visualstudio.com/downloads/) (recommended for Windows)

* GCC (automatic compilation not implemented), available from [MinGW](http://www.mingw.org/)

Make tool (optional) for automatic compilation available as a part of MSYS from [MinGW](http://www.mingw.org/)

For C/C++ compiler make sure that the environments are available from command line when you want to compile the source:

* Visual Studio: `cl --version`

* GCC: `gcc --version`

Use [src/startcl.bat](src/startcl.bat) to launch 64-bit Visual Studio environment. Requires `VS140COMNTOOLS` global variable, which should be set during Visual Studio installation.

### Compiling Server side

#### Using Make

Assuming the compilers are set up and make tool is available, the following code should run without errors:

```
matlab_c_sockets>cd src
matlab_c_sockets/src>make all
```

This should create directories for object files and executables.

#### Without Make

The command sequence can be executed manually:

```
matlab_c_sockets>mkdir bin
matlab_c_sockets>cd src
matlab_c_sockets/src>cl /Fe../bin/cpp_server.exe cpp_server.cpp socket_api.cpp socket.cpp crossplatform_win.cpp /O2 /EHsc /MT
```

### Compiling MATLAB side

Run the [src/makeClient.m](src/makeClient.m) from MATLAB IDE. It should create matlab_client.mexw64 file in the parent directory.

## Running the test

Start the server by either double-clicking on the executable file in the bin folder, or running it from command line:

```
matlab_c_sockets>cd bin
matlab_c_sockets/bin>cpp_server.exe
```

Run [testClient.m](testClient.m) script from MATLAB IDE. The script connects to the server, requests some data, and closes the connection.

## Adding a new communication

In this section is described where the code needs to be changed and edited to make a novel communication between MATLAB and C++.

1. Specify the structures that you wish to send from MATLAB and to MATLAB in [src/socket_api.h](src/socket_api.h) around line 106 analogous to `mjRequestSquares` and `mjReplySquares`. One for sending from MATLAB, and another to send data from CPP-server.
2. Write how the structures should be handled on the server and client side. Use
    * `mjtResult mj_request_squares(const mjRequestSquares* rqs, mjReplySquares* res)` (client)
    * `mjtResult mj_respond_squares(void)` (server)
in [src/socket_api.cpp](src/socket_api.cpp) as an example. Do not forget to declare them in [src/socket_api.h](src/socket_api.h)!
3. For proper response to a client request, add a new message code to `mjtComCode`  (line 40 of [src/socket_api.h](src/socket_api.h)). Add handling of this message to `mjtResult mj_respond(void)` in [src/socket_api.cpp](src/socket_api.cpp) line 372.
4. Write a MATLAB wrapper of the input in [src/matlab_client.cpp](src/matlab_client.cpp) analogous to `mxArray* getsquares(const mxArray* pin)` fucntion. It rearranges data from the MATLAB style into a structure and passes it to the client-side function.
5. Add handling of a new input keyword to MATLAB client same as in lines 264-265 and write a description into `const char* _help` (line 176).
6. Recompile the MATLAB and the server side using [src/makeClient.m](src/makeClient.m) and make, and it should be ready to use.

## Using on different computers and changing port

This software allows communication between client and server on different computers. When cpp_server starts, it prints IP address and port to which to connect to. If connecting on the same computer, it can be omitted on MATLAB side: matlab_client.mexw64 allows 'connect' without additional arguments, see 'help'.

Port can be passed to CPP server as a second argument: `cpp_server.exe 44401`. Connection to it on the same machine from MATLAB: `matlab_client('connect', '', '44401')`. Note that the port is passed as a char array.

## Authors

* **Emo Todorov** - *Initial work* - http://homes.cs.washington.edu/~todorov/

* **Anton Sobinov** - *Organization and restructuring of code* - [nishbo](https://github.org/nishbo)

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE.md](LICENSE.md) file for details.
