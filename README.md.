# 6DOF Color-Sorting Robotic Arm

A firmware implementation for a 6-Degree of Freedom (6DOF) robotic arm designed to detect, sort, and place objects based on color using an Arduino and the TCS3200 color sensor.

## 🛠 Hardware Components
* **Microcontroller:** Arduino (Uno/Mega)
* **Actuators:** 6 x Servo Motors (Waist, Shoulder, Elbow, Pitch, Roll, Gripper)
* **Sensor:** TCS3200 Color Recognition Sensor
* **Power:** External 5V/6V DC power supply for servos

## 🚀 Key Features
* **Smooth Motion Control:** Uses a `moveSmooth` function to prevent jerky movements and protect servo gears.
* **Color Logic:** Real-time RGB frequency analysis to distinguish between Red, Green, and Blue objects.
* **Modular Tasking:** Independent functions for `redTask()`, `greenTask()`, and `blueTask()` to allow for easy coordinate calibration.

## 📈 Agile Development Workflow
This project follows professional software engineering standards:
* **Feature Branching:** All coordinate adjustments are tested in isolated branches.
* **Pull Requests:** Changes are vetted through code reviews before being merged into the `main` branch.
* **Documentation:** Clear commit history and code comments for system maintainability.

## ⚙️ How to Calibrate
To adjust the drop-off points (e.g., if your bins move):
1. Create a new feature branch.
2. Update the `waist` or `shoulder` values in the respective task function.
3. Open a Pull Request for review.
