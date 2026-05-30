# Driver-Drowsiness-Detection-System-project
🚗 DRIVER DROWSINESS DETECTION SYSTEM
=====================================

📌 Project Title:
Driver Drowsiness Detection System

📌 Description:
This project detects driver drowsiness using a webcam.
It monitors the driver's eyes and checks if they remain closed 
for a certain amount of time. If drowsiness is detected, the system 
sends a signal to Arduino to activate a buzzer or alarm.

The system uses computer vision and machine learning techniques 
to improve road safety and reduce accidents caused by sleepy drivers.

-------------------------------------

🎯 Objectives:
- Detect driver's eye movement in real-time
- Identify drowsiness using Eye Aspect Ratio (EAR)
- Send alert signal to Arduino
- Trigger buzzer/alarm when driver is sleepy

-------------------------------------

🧠 Working Principle:

1. Webcam captures driver's face
2. MediaPipe detects facial landmarks
3. Eye Aspect Ratio (EAR) is calculated
4. If eyes remain closed for more than 1 second:
      → Drowsiness detected
      → Signal sent to Arduino
      → Buzzer turns ON
5. If eyes open:
      → Normal state

-------------------------------------

🛠️ Hardware Used:

- Arduino UNO
- USB Webcam
- Buzzer
- Jumper Wires
- Breadboard
- Computer/Laptop

-------------------------------------

💻 Software Used:

- Python
- OpenCV
- MediaPipe
- Arduino IDE
- Serial Communication (PySerial)

-------------------------------------

📁 Project Files:

DROWSY-ML-ARDUINO.py   → Main Python code
controller_code.ino    → Arduino code
requirements.txt       → Required Python libraries
README.txt             → Project documentation
SOFTWAREUSED.txt       → Software tools list

-------------------------------------

▶️ How to Run the Project:

Step 1:
Install Python (version 3.8 or above)

Step 2:
Install required libraries:
pip install -r requirements.txt

Step 3:
Connect Arduino to PC

Step 4:
Upload Arduino code using Arduino IDE

Step 5:
Run Python program:
python DROWSY-ML-ARDUINO.py

Step 6:
System starts detecting drowsiness

Press ESC to stop program.

-------------------------------------

📌 Applications:

- Driver Safety Systems
- Smart Vehicles
- Transport Monitoring
- Accident Prevention Systems

-------------------------------------

📌 Future Enhancements:

- Add sound alert in Python
- Add SMS notification
- Add mobile app integration
- Use deep learning models

-------------------------------------

👨‍💻 Developed by:
Vishnusai Siripuram

📅 Project Type:
Final Year Project
