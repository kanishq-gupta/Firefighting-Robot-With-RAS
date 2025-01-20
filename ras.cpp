#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial SIM7670Serial(2, 3); // RX, TX for SIM Module
SoftwareSerial gpsSerial(4, 5);     // RX, TX for GPS Module

const int buzzerPin = 11;           // Define the buzzer pin
const int flame_sensor_pin = 9;     // Fire sensor connected to pin 9
const int led_pin = 2;              // LED pin remains unchanged at pin 2

int flame_pin = HIGH;               // State of the sensor

TinyGPSPlus gps;                    // Create an instance of the GPS object

void setup() {
  Serial.begin(9600);               // Initialize serial communication
  pinMode(buzzerPin, OUTPUT);       // Set buzzer pin as output
  pinMode(led_pin, OUTPUT);         // Set LED pin as output
  pinMode(flame_sensor_pin, INPUT);// Set flame sensor pin as input
  
  SIM7670Serial.begin(115200);      // Initialize SoftwareSerial for SIM module
  gpsSerial.begin(9600);            // Initialize SoftwareSerial for GPS module
  
  sendATCommand("AT", "OK", 1000);  // Check communication with SIM module
  sendATCommand("AT+CMGF=1", "OK", 1000); // Set SMS format to text
}

void loop() {
  checkFlame();                     // Check flame sensor
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());   // Encode GPS data
  }
  delay(100);
}

void sendSMS(String number, String message) {
  String cmd = "AT+CMGS=\"" + number + "\"\r\n";  // AT command for sending SMS
  SIM7670Serial.print(cmd);
  delay(100);
  SIM7670Serial.println(message);    // Send SMS message
  delay(100);
  SIM7670Serial.write(0x1A);         // Send CTRL-Z to terminate SMS
  delay(100);
}

void sendATCommand(String cmd, String expectedResponse, int timeout) {
  SIM7670Serial.println(cmd);        // Send AT command to SIM module
  String response = "";
  long timeStart = millis();
  while (millis() - timeStart < timeout) {
    while (SIM7670Serial.available() > 0) {
      char c = SIM7670Serial.read();
      response += c;
    }
    if (response.indexOf(expectedResponse) != -1) {
      break;
    }
  }
  Serial.println(response);          // Print response from SIM module
}

void checkFlame() {
  flame_pin = digitalRead(flame_sensor_pin);  // Read flame sensor pin
  if (flame_pin == HIGH) {           // Check if fire is detected
    Serial.println("FLAME DETECTED");
    digitalWrite(led_pin, HIGH);     // Turn on the LED
    playMelody();                    // Play melody on the buzzer
    String location = getLocation();
    String message = "FIRE ALERT! LOCATION: " + location; 
    sendSMS("+917302562363", message); // Send SMS with location
  } else {
    Serial.println("No flame detected");
    digitalWrite(led_pin, LOW);      // Turn off the LED
    noTone(buzzerPin);               // Stop playing melody
  }
}

void playMelody() {
  // Play a simple melody: C4, E4, G4, C5
  tone(buzzerPin, 262, 200);   // C4
  delay(200);
  tone(buzzerPin, 330, 200);   // E4
  delay(200);
  tone(buzzerPin, 392, 200);   // G4
  delay(200);
  tone(buzzerPin, 523, 200);   // C5
  delay(200);
}

String getLocation() {
  if (gps.location.isUpdated()) {
    double lat = gps.location.lat();    // Get latitude
    double lng = gps.location.lng();    // Get longitude
    String location = "Lat: " + String(lat, 6) + ", Lng: " + String(lng, 6);
    return location;
  } else {
    return "INVALID"; // Return "Invalid" if location is not available
  }
}
