# Blood Pressure

This system record your blood pressure measures and allows you to get your history for medical help.

## Prerequisites

For this code, you will need a C language compiler.

## Compiling and running

You can build this system in any linux-based system using gcc in root folder, as follow:
```
$ gcc main.c -o BloodPressure
```

This will create a new executable in the project root path named BloodPressure (or BloodPressure.exe on windows). Now you only need to run it:

For Linux/MAC users:

```
./BloodPressure 
```

For Windows users, just double click on executable program.

## How to use

Considering that this system was developed in C, the use is around choosing options by typing a number of the option, then pressing Enter key to confirm.

### Hidden menu options

There are actually 2 options on main menu, but there are 3 hidden operations used to help on develop and check for code.

- Option **f**: add some fake data for faster tests, this is very useful on pagination tests.
- Option **d**: show the current state of global __history variable, useful to search for insert/update/delete operations.
- Option **a**: trigger a auto-test function, which do unit checks, useful when manipulate core.h functions.

Obs: to select these options, you can type then as choosed option on main menu screen.

## Some screens

This is the main menu screen:

![Main Menu](./.github/images/main_menu.png)


This is the add new blood pressure form menu:

![Register new blood pressure](./.github/images/add_menu.png)


Example of confirmation message:

![Register new blood pressure with confirmation message](./.github/images/add_menu_confirmation.png)


This is list blood pressure measures screen:

![Measure screens](./.github/images/list_menu.png)


## Todo's

- [ ] Create file persistence layer
- [ ] Allow remove records
- [ ] Order by creation date on list screen


## Authors

- **Nicolas Anelli** - [Github](https://github.com/NicolasAnelli).

### Considerations:

Feel free for forking this project, and submiting any improvement.

## License

MIT License

Copyright (c) 2020 Nicolas Anelli

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
