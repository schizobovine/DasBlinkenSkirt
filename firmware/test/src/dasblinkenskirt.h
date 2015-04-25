#ifndef __DASBLINKENSKIRT_H__
#define __DASBLINKENSKIRT_H__

#include <Arduino.h>
#include <Wire.h>
#include <HPRGB2.h>
#include "button.h"
#include "usec.h"

#ifndef SERIAL_DEBUG
#define SERIAL_DEBUG 1
#endif

#define WRITE_EEPROM 0

#ifndef DPRINT
#if (SERIAL_DEBUG)
#define DPRINT(...) Serial.println(__VA_ARGS__)
#define DPRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINTLN(...)
#endif
#endif

// Color state machine
typedef enum COLOR_STATE {
  CS_RED,
  CS_GREEN,
  CS_BLUE
} color_state_t;

// Brightness state machine
typedef enum BRIGHT_STATE {
  BRIGHT_OFF,
  BRIGHT_LOW,
  BRIGHT_MED,
  BRIGHT_HIGH
} bright_state_t;

// Fix PWM frequency (in kHz)
const uint16_t PWM_FREQ = 600;

// Brightness levels in mA
const int16_t ISET_OFF = 0;
const int16_t ISET_LOW = 100;
const int16_t ISET_MED = 200;
const int16_t ISET_HIGH = 300;

// Pin settings for buttons
const int8_t PIN_COLOR = 6;
const int8_t PIN_BRIGHT = 7;

// Function decls
void setup();
void loop();

#endif
