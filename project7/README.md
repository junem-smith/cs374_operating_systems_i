# Project 7: Multithreading
June Smith
CS374 Winter 2026

## Building

Command line:

* `make` to build. An executable called `grayscaler` will be produced.

VS Code:

* The default build task runs `make`.

## Files

* `grayscaler.c`: The main code to change a ppm file to grayscale and find average RGB values.
* `ppm.c`: Code logic for dealing with / alterring a ppm file
* `ppm.h`: Header for ppm code

## Data

There are two arrays of the length of the input for the number of threads by the user. One is pthread_t, and one is an array of structs.

## Functions

* `run()`
* `main()`

## Notes

* Usage: ./grayscaler threads input.ppm output.ppm
