#include <Arduino.h>
#include "button.h"

Button::Button(int8_t my_pin, usec_t _cooldown) {
  this->gpio_pin = my_pin;
  this->cooldown = _cooldown;
  this->last_push = 1;
  this->is_pushed = false;
  this->active_when = LOW;
}

Button::Button(int8_t my_pin) :
  Button::Button(my_pin, DEFAULT_COOLDOWN)
{
}

bool Button::read() {
  int8_t value = digitalRead(gpio_pin);
  return (value == active_when);
}

bool Button::debounce() {
  usec_t now = micros();
  bool pushed = read();
  bool retval = false;


  // Button value reads low, button is being held down, so remember
  if (pushed && !is_pushed) {
    is_pushed = true;
    last_push = now;
  } else {
    usec_t tdiff = diff(now, last_push);

    if (!pushed && is_pushed && tdiff > cooldown) {
      is_pushed = false;
      retval = true;
    }
  }

  return retval;
}
