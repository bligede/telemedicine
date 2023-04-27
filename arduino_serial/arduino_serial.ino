#include <SoftwareSerial.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

SoftwareSerial espSerial(19, 18);
String str;

int sys, dias, bpm;
float t;

bool bPrint = 0;
int count, countT;
char buff[40];

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  Wire.begin(0x50);              // join i2c bus with address #4
  Wire.onReceive(receiveEvent);  // register event
  delay(2000);
}
void loop() {

  sensors.requestTemperatures();

  Wire.onReceive(receiveEvent);  // register event

  t = sensors.getTempCByIndex(0);

  // Serial.print(" T: ");
  // Serial.print(t);
  // Serial.println("C");
  // str = String("coming from arduino: ") + String("H= ") + String(t) + String("T= ") + String(t);
  // espSerial.println(str);
  // delay(1000);
}

void receiveEvent() {

  while (0 < Wire.available())  // loop through all but the last
  {
    char c = Wire.read();  // receive byte as a character

    // Serial.print((int)c);

    if (countT < 4) {
      if (c == 'A') {
        countT = 1;
      }
      if (c == '9') {
        countT++;
      }
      if (c == '1') {
        countT++;
      }
      if (c == '0') {
        countT++;
      }
    } else if (countT == 4) {
      
      if (count == 0) {

        sys = c;

        if (sys <= 0) {
          sys * -1;
        }

      } else if (count == 1) {

        dias = c;

        if (dias <= 0) {
          dias * -1;
        }
      } else {
        bpm = c;
      }
      count++;
      if (count == 3) {

        // Serial.println();

        sprintf(buff, "sys:%d, dias:%d, bpm:%d, t:%d.%02d", sys, dias, bpm, (int)t, (int)(fabsf(t) * 100) % 100);
        Serial.println(buff);

        espSerial.println(buff);

        countT = 0;
        count = 0;

        break;
      }
    }
  }
}
