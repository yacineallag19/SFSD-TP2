Project Overview

Welcome to the university project developed at "Ecole supérieure d'informatique Alger - ESI," supervised by Dr. Kermi. The primary objective of this project is to manipulate a simple database, with the example used being a military database. Feel free to customize the database properties and structures to suit your needs.


Project Focus

The project primarily emphasizes database manipulation and optimization, prioritizing logic over user interface design. While the current focus leans towards the underlying logic, we are actively working on enhancing the user interface, which will be shared soon.
How to Run

To run this code, follow these simple steps:

    Download the following six files:
        main.c
        functions.h
        functions.c
        interface.h
        interface.c
        maps.c

    Open your terminal and navigate to the directory where you saved the downloaded files.

    Run the following commands sequentially:

    gcc -o program.o main.c interface.c functions.c
    ./program.o

Files Overview

    functions.h: This header file contains the database file structure and function declarations, organized into four categories:
        File manipulation functions: Open, close, update header values, read and write blocks in the file.
        Index file manipulation functions: Optimize using index files, including various functions for manipulation.
        Database manipulation functions: Search, add, remove, print soldiers, change soldier information, and print soldiers within a specified ID range.
        Validity test function: Checks if the date of birth is valid during insertion.

    functions.c: This source file implements all the functions declared in functions.h.

    maps.h: Used for mapping names of "wilayas" and military grades.

    interface.h: Declaration of functions used for the interface.

    interface.c: Implementation of the functions declared in interface.h.

    main.c: The main program orchestrating the functionality.

Feel free to explore, modify, and adapt the codebase to meet your specific requirements. If you have any questions or feedback, please don't hesitate to reach out. 
