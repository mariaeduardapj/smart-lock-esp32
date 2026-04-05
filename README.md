![ESP32](https://img.shields.io/badge/platform-ESP32-blue)
![Status](https://img.shields.io/badge/status-in%20development-yellow)
![IoT](https://img.shields.io/badge/type-IoT-green)
![License](https://img.shields.io/badge/license-MIT-blue)
# 🔐 Smart Lock ESP32

ESP32 based smart door lock prototype combining embedded systems, IoT connectivity and basic authentication security concepts.

This project demonstrates integration between hardware control, network communication and user authentication.

---

# 📌 Features

## Hardware features

* Relay door lock control
* OLED status display
* Buzzer audio feedback
* ESP32 WiFi connectivity

## Security features

* Password authentication
* Incorrect password detection
* Access control logic

## IoT features

* Local web interface
* ESP32 hosting web server
* Network authentication

---

# ⚙️ System Architecture

Authentication flow:

User → Web Interface → ESP32 → Password validation → Relay control

Hardware flow:

ESP32 → Relay → Door lock
ESP32 → OLED → Status display
ESP32 → Buzzer → Sound feedback

---

# 🛠 Hardware

Components used:

* ESP32 DevKit
* Relay module
* SSD1306 OLED display
* Active buzzer
* Breadboard
* Jumper wires

---

# 📂 Project Structure

src/

smart-lock.cpp

hardware/

schematic.kicad
schematic.png
hardware-list.pdf


# 🌐 Web Interface

The ESP32 hosts a local webpage where users can enter the password.

Display shows:

192.168.X.X

User opens browser and enters password.

---

# 🚀 Future Improvements

Planned upgrades:

* Password encryption
* HTTPS support
* Mobile app
* Fingerprint sensor
* MQTT communication
* Cloud logging
* Intrusion detection

---

# 🎯 Learning Objectives

This project was created to practice:

Embedded programming
IoT systems
Hardware integration
Basic security concepts
System architecture design

---

## License
This project is licensed under the MIT License - see the LICENSE.md file for details.

---

Developed by **Maria Eduarda P. de Jesus** 