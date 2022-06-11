*** Author Information ***
* Author: Pietro Baggetta
* Email: pbaggett@uoguelph.ca
* Student ID: 1092160

*** Course Information ***
* CIS*3110
* Assignment 3: Memory Management

*** How to Compile ***
    - make all

*** How to clean/remove all .o and executable files ***
    - make clean

*** How to run program ***
    - Run the following commands after compiling the program with "make all".
    - Different options for program:
        > ./holes <testfile> first
        > ./holes <testfile> best
        > ./holes <testfile> next
        > ./holes <testfile> worst
    - Where testfile is any filename that has the correct formatting for the program to read in.

*** NOTES BEFORE LAUNCHING PROGRAM ***
    - Ensure the testfile is in the same directory as the main program so there is no segmentation
      faults.
    - Ensure the testfile is in the proper format ie.:
            >1 200
            >2 400
            >3 350
        > Where first number represents any consecutive positive integer starting from 1 representing
          the process number.
        > Where second number represents any positive integer greater than one as the size of the
          process.
        > No spaces before the first number on each newline.

*** ABOUT PROGRAM ***
    - Program is complete and works as intended by the assignment instructions.
    - As long as the testfiles are the same format as those attached, feel free to add another testfile
      of the same format.
    - Compile program before executing.
        