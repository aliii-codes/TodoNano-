# TodoNano 📝

**The ultimate Arduino-powered task manager with persistent storage and intuitive controls.**

[![GitHub stars](https://img.shields.io/github/stars/aliii-codes/TodoNano-?style=for-the-badge)](https://github.com/aliii-codes/TodoNano-/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/aliii-codes/TodoNano-?style=for-the-badge)](https://github.com/aliii-codes/TodoNano-/network/members)
[![GitHub issues](https://img.shields.io/github/issues/aliii-codes/TodoNano-?style=for-the-badge)](https://github.com/aliii-codes/TodoNano-/issues)
[![License](https://img.shields.io/badge/license-MIT-blue.svg?style=for-the-badge)](LICENSE)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)

---

## 🌟 Highlights
- **EEPROM Persistence**: Tasks survive power cycles.
- **Button-Driven UI**: Navigate with up/down/select buttons.
- **Character Scrolling**: Intuitive task input system.
- **20-Task Capacity**: Manage up to 20 tasks efficiently.

---

## ✨ Features

| Feature                  | Description                                                                 |
|--------------------------|-----------------------------------------------------------------------------|
| **Persistent Storage**   | Tasks saved in EEPROM for power-off retention.                             |
| **Intuitive Navigation** | Button controls for menu and task management.                              |
| **Character Input**      | Scroll through characters to type tasks.                                   |
| **Task Management**      | Add/delete up to 20 tasks with visual feedback.                            |
| **Visual Feedback**      | TFT display highlights selections and shows task status.                   |

---

## 🛠️ Tech Stack

| Category       | Technologies                                                                 |
|----------------|------------------------------------------------------------------------------|
| **Language**   | ![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white) |
| **Libraries**  | ![Adafruit ST7735](https://img.shields.io/badge/Adafruit_ST7735-blue?style=flat-square) ![Adafruit GFX](https://img.shields.io/badge/Adafruit_GFX-blue?style=flat-square) ![EEPROM](https://img.shields.io/badge/EEPROM-yellow?style=flat-square) |
| **Hardware**   | ![Arduino Nano](https://img.shields.io/badge/Arduino_Nano-00979D?style=flat-square&logo=arduino&logoColor=white) ![ST7735 TFT](https://img.shields.io/badge/ST7735_TFT-1.44-blue?style=flat-square) ![Buttons](https://img.shields.io/badge/Buttons-Up/Select/Down-green?style=flat-square) |

---

## 🚀 Installation

1. **Clone Repository**  
   ```bash
   git clone https://github.com/aliii-codes/TodoNano-.git
   ```

2. **Install Arduino IDE**  
   Download from [Arduino Official Site](https://www.arduino.cc/en/software).

3. **Install Libraries**  
   - Open Arduino IDE.  
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.  
   - Install `Adafruit ST7735` and `Adafruit GFX`.

4. **Connect Hardware**  
   - Wire the ST7735 TFT display and buttons as per pin definitions in the code.

5. **Upload Code**  
   - Open `the_great_todo.ino` in Arduino IDE.  
   - Select your board and port.  
   - Click `Upload`.

---

## 🕹️ Usage

| Action          | Steps                                                                 |
|-----------------|-----------------------------------------------------------------------|
| **Power On**    | Device starts in the main menu.                                       |
| **Navigation**  | Use up/down buttons to cycle through options.                         |
| **Add Task**    | Navigate to "ADD TODO", scroll characters, hold select to save.       |
| **Delete Task** | Navigate to "DELETE TODO", select task, press select to delete.       |

---

## 📂 Project Structure

```
TodoNano/
├── the_great_todo.ino  # Main Arduino sketch
└── README.md           # Project documentation
```

---

## 🤝 Contributing

Contributions are welcome! Follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

---

## 🐞 Bug Reports & Feature Requests

Open an issue [here](https://github.com/aliii-codes/TodoNano-/issues).

---

## 📜 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

**Acknowledgements**: Built with ❤️ using [Adafruit Libraries](https://github.com/adafruit).
