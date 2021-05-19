#ifndef SERIALPROTOCOL_H
#define SERIALPROTOCOL_H

typedef enum {
    IncomingMessageEcho = 0x00,

    IncomingMessageDriveMotors = 0x01,
    IncomingMessageSetMotorAcceleration = 0x06,
    IncomingMessageCalibrateAccelerometer = 0x07,
    IncomingMessageRequestAccelerometerData = 0x08,
} IncomingMessageType;

typedef enum {

    OutgoingMessagePing = 254,
    OutgoingMessageDebug = 255,
} OutgoingMessageType;

typedef enum {
    InitializationFailureAccelerometer = 0x09,
} InitializationFailureType;

#endif // SERIALPROTOCOL_H
