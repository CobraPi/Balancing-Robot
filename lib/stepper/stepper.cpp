#include <Arduino.h>
#include "stepper.h"

Stepper::Stepper(int step_pin, int dir_pin) {
    _step_pin = step_pin;
    _dir_pin = dir_pin;
}

void Stepper::one_step(int direction) {
    digitalWrite(_dir_pin, direction);

}

void Stepper::drive(int direction, int steps, int step_delay) {
    digitalWrite(_dir_pin, direction);
    for (int i = 0; i < steps; i++) {
        digitalWrite(_step_pin, 1);
        delayMicroseconds(step_delay);
        digitalWrite(_step_pin, 0);
        delayMicroseconds(step_delay);
    }
}
