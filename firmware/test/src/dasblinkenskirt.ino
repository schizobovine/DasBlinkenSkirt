#include<Arduino.h>
#include<Wire.h>
#include<HPRGB2.h>

#define SERIAL_DEBUG 1
#define WRITE_EEPROM 1

const uint16_t ISET_R = 100;
const uint16_t ISET_G = 100;
const uint16_t ISET_B = 100;

const uint16_t PWM_FREQ = 600;

const int TEST_DELAY = 2000;

HPRGB led_driver;

void setup() {

#if SERIAL_DEBUG
  // Setup serial for debugging
  Serial.begin(9600);
  Serial.println("HAI");
#endif

  // Initialize i2c comms
  led_driver.begin();

  // Set current limit and PWM frequencies
  led_driver.setCurrent(ISET_R, ISET_G, ISET_B);
  led_driver.setFreq(PWM_FREQ);

#if WRITE_EEPROM
  // Write settings to EEPROM but only if it's compiled in (should only need to
  // do once since, well, it's EEPROM).
  led_driver.eepromWrite();// write current settings to EEPROM

  // From the original author, I assume to insure the write is finished?
  delay(100);
#endif

}

void loop() {

  // Test red channel
  led_driver.goToRGB(255,0,0);
  delay(TEST_DELAY);

  // Test green channel
  led_driver.goToRGB(0, 255, 0);
  delay(TEST_DELAY);

  // Test blue channel
  led_driver.goToRGB(0, 0, 255);
  delay(TEST_DELAY);

  // Everybody together now...
  led_driver.goToRGB(255,255,255);
  delay(TEST_DELAY);

}
