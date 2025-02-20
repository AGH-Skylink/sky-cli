# sky-cli
## Table of Contents:
1. [Overview](#overview)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [The Basics](#the-basics)
5. [Static variables](#static-variables)
6. [Examples](#examples)

## Overview
**sky-cli** is a command-line interface building library, built on top of *GNU Readline* with C++17. The project is compiled and installed via *CMake*. Library's inner functionality is unit-tested with the help of *GoogleTest* framework. It abstracts away some necessary boilerplate when building a CLI.

The library has been created for student scientific club **AGH Skylink**, as a means for quick and easy deployment of prototype CLIs for various projects of the club. The library is open-source and free to use under the provided license.

## Requirements 
- [GCC](https://gcc.gnu.org/) compiler (with C++17 support)
- [CMake](https://cmake.org/)
- [GoogleTest](https://github.com/google/googletest) (necessary for testing) 

## Installation
First, clone and enter the repository:
```bash
git clone https://github.com/AGH-Skylink/sky-cli.git
cd sky-cli
```
Then set up the project on your machine using CMake:
```bash
cmake -S . -B build
cmake --build build/
sudo cmake --install build/ 
```
Alternatively, you can use the provided bash script:
```bash
sudo ./setup.sh
```
*CMake* also automatically compiles the tests, you can run them with:
```bash
./build/runTests
``` 
If you wish to uninstall the library, you can do:
```bash
sudo ./setup.sh uninstall
```
## The Basics
### Linking
To use this library in your projects you can:

Find the package and link it with *CMake*. Example:
```c
...
add_executable(example_exe "example.cpp")

find_package(skycli REQUIRED)
target_link_libraries(example_exe PRIVATE skycli::skycli)
...
```
Or, you can also link it manually with *GCC* like so:
```bash
g++ example.cpp -lskycli -lreadline
```

### Using the library in your code
All necessary parts are included in a single header file, so doing this is enough to get started:
```cpp
#include <skycli/skycli.hpp>
```
The core of the library is contained in the `CLI` class.
```
skycli::CLI cli;
```
`CLI` objects contain all of the necessary commands, and also handle core logic. They can be constructed in a couple of ways:
```cpp
skycli::CLI example; // default, prompt = "> ", delimeter = " "
skycli::CLI example(const std::string &prompt); // sets a custom prompt
skycli::CLI example(const char &delim); // sets a custom argument delimeter
skycli::CLI example(const std::string &prompt, const char &delim); // sets a custom prompt and delimeter
```

**sky-cli** provides several macros to streamline user experience. The most important one is used to add new commands to a `CLI` object:
```cpp
add_command_to_cli(cli_obj, command_name, description, function, ...);
```
*cli_obj* is a `CLI` object instance.
 *command_name* is the name that will be used inside the running CLI to invoke a function.
 *description* is the commands description that will be available with the "help" command inside the CLI.
 *function* is a pointer to a void function accepting 0-6 arguments. 
 The following macro parameters should be the types of *function*s arguments. CLI only allows the following types: `bool, int, float, double, char, std::string`.

`skycli::CLI::run_loop()` starts the CLI. 

Small, working example of the library's capabilities:

```cpp
#include <iostream>
#include <skycli/skycli.hpp>

void hello() {
	std::cout << "Hello!" << std::endl;
}

void hello_n(int a) {
	std::cout << "Hello " << a << " times!" << std::endl;
}

int main() {
	skycli::CLI cli(">>> ");
	
	add_command_to_cli(cli, "hello", "Say hello to the user", hello);
	add_command_to_cli(cli, "hello_n", "Say hello many times", hello_n, int);

	cli.run_loop();
}
```
Result:
```c
>>> asdfg
Unknown command. Maybe try using 'help'?
>>> help
AVAILABLE COMMANDS:
hello - argument #: 0
    Say hello to the user
--------------------
hello_n - argument #: 1, argument types: int 
    Say hello many times
--------------------
help/HELP - argument #: 0
    Lists all available commands
--------------------
exit/EXIT - argument #: 0
    Exits the CLI
--------------------
>>> hello
Hello!
>>> hello_n
Warning: Insufficient number of arguments. Expected: 1, received: 0
>>> hello_n 2.5
Warning: Wrong type of argument #1. Argument type should be: int
>>> hello_n 5
Hello 5 times!
>>> exit
```
Thanks to the use of *GNU Readline*, history and shortcuts are provided out of the box.

### Static variables
The library also enables the use of "static" variables. These variables are created inside a `CLI` object, and are reachable and modifiable inside user-defined commands. 

To add a static-var-using command to the `CLI` object, you should use a different, but similar macro to the one used with regular commands:
```cpp
add_command_to_cli_s(cli_obj, command_name, description, function, ...);
```
The *function* also has to look a little bit different. The first argument can be made a simple macro:
```cpp
void example_func(STATIC_VARS(), int a, int b);
```
To add a static variable to the CLI, you need to make use of some macros. First, register the variable, before using it inside of any function:
```cpp
REGISTER_VAR(var_name, var_type);
```
```cpp
REGISTER_VAR(variable1, int); // example
```
It can also be done in a single header, which will be included in other files, where the functions are defined.

Then, you can access this variable inside a function:
```cpp
void example_func(STATIC_VARS(), int a, int b) {
	int &var = GET_VAR(variable1);
	var += a - b;
	std::cout << var << std::endl;
}
```
And remember to add that variable to your `CLI` object inside `main`:
```cpp
skycli::CLI cli;
ADD_VAR(cli, variable1);
```
You can access the variable inside functions in three ways:
```cpp
type& var = GET_VAR(example); //as a reference
type var = GET_VAR(example); //as a copy, modifying this value won't change the static one
type *var = &GET_VAR(example); //as a pointer
```
`GET_VAR(name)` is a modifiable r-value. 

An important thing to note, is that static variables can be of any type, including user defined. That means that they can be very handy for more complex applications, or already existing code-bases.

## Examples
Example:
```cpp
#include <iostream>
#include <string>
#include <skycli/skycli.hpp>

static double temp =  0;
static double pressure =  0;

void set_param(std::string param, double val) {
	if (param == "temp") {
		temp = val;
	}
	else if (param == "pressure") {
		pressure = val;
	}
}

void get_param(std::string param) {
	if (param == "temp") {
		std::cout << temp << std::endl;
	}
	else if (param ==  "pressure") {
		std::cout << pressure <<  std::endl;
	}
}

int main() {
	skycli::CLI cli;

	add_command_to_cli(cli, "set", "Set the value of a given parameter", set_param, std::string, double);
	add_command_to_cli(cli, "get", "Print the value of a given parameter", get_param, std::string);

	cli.run_loop();
}
```
Result:
```c
> get temp
0
> set temp 12.5
> get temp
12.5
> set pressure aaa
Warning: Wrong type of argument #2. Argument type should be: double
> get pressure
0
> exit
```
\
Example with static variables:
```cpp
#include <iostream>
#include <string>
#include <skycli/skycli.hpp>

REGISTER_VAR(temp, double);
REGISTER_VAR(pressure, double);

void set_param(STATIC_VARS(), std::string param, double val) {
	if (param == "temp") {
		GET_VAR(temp) = val;
	}
	else if (param == "pressure") {
		GET_VAR(pressure) = val;
	}
}

void get_param(STATIC_VARS(), std::string param) {
	if (param == "temp") {
		std::cout << GET_VAR(temp) << std::endl;
	}
	else if (param == "pressure") {
		std::cout << GET_VAR(pressure) << std::endl;
	}
}

int main() {
	skycli::CLI cli;
	
	ADD_VAR(cli, temp);
	ADD_VAR(cli, pressure);
	add_command_to_cli_s(cli, "set", "Set the value of a given parameter", set_param, std::string, double);
	add_command_to_cli_s(cli, "get", "Print the value of a given parameter", get_param, std::string);
	
	cli.run_loop();
}
```
Result:
```c
> get temp
0
> set temp 10
> get temp
10
> set pressure -123
> get pressure
-123
> help
AVAILABLE COMMANDS:
set - argument #: 2, argument types: string double 
    Set the value of a given parameter
--------------------
get - argument #: 1, argument types: string 
    Print the value of a given parameter
--------------------
help/HELP - argument #: 0
    Lists all available commands
--------------------
exit/EXIT - argument #: 0
    Exits the CLI
--------------------
> exit
```