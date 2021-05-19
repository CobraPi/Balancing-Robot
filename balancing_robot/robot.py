from SerialProtocol import OutgoingMessageType, IncomingMessageType, InitializationFailureType
import serial
import time


serial_connection = False
serial_port = "/dev/tty.usbmodem14601"
serial_baud = 115200

serial = serial.Serial(serial_port, serial_baud, timeout=10)
time.sleep(5)

def process_serial():
    print("Checking serial communication")
    serial.write([OutgoingMessageType.ping, 0])
    serial_open = read_response_status(IncomingMessageType.echo, None)
    if serial_open:
        print("Serial port opened")
    else:
        print("Failed to open serial port")

def read_response_status(success_code, failure_code):
    control = read_byte()
    length = read_byte()
    msg = None
    print(control, length)
    if length > 0:
        msg = serial.read(length)

    if control == success_code:
        return True

    if control == failure_code:
        return False
    if control == InitializationFailureType.acceleromter_failure:
        self.handle_initialization_failure(msg)

    if control == IncomingMessageType.debug:
        print('Incoming Debug Message:', msg.decode('utf-8'))
        return True#read_response_status(success_code, failure_code)
    else:
        raise Exception('Unexpected serial message {}'.format(control))


def read_byte():
        b = serial.read()
        #print(b)
        return list(b)[0]

def drive_motors(left_speed, left_distance, left_direction, right_speed, right_distance, right_direction):
    """
    left_direction = 1
    right_direction = 1

    if left_distance < 0:
        left_direction = 0
    if right_direction < 0:
        right_direction = 0
    Ω"""
    data = [OutgoingMessageType.drive_motors, 6, left_speed, abs(left_distance), left_direction, right_speed, abs(right_distance), right_direction]
    serial.write(data)

def main():
    process_serial()
    drive_motors(100, 255, 1, 100, 255, 1)
    time.sleep(1)
    #drive_motors(100, 255, 0, 100, 255, 0)
    drive_motors(0, 0, 0, 0, 0, 0)
    #serial.write(OutgoingMessageType.debug, 0)
    #read_response_status(None, None)
    serial.flush()

if __name__ == "__main__":
    try:
        serial.flush()
        main()
    except Exception as e:
        print(str(e))
