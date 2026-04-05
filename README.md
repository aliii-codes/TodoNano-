# TodoNano

## Project Title & Description
A compact, Arduino-based TODO list manager with a TFT display and button controls. It allows users to view, add, and delete tasks persistently stored in EEPROM. Ideal for simple task tracking without external dependencies.

## Features
- **Persistent Storage**: Saves tasks to EEPROM for retention across power cycles.
- **Intuitive Navigation**: Uses buttons for menu navigation and task management.
- **Character Input System**: Allows typing tasks using a scrolling character set.
- **Task Management**: Supports up to 20 tasks with add/delete functionality.
- **Visual Feedback**: Displays tasks and menus on a TFT screen with highlighting for selected items.

## Tech Stack
- **Language**: C++ (Arduino Framework)
- **Libraries**: Adafruit ST7735, Adafruit GFX, EEPROM
- **Hardware**: Arduino Nano, ST7735 TFT Display 1'44 Inch, Buttons (up, select, down)

## Installation
1. **Clone Repository**:  
   ```bash
   git clone https://github.com/aliii-codes/TodoNano.git
   ```
2. **Install Arduino IDE**: Download and install from [Arduino Official Site](https://www.arduino.cc/en/software).
3. **Install Libraries**:  
   - Open Arduino IDE.  
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.  
   - Search and install `Adafruit ST7735` and `Adafruit GFX`.
4. **Connect Hardware**:  
   - Wire the ST7735 TFT display and buttons as per pin definitions in the code.
5. **Upload Code**:  
   - Open `the_great_todo.ino` in Arduino IDE.  
   - Select your board and port.  
   - Click `Upload`.

## Usage
1. **Power On**: The device starts in the main menu.  
2. **Navigation**:  
   - **Up Button**: Cycle through menu options (Watch, Add, Delete).  
   - **Down Button**: Cycle backward through menu options.  
   - **Select Button**: Confirm selection or trigger actions.  
3. **Add Task**:  
   - Navigate to "ADD TODO".  
   - Use up/down buttons to select characters.  
   - Press and hold "Select" to save the task.  
4. **Delete Task**:  
   - Navigate to "DELETE TODO".  
   - Use up/down buttons to select a task.  
   - Press "Select" to delete the highlighted task.  

## Project Structure
```
TodoNano/
├── the_great_todo.ino  # Main Arduino sketch
└── README.md           # Project documentation
```

## License
This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.
```