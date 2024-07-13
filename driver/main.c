#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define GPIO pin numbers
#define DIR_PIN  0  // GPIO17
#define STEP_PIN 2  // GPIO27
#define EN_PIN   3  // GPIO22

void setup() {
    // Setup wiringPi
    if (wiringPiSetup() == -1) {
        printf("wiringPi setup failed\n");
        exit(1);
    }

    // Set pin modes
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    // Enable the motor driver
    digitalWrite(EN_PIN, LOW); // Enable pin active LOW
}

void rotateStepper(int steps, int direction, int delay_ms) {
    // Set direction
    digitalWrite(DIR_PIN, direction);

    // Rotate stepper
    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delay_ms);  // Delay for the step
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delay_ms);  // Delay before next step
    }
}

int main(int argc, char *argv[]) {
    // Check for correct usage
    if (argc != 4) {
        printf("Usage: %s <steps> <direction> <delay_ms>\n", argv[0]);
        return 1;
    }

    // Get parameters from command line
    int steps = atoi(argv[1]);
    int direction = atoi(argv[2]);
    int delay_ms = atoi(argv[3]);

    // Setup GPIO
    setup();

    // Rotate the stepper motor
    rotateStepper(steps, direction, delay_ms);

    // Disable the motor driver
    digitalWrite(EN_PIN, HIGH); // Disable pin active HIGH

    return 0;
}

