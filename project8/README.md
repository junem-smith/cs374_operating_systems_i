# Project 8: Mutexes
June Smith
CS374 Winter 2026

## Building

Command line:

* `make` to build. An executable called `reservations` will be produced.

VS Code:

* The default build task runs `make`.

## Files

* `reservations.c`: The main code for reserving a given number of seats.

## Data

seat_taken is an array of seats of size initialized by the user.

## Functions

* `lock()`
* `unlock()`
* `reserve_seat()`
* `free_seat()`
* `verify_seat_count()`
* `seat_broker()`
* `main()`

## Notes

* Usage: ./reservations seat_count broker_count xaction_count