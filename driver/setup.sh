sudo apt-get update
sudo apt-get install wiringpi

gpio -v

gcc -o stepper_motor stepper_motor.c -lwiringPi

sudo ./stepper_motor 200 1 500

