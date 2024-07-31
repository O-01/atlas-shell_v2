# hsh - SHELL_V2
![Screenshot](https://github.com/user-attachments/assets/bff7fe95-9d36-41d9-9807-069927b7fbc1)
### Introduction
> This README is for the C - Shell v2 project at Atlas School.
> This document lists all project requirements and allowed standard library functions, as well as steps to compile and run the program.

**hsh** is an application that reads lines from either file or terminal input, parses these lines, and executes entered commands as applicable. hsh implements a language that has flow control constructs, a macro facility that provides a variety of features in addition to data storage, along with possibility for future implementation of built-in history and line editing features. It incorporates many features to aid interactive use and has the advantage that the interpretative language is common to both interactive and non-interactive use.

This program simulates a command interpreter based in UNIX and GNU/LINUX with its basic commands.
hsh is not expected to be an exact implementation of bash, yet it is still quite capable of operating with and performing the most commonly used basic functions.

Operates in the following modes:
- ***Interactive mode*** -
Commands are executed per user interaction within application with constant return to application prompt upon command execution/failure.  
- ***Non-interactive mode*** - Shell runs from an automated process of command(s) piped to the hsh shell executable without entering to the application prompt interface and cannot currently request input or assume that further input may occur.
### Requirements
- Modern GNU/Linux operating system, working environment, or equivalent
- GCC version 4.8.4 or higher along with its dependencies (incl. GNU make)
### Compilation
> This repository contains a makefile for compiling the program using `gcc 4.8.4`.
1. Clone or download source zip [here](https://github.com/O-01/atlas-shell_v2/archive/refs/heads/master.zip) and extract locally.
2. Open console/terminal and navigate to cloned repository directory or directory containing extracted source files.
3. Enter `make`.
4. Source files are compiled to produce `hsh` application.
### Launch
#### Interactive mode:
1. Open console/terminal and navigate to directory containing compiled `hsh` binary.
2. Enter `./hsh` to launch application in interactive mode.
3. User will be presented with prompt that appears as below:
```
# 
```
4. Once any desired commands have been entered at the prompt, the process of their execution will begin once the `ENTER` key is been pressed.
5. Enjoy!
> Interactive mode may be exited at any time by entering `exit` or pressing `CTRL+D` at the prompt.
#### Non-interactive mode:
1. Open console/terminal and navigate to directory containing compiled `hsh` binary.
2. Echo desired command as pipe to `./hsh`.

Example:
```
$ echo "ls -1R" | ./hsh
AUTHORS
build
hsh
hsh-debug
include
Makefile
man_1_hsh
README.md
src
$ 
```
## Features
- This program displays a prompt and waits for the user to type a command. Command line input is performed by pressing `ENTER` key.

- The prompt is displayed again each time a command has been executed in interactive mode.

- When the user enters `exit`, hsh will end with status 0.

    - User may enter desired code to exit application with that code e.g. `exit 144`.

- Otherwise, user may exit the program using `CTRL+D` (`EOF` / `END OF FILE`).

- Program does not exit when user inputs `^C` (`CTRL+C`).

- Handles successive command line inputs with arguments and pathways.

- Change working directory using `cd`.

- View and manipulate environment variable values using `env`, `setenv`, `unsetenv`.

- Executes programs stored in PATH locations along with arguments.

- When command cannot be found, an error message is printed and returns user to the prompt.

- Commands may be separated by control or redirect operators including: `;` `&&` `||` `>` `>>` `<` `|`.

- Current version only marginally supports pipes `|` and does not support heredoc `<<`.

- Does not currently support commentaries using `#`.

- Does not currently support wildcard characters or quotes in any situation.
## Built-in command implementations
- #### *cd* - Changes current working directory to directory specified.
    ```
    # cd /home ; pwd
    /home
    # pwd ; cd /home ; pwd ; cd - ; pwd
    /home/user/Project/atlas-shell_v2
    /home
    /home/user/Project/atlas-shell_v2
    #
    ```
- #### *env* - Lists environmental variables.
    ```
    # env
    SHELL=/bin/bash
    USER=user
    HOME=/home/user
    [...]
    ```
- #### *exit* - Exits application with desired status code or 0 if unspecified.
    ```
    # exit
    root@user:atlas-shell_v2#
    root@user:atlas-shell_v2# echo $?
    0
    ```
    ```
    # exit 144
    root@user:atlas-shell_v2#
    root@user:atlas-shell_v2# echo $?
    144
    ```
- #### *setenv* - Sets or creates environmental variable of specified name and value.
    ```
    # setenv NAME value
    # env
    [...]
    NAME=value
    ```
- #### *unsetenv* - Clears or removes variable of specified name from environmental variables.
    ```
    # env ; unsetenv NAME ; echo -- ; env
    [...]
    NAME=value
    [...]
    --
    [...]
    [...]
    ```
## Examples of Usage with Standard Applications
- ### *ls*
    ```
    # ls -R
    .:
    AUTHORS  build  hsh  hsh-debug  include  Makefile  man_1_hsh  README.md  src

    ./include:
    _sh.h

    ./src:
    builtin.c  error.c  free.c  _getenv.c  launcher.c  memory_tools.c  operators.c  parse.c  separator.c  _sh.c  string.c  tools.c
    # 
    ```
- ### *cal*
    ```
    # cal -3
    December 2023          January 2024         February 2024      
    Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  
                    1  2      1  2  3  4  5  6               1  2  3  
    3  4  5  6  7  8  9   7  8  9 10 11 12 13   4  5  6  7  8  9 10  
    10 11 12 13 14 15 16  14 15 16 17 18 19 20  11 12 13 14 15 16 17  
    17 18 19 20 21 22 23  21 22 23 24 25 26 27  18 19 20 21 22 23 24  
    24 25 26 27 28 29 30  28 29 30 31           25 26 27 28 29        
    31  
    # 
    ```
- ### *ps*
    ```
    # ps -lm
    F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
    0 -  1000    1792    1524  0   -   - -  2958 -      pts/0    00:00:00 bash
    0 S  1000       -       -  0  80   0 -     - do_wai -        00:00:00 -
    0 -  1000   84034    1792  0   -   - -   622 -      pts/0    00:00:00 hsh
    0 S  1000       -       -  0  80   0 -     - do_wai -        00:00:00 -
    4 -  1000   84245   84034 99   -   - -  3979 -      pts/0    00:00:00 ps
    4 R  1000       -       - 99  80   0 -     - -      -        00:00:00 -
    # 
    ```
## Repository Files
| **File** | *__Description__* |
|----------|----------------:|
|include/_sh.h| Header file for the program that includes definitions for all data structs, macros, and non-static function prototypes|
|src/_sh.c| Main entry for the program, contains functions for handling the input as well as displaying the prompt|
|src/_getenv.c| File containing function for retrieving an environmental variable|
|src/builtin.c| File containing all functions for managing built-ins|
|src/error.c| File containing all functions for handling errors|
|src/free.c| File containing functions for freeing allocated memory|
|src/launcher.c| File containing all functions for routing input commands and operators, as well as forking processes/executing applications|
|src/memory_tools.c| File containing all functions for allocating and managing memory|
|src/operators.c| File containing all functions for managing operators|
|src/parse.c| File containing all functions for parsing inputs containing operators and/or spaces|
|src/separator.c| File containing all functions for dividing input string into separate commands/arguments|
|src/string.c| File containing all functions for manipulating strings|
|src/tools.c| File containing functions for various tools such as a function that checks if an input char is a digit or a function that converts strings to ints|
|Makefile| File containing all the rules needed for compiling the program|
|Authors| File containing the Authors|
## Project description
### Requirements
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 14.04 LTS
- Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
- A README.md file, at the root of the folder of the project, is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- All your header files should be include guarded
- No more than 5 functions per file
- Valgrind should show 0 memory leak and 0 error

### Allowed Function and System Calls
- access
- chdir
- close
- execve
- fork
- stat (__xstat)
- lstat (__lxstat)
- fstat (__fxstat)
- kill
- open
- read
- signal
- wait
- waitpid
- wait3
- wait4
- write
- _exit
- dup
- dup2
- pipe
- unlink
- time
- gethostname
- geteuid
- sigaction
- sigemptyset
- select
- getpid
- _errno_location (ernno macro)
- closedir
- exit
- free
- getcwd
- getline
- malloc
- opendir
- perror
- readdir
- strtok
- localtime
- getpwuid
- isatty
- printf
- fflush
- fprintf
- vfprintf
- sprintf
## Authors / Contact info
- **Sammy Ansari** **|** [Github](https://github.com/O-01) **|** [LinkedIn](https://linkedin.com/in/sammy-ansari) **|** [Email](mailto:sam.ansari@atlasschool.com)
- **Logan Savage** **|** [Github](https://github.com/SavageLM) **|** [LinkedIn](https://www.linkedin.com/in/logan-m-savage/) **|** [Email](mailto:logan.savage@atlasschool.com)  
#
![Atlas School](https://assets-global.website-files.com/6571f4826e9363343bcd2acd/658c333153345aa78869f0b3_logo-atlas-school-blue-lightning-bug.svg)
#
