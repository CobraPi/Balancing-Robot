#ifndef _STEPPER_H
#define _STEPPER_H

class Stepper {
    private:
        int _step_pin;
        int _dir_pin;

    public:
        Stepper(int step_pin, int dir_pin);
        void one_step(int direction);
        void drive(int direction, int steps, int step_delay);
};

#endif // _STEPPER_H
