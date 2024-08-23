# LOW-ESP32 Hardware Monitor

![LOW-ESP32 Hardware Monitor](https://github.com/oauramos/LOW-ESP32-HardwareMonitor/blob/main/doc/Group%203.png)

## Overview

**LOW-ESP32 Hardware Monitor** is a lightweight, powerful solution for real-time monitoring of your PC's hardware stats, directly on an ESP32 with a T-Display V1.1. With this project, you can effortlessly monitor your CPU, GPU, and RAM performance at a glance, all thanks to the Open Hardware Monitor server running on your PC.

## Features

- **Real-Time Monitoring**: Display current CPU, GPU, and RAM statistics on your TTGO ESP32 T-Display.
- **Minimal Setup**: Easily configurable with minimal hardware requirements.
- **Customizable Display**: Adjust the display to show the information you care about most.
- **Wi-Fi Enabled**: Connects to your PC over Wi-Fi to fetch and display data.

## Hardware Requirements

- **TTGO ESP32 T-Display V1.1**
- **Wi-Fi Connection**
- ![PC running Libre Hardware Monitor](https://github.com/LibreHardwareMonitor/LibreHardwareMonitor)

## Default Ports/Localhost

- **LibreOpenHardware - http://localhost:8085/**
- **Express.Js - http://localhost:5000**

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/oauramos/LOW-ESP32-HardwareMonitor.git
   cd LOW-ESP32-HardwareMonitor
   ```

2. **Install required libraries**:

   - Install the required libraries in your Arduino IDE or PlatformIO environment:
     - `ESP32`
     - `TFT_eSPI`
     - `WiFi`
     - `ArduinoJson`

3. **Configure Wi-Fi**:

   - Edit the `config.h` file with your Wi-Fi credentials and the IP address of your Open Hardware Monitor server.

4. **Upload the code**:

   - Compile and upload the code to your TTGO ESP32 T-Display.

5. **Run the Open Hardware Monitor**:
   - Ensure your Open Hardware Monitor server is running and accessible via the configured IP address.

## Usage

Once the code is uploaded and your device is powered on, the TTGO ESP32 T-Display will automatically connect to your Wi-Fi network and start displaying real-time stats from your PC.

- **CPU Usage**: Displays name, load, temp.
- **GPU Usage**: Displays name, load, temp.
- **RAM Usage**: Displays name, load, Max capacity.
- **Disk Usage**: Displays name, load, temp.

## Customization

You can customize what information is displayed and how it is presented by modifying the code in the `main.cpp` file. The display layout and styles can be adjusted to suit your preferences.

## Troubleshooting

- **No Data Displayed?**

  - Check that your ESP32 is connected to the correct Wi-Fi network.
  - Verify that the Open Hardware Monitor server is running and accessible at the configured IP address.
  - Ensure that the IP address in the `config.h` file matches the one used by your Open Hardware Monitor.

- **Display Issues?**
  - Confirm that the correct display settings are configured in the `User_Setup.h` file for your TTGO ESP32 T-Display.

## Contributions

Contributions are welcome! Feel free to submit pull requests or open issues to help improve this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
