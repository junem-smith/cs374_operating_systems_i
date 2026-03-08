# Project 9: Producers and Consumers
June Smith
CS374 Winter 2026

## Building

Command line:

* `make` to build. An executable called `pc` will be produced.

## Files

* `pc.c`: The main code with producers and consumers.
* `eventbuf.c`: Code for the event buffer logic
* `eventbuf.h`


## Data

seat_taken is an array of seats of size initialized in the command line arguments.

## Functions

* `main()`
    * `eventbuf_create()`
    * `sem_open_temp()`: Handles Semaphore creation
    * `p_run()`: Locks the queue and prints production message, and posts to *items* semaphore
        * `eventbuf_add`
    * `c_run()`: Locks the queue and prints the consumption message, and posts to *spaces* semaphore
        * `eventbuf_empty`
        * `eventbuf_get`
    * `eventbuf_free()`

    

## Notes

* Usage: ./pc nproducers nconsumers events max_outstanding_events
