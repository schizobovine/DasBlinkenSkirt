#ifndef __USEC_H__
#define __USEC_H__

/*
 * usec.h - Functions to help with comparing microsecond times, since I find
 * myself using them a lot to avoid the hazards of functions like delay() with
 * respect to the hardware timers and interrupts.
 */

#include<limits.h>

// Define a microseconds type
typedef unsigned long usec_t;
typedef unsigned long usec;

// Overflow safe microseconds comparator
inline usec_t diff(const usec_t x, const usec_t y) {
  usec_t retval = 0;

  if (x > y) {
    retval = x - y;
  } else {
    retval = x + (ULONG_MAX - y);
  }

  return retval;
}

#endif
