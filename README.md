# GraffOS — CNC Machine Controller

A real-time CNC controller written in C++20 for a 3-axis (XYZ) router/mill running on a **Raspberry Pi 3**. Reads industry-standard G-code (`.ngc`) files and drives stepper motors and a spindle via GPIO using the WiringPi library.

## Features

- Interactive REPL shell (`GraffOS>`) and single-command CLI mode
- G-code parser following [LinuxCNC order-of-execution](https://linuxcnc.org/docs/stable/html/gcode/overview.html#gcode:order-of-execution)
- Multi-threaded motor control — all axes move simultaneously using `std::thread`
- Circular interpolation (G2/G3) discretized to 0.1 mm segments with helix support
- Software homing via limit switches
- Work Coordinate Systems (G54–G59) with interactive offset entry
- macOS HAL stub for development without hardware

## Supported G-codes & M-codes

| Code | Description |
|------|-------------|
| G0 | Rapid positioning |
| G1 | Linear feed move |
| G2 / G3 | Arc CW / CCW (XY, XZ, YZ planes) |
| G17 / G18 / G19 | Plane selection |
| G20 / G21 | Units: inches / millimeters |
| G28 | Return to home |
| G43 / G49 | Tool length offset on/off |
| G53–G59 | Machine / work coordinate systems |
| G61 / G64 | Exact stop / path blending mode |
| G90 / G91 | Absolute / incremental distance mode |
| G90.1 / G91.1 | Arc absolute / incremental offset mode |
| G94 / G95 | Feed per minute / feed per revolution |
| M0 | Program pause |
| M3 / M4 / M5 | Spindle on CW / CCW / off |
| M6 | Tool change (interactive prompt) |
| M30 | Program end |

## Hardware

| Component | Details |
|-----------|---------|
| Controller | Raspberry Pi 3 |
| Motor driver | DRV8825-style (STEP/DIR/EN + MS1/MS2 microstep select) |
| X axis | 1× stepper, 8 mm/rev leadscrew, GPIO 17/27/22/14/15 |
| Y axis | 2× ganged steppers (gantry), 8 mm/rev, GPIO 23/24/10/9/11 and 25/8/7/5/6 |
| Z axis | 1× stepper, 2 mm/rev leadscrew, GPIO 13/19/16/26/20 |
| Spindle | Brushless motor, PWM on GPIO18, DIR on GPIO4, max 4500 RPM |
| Limit switches | X: GPIO21, Y: GPIO12, Z: GPIO0, T: GPIO1 |

> **Note:** UART must be disabled on the Pi so that GPIO14/GPIO15 are available for X-axis stepper control.

## Requirements

- C++20-capable compiler (g++ or clang++)
- CMake ≥ 3.16
- [WiringPi](https://github.com/WiringPi/WiringPi) (Raspberry Pi only)

```bash
# Install WiringPi on Raspberry Pi
sudo apt install wiringpi
```

On macOS, WiringPi calls are stubbed (`src/hal/wiringMac.cpp`) so the project compiles and runs without hardware.

## Build

```bash
# CMake (recommended)
mkdir build && cd build
cmake ..
make

# Or use the provided script
chmod +x OSCompile.sh
./OSCompile.sh
```

Both produce the executable `cncOS`.

## Usage

### Interactive shell

```bash
./cncOS
```

```
GraffOS> run gFiles/manual.ngc      # execute a G-code file
GraffOS> moveby -x10 -y5 -z-2 -f500 # relative jog (mm, mm/min)
GraffOS> info                        # print current position & state
GraffOS> home                        # home all axes via limit switches
GraffOS> mdi                         # enter MDI mode (single G-code lines)
GraffOS> quit                        # disable motors and exit
```

### Single command

```bash
./cncOS run gFiles/101.ngc
```

Ctrl+C or Ctrl+Z cleanly disables all motors before exiting.

## Project Structure

```
CNCSoftware/
├── src/
│   ├── core/       # main.cpp (REPL), cncSetup.cpp (machine controller)
│   ├── gcode/      # G-code file loader, parser, command tokens, priority rules
│   ├── motion/     # Stepper driver, spindle PWM, arc path generator, limit switches
│   ├── tools/      # Tool length offsets, work coordinate systems
│   └── hal/        # wiringMac.cpp — macOS no-op stubs for WiringPi
├── include/        # Header files mirroring src/ layout + config enums + rpi3pinout.h
├── gFiles/         # Sample G-code programs (.ngc)
├── CMakeLists.txt
└── OSCompile.sh
```

## Known Limitations

- No acceleration/deceleration ramp — constant step delay can cause missed steps at high feedrates.
- G43 tool length offset is stored but not yet applied to Z motion.
- Arc R-word is parsed but I/J/K calculation from R is not yet implemented.
- Canned cycles, coolant (M7/M8), probing, and subprograms are not implemented.

## References

- [LinuxCNC G-code reference](https://linuxcnc.org/docs/html/gcode/g-code.html)
- [LinuxCNC M-code reference](https://linuxcnc.org/docs/html/gcode/m-code.html)
- [LinuxCNC order of execution](https://linuxcnc.org/docs/stable/html/gcode/overview.html#gcode:order-of-execution)
- [LinuxCNC full documentation (PDF)](http://linuxcnc.org/docs/2.8/pdf/LinuxCNC_Documentation.pdf)
