#include "dasblinkenskirt.h"

// Initial values for colors
uint8_t color_r = 255;
uint8_t color_g = 0;
uint8_t color_b = 0;

// Initial values for LED current
uint16_t iset_r = ISET_OFF;
uint16_t iset_g = ISET_OFF;
uint16_t iset_b = ISET_OFF;

// Initial state setup
color_state_t color_state = CS_RED;
bright_state_t bright_state = BRIGHT_OFF;

// LED driver object
HPRGB led_driver = HPRGB();

// Button debouncers
Button butt_color = Button(PIN_COLOR);
Button butt_bright = Button(PIN_BRIGHT);

////////////////////////////////////////////////////////////////////////
// setup() - Called once just after device reset
////////////////////////////////////////////////////////////////////////

void setup() {

#if SERIAL_DEBUG
  // Setup serial for debugging
  Serial.begin(9600);
  Serial.println("HELLO");
#endif

  // Initialize i2c comms
  Wire.begin();
  led_driver.begin();

  // Set current limit and PWM frequencies
  led_driver.setCurrent(iset_r, iset_g, iset_b);
  led_driver.setFreq(PWM_FREQ);

  // Setup buttons
  pinMode(PIN_COLOR, INPUT_PULLUP);
  pinMode(PIN_BRIGHT, INPUT_PULLUP);

#if WRITE_EEPROM
  // Write settings to EEPROM but only if it's compiled in (should only need to
  // do once since, well, it's EEPROM).
  led_driver.eepromWrite();// write current settings to EEPROM

  // From the original author, I assume to insure the write is finished?
  delay(100);
#endif

}

////////////////////////////////////////////////////////////////////////
// loop() - Done many times, like your mom
////////////////////////////////////////////////////////////////////////

void loop() {

  // Check if color change button has been pushed
  if (butt_color.debounce()) {
    switch (color_state) {
      case CS_BLUE:
        color_r = 255;
        color_g = 0;
        color_b = 0;
        color_state = CS_RED;
        DPRINTLN("RED");
        break;
      case CS_RED:
        color_r = 0;
        color_g = 255;
        color_b = 0;
        DPRINTLN("GREEN");
        color_state = CS_GREEN;
        break;
      case CS_GREEN:
        color_r = 0;
        color_g = 0;
        color_b = 255;
        DPRINTLN("BLUE");
        color_state = CS_BLUE;
        break;
      default:
        DPRINTLN("OMG SHOULD NOT HAPPEN (1)");
        break;
    }
  }


  // Check if brightness change button has been pushed
  if (butt_bright.debounce()) {
    switch (bright_state) {
      case BRIGHT_HIGH:
        iset_r = ISET_OFF;
        iset_g = ISET_OFF;
        iset_b = ISET_OFF;
        bright_state = BRIGHT_OFF;
        DPRINTLN("OFF");
        break;
      case BRIGHT_OFF:
        iset_r = ISET_LOW;
        iset_g = ISET_LOW;
        iset_b = ISET_LOW;
        bright_state = BRIGHT_LOW;
        DPRINTLN("LOW");
        break;
      case BRIGHT_LOW:
        iset_r = ISET_MED;
        iset_g = ISET_MED;
        iset_b = ISET_MED;
        bright_state = BRIGHT_MED;
        DPRINTLN("MED");
        break;
      case BRIGHT_MED:
        iset_r = ISET_HIGH;
        iset_g = ISET_HIGH;
        iset_b = ISET_HIGH;
        bright_state = BRIGHT_HIGH;
        DPRINTLN("HIGH");
        break;
      default:
        DPRINTLN("OMG SHOULD NOT HAPPEN (2)");
        break;
    }
  }

  // Perform settings
  led_driver.goToRGB(color_r, color_g, color_b);
  led_driver.setCurrent(iset_r, iset_g, iset_b);

}
