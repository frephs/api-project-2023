# API's Project - Academic Year 2022/2023
This is the solution I submitted for the final project of the course of Theoretical Computer Science and Algorithms (Algoritmi e Principi dell'Informatica - API for short) at [Politecnico di Milano](polimi.it).   

You can find the assignment [here](assignment.pdf) and my solution [here](main.c). 

## Tests

The test generator is not provided according to course policy. The open tests are available in the [tests](Tests) folder.


## How to run/compile
The provided Makefile provides several targets to build, test, and debug the program. Here's a brief overview of how to use it:

### Building and Running Tests

* To build the program, simply run `make build`.
* To run a test with input from a file, use `make test TEST=<test_number>`, replacing `<test_number>` with the desired test number.
* To run a test and save the output to a file, use `make testSave TEST=<test_number>`.

### Debugging and Diffing

* To debug a test using gdb, use `make debug TEST=<test_number>`.
* To debug until specific lines of a test, use `make debugLine TEST=<test_number> LINE=<line_number>`.
* To diff the output of a test against the expected output, use `make diff TEST=<test_number>`.
* To diff specific lines of a test output, use `make diffLine TEST=<test_number> LINE=<line_number>`.

### Running Multiple Tests

* To run the diff target on multiple tests until a specified number, use `make diffUntil TEST=<test_number>`.
* To run the diff target from one test to another, use `make diffFromUntil TESTA=<start_test> TESTB=<end_test>`.

### Measuring Time

* To measure the time of running a test and saving the output, use `make time TEST=<test_number>`.

