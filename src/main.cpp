/*
  Arduino Code to run the steppers and get data from the
  acceperometer. All the processing is done on the Raspberry
  Pi

  Pinout:

  x_step = D2
  x_dir  = D5
  y_step = D3
  y_dir  = D6
  z_step = D4
  z_dir  = D7
*/
#include <Arduino.h>
#include "AccelStepper.h"
#include "MultiStepper.h"
#include "MPU6050.h"
#include "serialprotocol.h"
//#include "stepper.h"

#define R_STEP 2
#define R_DIR 5
#define L_STEP 3
#define L_DIR 6
#define Z_STEP 4
#define Z_DIR 7
#define FORWARD 1
#define BACKWARD 0
#define STEPS_PER_REVOLUTION 800

AccelStepper right_motor(AccelStepper::FULL4WIRE, Z_STEP, Z_DIR);
AccelStepper left_motor(AccelStepper::FULL4WIRE, L_STEP, L_DIR);

MultiStepper motors;

void debug(char *message);
void drive_motors(float left_speed);
void process_serial();

void setup() {
    Serial.begin(115200);
    right_motor.setMaxSpeed(1000);
    right_motor.setAcceleration(1000.0);
    left_motor.setMaxSpeed(1000);
    left_motor.setAcceleration(1000.0);
    motors.addStepper(right_motor);
    motors.addStepper(left_motor);
}


void loop() {
    int code, value, distance;
    if (Serial.available() >= 1) {
        code = Serial.read();
        Serial.println(code);
        //     value = Serial.read();
        //distance = Serial.read();
    }
    switch(code) {
        case 49:
            right_motor.setSpeed(1000);
            //right_motor.move(-800);
            right_motor.run();
            Serial.println("right");
            break;
        case 48:
            left_motor.setSpeed(1000);
            //left_motor.move(-800);
            left_motor.run();
            Serial.println("left");
            break;
        case 50:
            long positions[2];
            positions[0] = -1000;
            positions[1] = 1000;
            motors.moveTo(positions);
            motors.run();
            positions[0] = 0;
            positions[1] = 0;
            motors.moveTo(positions);
            motors.run();
            Serial.println("both");
            break;
    }
 }


 void debug(char *message) {
    uint8_t len = strlen(message);
    uint8_t packet[2 + len];

    packet[0] = OutgoingMessageDebug;
    packet[1] = len;

    for (int i = 0; i < len; i++) {
        packet[i + 2] = (uint8_t) message[i];
    }

    Serial.write(packet, sizeof(packet));
}
