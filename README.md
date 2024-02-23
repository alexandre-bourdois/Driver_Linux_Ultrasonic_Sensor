## Driver for an Ultrasonic Sensor interfaced with a Linux System

### Solution Description

1. Connect to the board via *ssh*.

2. Navigate to the directory `/testFolder`.

3. Run `make`.

4. Load the driver using `sudo insmod main.ko`.

5. Set pin 17 to high to emit a signal on the trigger pin.

6. Monitor the kernel logs to check the measured distance with `dmesg`.

7. Unload the driver using `sudo rmmod main.ko`.

### Authors

Paul RENAULT, Alexandre BOURDOIS, Geoffroy PIGEON, Paul MOREAU.
