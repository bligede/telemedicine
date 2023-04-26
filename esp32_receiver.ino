
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}

void loop() { // run over and over
if (Serial.available()) {
  String data = Serial.readStringUntil('\n');
    if (data.startsWith("coming from arduino:")) {
      int indexH = data.indexOf("H=") + 2;
      int indexT = data.indexOf("T=") + 2;
      if (indexH > 0 && indexT > 0) {
        String strH = data.substring(indexH, data.indexOf("T="));
        String strT = data.substring(indexT);
        float H = strH.toFloat();
        float T = strT.toFloat();
        Serial.print("Humidity: ");
        Serial.println(H);
        Serial.print("Temperature: ");
        Serial.println(T);
      }
    }
// Serial.write(Serial.read());
}
}


// #include <SoftwareSerial.h>

// SoftwareSerial serial(RX, TX); // RX, TX pin ESP32

// void setup() {
//   Serial.begin(115200);
//   serial.begin(115200);
// }

// void loop() {
//   if (serial.available()) {
//     String data = serial.readStringUntil('\n');
//     if (data.startsWith("coming from arduino:")) {
//       int indexH = data.indexOf("H=") + 2;
//       int indexT = data.indexOf("T=") + 2;
//       if (indexH > 0 && indexT > 0) {
//         String strH = data.substring(indexH, data.indexOf("T="));
//         String strT = data.substring(indexT);
//         float H = strH.toFloat();
//         float T = strT.toFloat();
//         Serial.print("Humidity: ");
//         Serial.println(H);
//         Serial.print("Temperature: ");
//         Serial.println(T);
//       }
//     }
//   }
// }