# Firefighting Robot with RAS (Remote Alert System)

## Overview
This project demonstrates a Firefighting Robot that can detect fire using IR sensors, extinguish it using a water pump and servo motor, and send real-time alerts via SMS using a GPS and GSM module. The robot is equipped with a flame sensor, GPS module, and remote alert system to notify users about the fire's location. The project utilizes Arduino-based hardware components and software to make the robot functional.

## Components Used

1. **Firefighting Robot**
   - **Servo Motor**: Used to rotate the water spray nozzle for extinguishing fire.
   - **IR Sensors**: Detect obstacles and the presence of fire.
   - **L293D Motor Driver**: Controls the movement of the robot.
   - **Water Pump**: Activated to spray water when fire is detected.
   - **Arduino Board**: Controls the robot's logic and sensors.

2. **Remote Alert System (RAS)**
   - **SIM7670 GSM Module**: Sends SMS alerts when fire is detected.
   - **TinyGPS Module**: Obtains the current GPS coordinates for location reporting.
   - **Flame Sensor**: Detects the presence of fire.
   - **Buzzer**: Sounds an alarm when fire is detected.
   - **LED**: Lights up when fire is detected.

## Project Description

### Firefighting Robot:
The Firefighting Robot autonomously moves based on the input from three IR sensors (left, forward, and right). When the forward IR sensor detects a fire (low signal), the robot halts, and the water pump is activated. The servo motor rotates to spray water in a sweeping motion to extinguish the fire. The robot returns to its normal movement once the fire is extinguished.

### Remote Alert System (RAS):
The RAS monitors the flame sensor for any detection of fire. When a fire is detected, it triggers the following actions:
1. Activates a buzzer to signal the presence of fire.
2. Sends an SMS to a predefined phone number with the GPS coordinates of the location where the fire is detected.
3. Lights up an LED to visually indicate fire detection.

The system utilizes an Arduino board with a SIM7670 GSM module to send SMS alerts and a TinyGPS module to acquire location data.

## Features
- **Autonomous Fire Detection**: The robot can detect fire using IR sensors and automatically activate the water pump to extinguish it.
- **Real-Time Alerts**: The RAS sends SMS notifications with the fire location to the specified phone number.
- **Movement Control**: The robot can navigate and avoid obstacles using the IR sensors, turning left or right as needed.
- **Sound and Visual Alerts**: Buzzer and LED indicators provide local alerts when a fire is detected.

## Getting Started

### Prerequisites
Before running the code, ensure you have the following components:

- Arduino Board (e.g., Arduino UNO)
- Servo Motor
- L293D Motor Driver
- IR Sensors
- Flame Sensor
- SIM7670 GSM Module
- TinyGPS Module
- Buzzer
- LED
- Water Pump
- Jumper Wires
- Power Supply

### Installation

1. **Firefighting Robot Code**:
   - Open the Arduino IDE.
   - Create a new sketch and paste the Firefighting Robot code.
   - Connect the components to the Arduino board as per the wiring diagram provided in the code.
   - Upload the code to the Arduino.

2. **RAS Code**:
   - Open the Arduino IDE.
   - Create a new sketch and paste the RAS code.
   - Connect the components for flame detection and communication to the Arduino board.
   - Upload the code to the Arduino.

### Running the Project
1. Once the robot is powered, it will start moving forward and scanning for obstacles and fire.
2. If a fire is detected by the IR sensor, the robot will stop, activate the water pump, and extinguish the fire using the servo motor.
3. Simultaneously, the RAS will send an SMS with the location coordinates of the fire.
4. The buzzer will sound, and the LED will light up, indicating the fire detection.

## Code Explanation

### Firefighting Robot Code:
- The robot moves based on the input from the IR sensors, stopping and activating the water pump when fire is detected.
- The servo motor rotates to sweep water on the fire.
- The robot returns to its normal state once the fire is extinguished.

### Remote Alert System Code:
- The system checks for fire using the flame sensor.
- If fire is detected, an SMS is sent with the GPS coordinates of the location.
- The buzzer sounds a melody, and the LED turns on to indicate the fire.
