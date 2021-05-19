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
void drive_motors(float left_speed, int left_direction, int left_distance,
                  float right_speed, int right_direction, int right_distance);
void process_serial();
void handle_echo(uint8_t *data, uint8_t length);
void handle_drive_motors(uint8_t *data, uint8_t length);

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
    process_serial();
    //debug("Testing");
 }

void drive_motors(float left_speed, int left_direction, int left_distance,
                  float right_speed, int right_direction, int right_distance) {

    left_motor.setSpeed(left_speed);
    right_motor.setSpeed(right_speed);
    left_motor.moveTo(left_distance);
    right_motor.moveTo(right_distance);
    left_motor.run();
    right_motor.run();
}

void process_serial() {
    uint8_t code, length, data[length];
    if (Serial.available() >= 2) {
        code = (uint8_t) Serial.read();
        length = (uint8_t) Serial.read();
        data[length];
        if (length > 0) {
            Serial.readBytes(data, length);
        }
    }
    switch (code) {
        case IncomingMessageEcho:
            handle_echo(data, length);
            break;
        case IncomingMessageDriveMotors:
            handle_drive_motors(data, length);
            break;
    }
}

void handle_echo(uint8_t *data, uint8_t length) {
    uint8_t msg[2];
    msg[0] = OutgoingMessagePing;
    msg[1] = 0;
    Serial.write(msg, sizeof(msg));
}

// Format of motor data is:
// {left_speed, left_distance, right_speed, right_distance}
void handle_drive_motors(uint8_t *data, uint8_t length) {
    float left_speed = (float) data[0];
    int left_distance = data[1];
    int left_direction = data[2];
    float right_speed = (float) data[3];
    int right_distance = data[4];
    int right_direction = data[5];
    left_motor.setSpeed(left_speed);
    right_motor.setSpeed(right_speed);
    left_motor.move(left_distance);
    right_motor.move(right_distance);
    left_motor.run();
    right_motor.run();

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
