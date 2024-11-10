/*the values of this code are hypothetical values and were made on wadi dayqah dam, 
considering the height of the dam to be 75m
 thus,after three-quarters of the dam are full the buzzer will start tone.so, 
 when the water level reaches 57m */
#define BLYNK_TEMPLATE_ID "TMPL6OKr3eChp"
#define BLYNK_TEMPLATE_NAME "Flood warning  Sys"
#define BLYNK_AUTH_TOKEN "PZYXYS8oHHWUQyIuygb_uiGiELRDVVNd"
#define BLYNK
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SmtpClient.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "duha";
char pass[] = "12345678";
#define TRIG_PIN   D1 // The ESP8266 pin D1 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN   D2 // The ESP8266 pin D2 connected to Ultrasonic Sensor's ECHO pin
#define Buzzer D7
 double height,waterLev;
void setup(){
    Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
   pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(Buzzer, OUTPUT);
Blynk.virtualWrite(V1, waterLev);
Blynk.virtualWrite(V0, height);
}
void loop(){
  Blynk.run();
 long duration;
  // Clear the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(10);

  // Set the TRIG_PIN HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the ECHO_PIN
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate height in cm
 height = (duration * 0.034) / 2;
waterLev=(75 - height);
 Blynk.virtualWrite(V1, waterLev);
Blynk.virtualWrite(V0, height);

  // suppose the water level is less than 19 meters 
  if (height <= 19 ) {
    // Sound a tone on the buzzer
    tone(Buzzer, 1000); // 1000 Hz

  } else {
    noTone(Buzzer); // Turn the buzzer off

  }

  delay(500); // Wait half a second before the next measurement

}