#include<Arduino.h>
#include<Wire.h>
#include<Adafruit_LSM303.h>
#include<string.h>

Adafruit_LSM303 accel;

void setup() {

  Serial.begin(9600);
  Serial.println("HAI");

  while (!accel.begin()) {
    Serial.println("Unable to initialize i2c with LSM303 module! Retrying in 5s...");
    delay(5000);
  }

}

void barf(int16_t x, int16_t y, int16_t z) {
  char buff[16];

  snprintf(buff, 16, "(% 6d, ", x);
  Serial.print(buff);

  snprintf(buff, 16, "% 6d, ", y);
  Serial.print(buff);

  snprintf(buff, 16, "% 6d)", z);
  Serial.print(buff);

}

void loop() {

  accel.read();

  Serial.print("Acc = ");
  barf(accel.acc.x, accel.acc.y, accel.acc.z);
  Serial.print(" Mag = ");
  barf(accel.mag.x, accel.mag.y, accel.mag.z);
  Serial.println();

  delay(1000);

}
