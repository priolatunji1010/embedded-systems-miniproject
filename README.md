# embedded-systems-miniproject
Embedded systems code examples exploring UART, CAN communication, ADC measurements, and FreeRTOS across microcontroller platforms.
# Embedded Systems Mini Project

## Overview

This repository contains embedded systems code examples for XMC, STM32, and ESP32 microcontroller platforms.

The notebook explores UART communication, CAN communication, analog-to-digital conversion, FreeRTOS tasks, and basic threshold-based monitoring logic.

The examples use platform-specific firmware frameworks and should be integrated and tested in their respective development environments.

## Objectives

- Explore embedded C programming.
- Demonstrate UART communication.
- Transmit encoded temperature data over CAN.
- Read analog voltage using an ADC.
- Explore ESP32 UART and TWAI CAN communication.
- Organize functionality into FreeRTOS tasks.
- Implement threshold-based buzzer-control logic.

## Technologies Used

- C
- Infineon XMC and DAVE
- STM32 and STM32 HAL
- ESP32 and ESP-IDF
- UART
- CAN / TWAI
- ADC
- FreeRTOS
- GPIO

## Project Components

### 1. Infineon XMC: Temperature Simulation and CAN

The XMC example initializes the DAVE environment, generates simulated temperature values between approximately 25°C and 35°C, and transmits a scaled temperature value in a CAN data payload.

The temperature is simulated rather than read from a physical sensor.

**Concepts:** Embedded C, simulated sensor data, CAN message encoding, and CAN transmission.

### 2. STM32: ADC Voltage Measurement

The STM32 example uses HAL functions to read an ADC value, convert it to an estimated voltage using a 3.3 V reference, apply a voltage-divider correction factor, and transmit the result over USART2.

**Concepts:** ADC conversion, voltage calculation, voltage-divider compensation, UART output, and periodic measurement.

Correct ADC configuration and safe input voltage levels are required for hardware testing.

### 3. ESP32: UART, CAN, and FreeRTOS

The ESP32 example includes UART initialization, TWAI CAN initialization, CAN message reception, message parsing, and buzzer-control task logic.

The UART configuration uses a baud rate of 115200. The CAN configuration specifies 500 kbit/s. The buzzer logic checks configured temperature and voltage thresholds.

**Concepts:** ESP-IDF drivers, FreeRTOS tasks, UART parsing, CAN reception, and GPIO control.

The code examples require integration and verification before they can be considered a complete application.

## Project Structure

```text
embedded-systems-miniproject/
├── README.md
└── miniproject-xmc-stm-esp.ipynb
```

## Development Requirements

### Infineon XMC

- Compatible XMC development board or target.
- Infineon DAVE environment.
- Configured CAN peripheral and pins.

### STM32

- Compatible STM32 development board.
- STM32CubeIDE or a suitable toolchain.
- Configured ADC and USART2 peripherals.
- Correctly connected voltage-divider circuit.

### ESP32

- Compatible ESP32 board.
- ESP-IDF development environment.
- Appropriate UART connections.
- CAN transceiver compatible with the TWAI peripheral.
- Buzzer or output circuit connected to the configured GPIO.

## How to Use

1. Clone or download this repository.
2. Open `miniproject-xmc-stm-esp.ipynb`.
3. Review the code examples for each platform.
4. Copy the relevant C code into the corresponding vendor development environment.
5. Configure clocks, peripherals, pins, and drivers.
6. Build the firmware for the selected microcontroller.
7. Test communication and peripheral functionality on the target hardware.
8. Document verified results and any board-specific modifications.

The notebook is a collection of embedded code examples, not a single Python application that runs end-to-end.

## Testing and Validation

Suggested tests include:

- Verify UART output at the configured baud rate.
- Compare STM32 ADC voltage readings against a known input.
- Inspect XMC CAN transmission using a compatible CAN interface.
- Verify ESP32 CAN reception and payload decoding.
- Test buzzer behavior at the configured thresholds.
- Validate task scheduling and communication error handling.

No hardware test results are claimed in this README.

## Limitations

- The XMC temperature input is simulated.
- STM32 functionality depends on peripheral configuration and circuit wiring.
- ESP32 code requires application integration and error handling.
- CAN operation requires compatible transceivers and bus configuration.
- Thresholds are hard-coded in the example.
- A complete unified build system and hardware schematic are not included.

## Future Improvements

- Integrate a physical temperature sensor.
- Add ADC calibration and measurement validation.
- Complete ESP32 task creation and error handling.
- Define a consistent CAN message format.
- Add CAN fault handling and communication timeouts.
- Make alarm thresholds configurable.
- Add wiring diagrams and verified hardware test results.

## Disclaimer

This repository is an educational embedded systems project. The examples are not a safety-certified monitoring system. Validate hardware connections, voltage levels, peripheral configuration, and communication behavior before practical use.
