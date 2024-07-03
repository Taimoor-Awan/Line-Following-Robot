# Line Following Robot (LFR)

This repository contains the code for a Line Following Robot (LFR) using Arduino. The robot is designed to follow a black line on a white surface, adjusting its path based on input from multiple sensors. It employs a PID control algorithm for smooth and accurate movement.

## Hardware Setup

### Components
- Arduino board
- Motor driver
- DC motors (2)
- Line sensors (5)
- LED (1)
- Power supply

### Pin Configuration
- Speed control motor A: `int S_A = 6;`
- Motor A positive: `int M_A1 = 8;`
- Motor A negative: `int M_A2 = 7;`
- Motor B positive: `int M_B1 = 9;`
- Motor B negative: `int M_B2 = 10;`
- Speed control motor B: `int S_B = 11;`

- Line sensor 1 (second sensor from left): `int s1 = 4;`
- Line sensor 2 (third sensor from left): `int s2 = 2;`
- Line sensor 3 (fourth sensor from left): `int s3 = 3;`
- Rightmost sensor: `int s4 = 5;`
- Leftmost sensor: `int s5 = 12;`

- LED: `int led = 13;`

## Software Description

### Libraries
- [PID_v1.h](https://github.com/br3ttb/Arduino-PID-Library): Library for implementing the PID control algorithm.

### Variables
- `unsigned long prevt, currt;`: Variables for timing control.
- `int dspeed = 180;`: Desired speed for motors.
- `double Setpoint = 0;`: Target value for PID control.
- `double Output;`: PID output.
- `double Deviation;`: Deviation value for PID input.
- `double Kp = 25, Ki = 0, Kd = 2.5;`: PID tuning parameters.

### Functions
- `void setup()`: Initializes pins and starts PID control.
- `void loop()`: Main loop for reading sensor values, computing PID output, and controlling motors.
- `void forword()`: Function to move the robot forward.
- `void turnRight()`: Function to turn the robot right.
- `void turnLeft()`: Function to turn the robot left.
- `void SturnLeft()`: Function to make a sharp left turn.
- `void SturnRight()`: Function to make a sharp right turn.
- `double getDeviation()`: Calculates the deviation of the robot from the line.

### How It Works
1. **Initialization**: The `setup()` function initializes the pins and PID controller.
2. **Main Loop**: The `loop()` function continuously reads the sensor values to determine the robot's position relative to the line.
3. **Deviation Calculation**: The `getDeviation()` function calculates the deviation based on sensor inputs.
4. **PID Control**: The PID controller computes the correction needed based on the deviation.
5. **Motor Control**: The robot's motors are controlled using the PID output to adjust its path and stay on the line.
6. **Directional Logic**: Depending on the sensor inputs, the robot decides whether to move forward, turn left, turn right, or make sharp turns.

---

This repository aims to provide a simple yet effective example of implementing a line-following robot using Arduino and PID control. Your contributions and feedback are welcome!
