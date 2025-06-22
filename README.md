# Smart Energy Monitor – Embedded Systems Project

This repository contains the final version of my **Smart Energy Monitor**, developed in 2024 as part of the **ELECTENG 209** course at the University of Auckland.

>  _This project was originally submitted in Semester 2, 2024.  
> The code and documentation have now been archived in this repository for portfolio and learning reference purposes._

---

## Project Overview

The Smart Energy Monitor is an embedded system that measures real-time voltage, current, and power across a connected load.  
It was designed and implemented using the **ATmega328P microcontroller**, with software developed in **C using Atmel Studio**, and circuit simulations in **Proteus** and **LTspice**.

---

##  Key Features

-  **Voltage & Current Measurement**  
  - Measures Vrms and Ipeak values
  - Signal conditioning via voltage dividers and current sense resistors
  - Uses 10-bit ADC with 5V reference

-  **LCD Display Output**  
  - Scrolls between voltage, current, and power readings every 1 second

-  **Real-Time Signal Sampling**  
  - ADC sampling rate at 10 kHz  
  - UART transmission at 9600 baud (8N1, no parity)

-  **Data Transmission via UART**  
  - Sends voltage, current, power, and energy data to external serial monitor

-  **PCB Design (Optional)**  
  - Double-layer PCB layout with PTH, 20000 mm² size limit  
  - Component technology: TH or SMT (optional BLE module)

---

##  Technologies Used

| Component        | Description                     |
|------------------|---------------------------------|
| **Microcontroller** | ATmega328P @ 2 MHz           |
| **Language**     | C (Atmel Studio)                |
| **Simulation**   | LTspice, Proteus                |
| **Display**      | 16x2 LCD                        |
| **Communication**| UART Serial (9600 Baud)         |

---

##  Folder Structure

| Folder           | Contents                                           |
|------------------|----------------------------------------------------|
| `firmware/`      | C source code for ATmega328P                       |
| `ltspice/`       | LTspice simulation files                           |
| `proteus/`       | Proteus simulation project                         |
| `pcb/`           | PCB design files (e.g., EasyEDA or Eagle format)   |
| `docs/`          | Design report, block diagrams, calculations        |

---

##  Background

This project was completed as part of the **ELECTENG 209 course**  
 *University of Auckland – Semester 2, 2024*  
 *Project archived to this personal GitHub repository in 2025 for showcase purposes.*

---

## ✉ Contact

For questions or demo requests, feel free to reach out:  
 Email: avalee0215@gmail.com  
 GitHub: [@avalee0215](https://github.com/avalee0215)
