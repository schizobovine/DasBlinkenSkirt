#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "usec.h"

// Debounce timer length (us)
const usec_t DEFAULT_COOLDOWN = 20000;

class Button {

  public:
    Button(int8_t my_pin, usec_t cooldown);
    Button(int8_t my_pin);
    bool debounce(void);

  private:
    usec_t cooldown;
    usec_t last_push;
    int8_t gpio_pin;
    int8_t active_when;
    bool is_pushed;

    bool read(void);

};

#endif

