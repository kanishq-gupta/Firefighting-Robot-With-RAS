#include <Servo.h>  // Include Servo library

Servo myservo;      // Servo object for water spray rotation
int pos = 0;        // Servo position
boolean fire = false; // Fire detection flag

// IR sensor pins
#define Left 10      // Left IR sensor
#define Forward 8    // Front (middle) IR sensor
#define Right 9      // Right IR sensor

// L293D motor driver pins
#define LM1 2        // Left motor IN1
#define LM2 7        // Left motor IN2
#define RM1 4        // Right motor IN3
#define RM2 12       // Right motor IN4

#define pump 6       // Pump control pin

void setup() {
  // Configure IR sensor pins
  pinMode(Left, INPUT);
  pinMode(Forward, INPUT);
  pinMode(Right, INPUT);

  // Configure motor pins
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  // Configure pump pin
  pinMode(pump, OUTPUT);

  // Attach servo motor to pin 11
  myservo.attach(11);
  myservo.write(90); // Set servo to the center position
}

void put_off_fire() {
  // Stop the robot
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);

  // Activate water pump
  digitalWrite(pump, HIGH);

  // Sweep the servo motor to spray water
  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10); // Small delay for smooth servo movement
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }

  // Deactivate water pump
  digitalWrite(pump, LOW);
  myservo.write(90); // Reset servo to center position

  fire = false; // Reset fire detection flag
}

void loop() {
  // Default position for the servo
  myservo.write(90);

  // Read IR sensors
  int leftSensor = digitalRead(Left);
  int forwardSensor = digitalRead(Forward);
  int rightSensor = digitalRead(Right);

  // Control robot movement based on IR sensors
  if (leftSensor == HIGH && rightSensor == HIGH && forwardSensor == HIGH) {
    // Move forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  } else if (forwardSensor == LOW) {
    // Fire detected in front, stop and extinguish
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    fire = true;
  } else if (leftSensor == LOW) {
    // Left IR sensor activated, turn right
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
  } else if (rightSensor == LOW) {
    // Right IR sensor activated, turn left
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }

  delay(300); // Small delay to stabilize the robot's movement

  // If fire is detected, extinguish it
  while (fire) {
    put_off_fire();
  }
}
