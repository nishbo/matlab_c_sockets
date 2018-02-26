/*
  Simple test server exploring functionality of socket library

  Written by Anton Sobinov

  Copyright (C) 2017 Anton Sobinov

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

#include "socket_api.h"

#include "stdio.h"
#include <string.h>
#include "stdlib.h"


const char _help[] =
"\ncpp_server.exe creates a local server for MATLAB to connect to.\n"
"USAGE:  cpp_server [port | /?]\n\n"
"where\n"
"\tport\t\t\t\tPort number. Defaults to 44400.\n"
"\n"
"\tOptions:\n"
"\t\t/?\t\t\tDisplay this help message\n";


int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "/?"))
        {
            printf(_help);
            return 0;
        }
        else {
            if (sa_change_port(argv[1]) != saOK)
            {
                printf("Error: %s.\n", sa_last_result());
                return 1;
            }
            else {
                printf("Port set to %s.\n", argv[1]);
            }
        }
    }
    printf("Server initiated.\n");

    while (mj_respond() == mjCOM_OK)
    {

    }

    printf("Closing, %s.\n", sa_last_result());

    sa_close();
    return 0;
}
