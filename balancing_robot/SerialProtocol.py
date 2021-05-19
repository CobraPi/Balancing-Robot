class IncomingMessageType:
    echo = 254
    debug = 255

class OutgoingMessageType:
    ping = 0

    drive_motors = 1

    set_motor_acceleration = 6
    calibrate_accelerometer = 7
    request_accelerometer_data = 8

class InitializationFailureType:
    acceleromter_failure = 9
