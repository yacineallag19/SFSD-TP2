This project is a university project at "Ecole superieur d'informatique Alger -ESI-" and it was supervised by Dr.Kermi, its goal is to manipulate a simple data base, and the exemple used is a military data base,you can change the data base proprities and structures as they would fit you.

Since the main goal here is to manipulate data base and optimize it, the focus was more into the logic than into the user interface. However, a better user interface is in developement right now, and soon it will be published.


To run this code, please download the 6 files -"main.c""functions.h""functions.c""interface.h""interface.c""maps.c"-, then open your terminal, change your directory to the directory you saved the downloaded files in, amd run this 2 commands one by one:
                                   gcc -o program.o main.c interface.c functions.c
                                   ./program.o
                        
FILES OVERVIEW:
   functions.h : this file is a header file that contains the data base file structure and functions declarations. the functions declared here are 4 categories:
      1. functions to manipulate file such as open it, close it, update a value in the header or get a value, read and write a bloc in the file
      2. functions to manipulate the index file: since central memory is way too fast compared to secondary memory, it would be better to optimize and use index files. This sections of functions contain all different functions to manipulate the index.
      3. data base manipulation functions such as search for a soldier using his id, add new soldier, remove soldier, print all soldiers, change an info about the soldier and print all soldiers of an id between id1 and id2.
      4. a function that tests if the date of birth is valid during insertion.
   functions.c : this file is a sourcre file that implements all of the functions.h declared functions
