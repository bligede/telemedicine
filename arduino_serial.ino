#include <SoftwareSerial.h>

SoftwareSerial espSerial(19, 18);
String str;

void setup(){
Serial.begin(115200);
espSerial.begin(115200);
delay(2000);
}
void loop()
{
float h = random (60,90);
// Read temperature as Celsius (the default)
float t = random(15,35);
Serial.print("H: ");
Serial.print(h); 
Serial.print("% ");
Serial.print(" T: ");
Serial.print(t); 
Serial.println("C");
str =String("coming from arduino: ")+String("H= ")+String(h)+String("T= ")+String(t);
espSerial.println(str);
delay(1000);
}