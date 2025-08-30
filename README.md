## 📖 Introduction
**general-offensive-1975-project** is a **C++ project** demonstrating fundamental **data structures and algorithms**, inspired by the **Spring 1975 General Offensive and Uprising**, marking Vietnam’s **Reunification Day (April 30th)**.  
This project is developed to commemorate the **50th anniversary (1975–2025)**, also known as **A50**.  

---

## 🚀 Features
- Implementation of key **data structures** (linked list, static array, dynamic array etc.).  
- Demonstration of **classic algorithms** (sorting, searching, traversal, etc.).  
- Historical theme connecting computer science with the **spirit of 30/04/1975**.  

---

## 🛠️ Requirements
- **C++17 or newer**  
- A C++ compiler such as:
  - **GCC / G++** (Linux, Windows via MinGW or MSYS2)

### Recommended Editors/IDEs for Beginners
- **Visual Studio Code (VS Code)**  
  - Lightweight, cross-platform editor  
  - Install the **C/C++ extension (by Microsoft)** for IntelliSense and debugging  
  - Recommended for quick setups and working with multiple platforms  

- **Visual Studio (Community Edition)** (Windows only)  
  - Full IDE with built-in MSVC compiler  
  - Easier debugging and project management for beginners on Windows

## ▶️ How to Run
Open the terminal in VSCode, you can compiled it with:
.\run.bat
and run with:
.\main

📊 Expected Output
When running the program, the expected output will be:
<img width="1511" height="957" alt="Screenshot 2025-08-31 020203" src="https://github.com/user-attachments/assets/c4a60bb3-7a0b-4f9b-ac16-eac4616826af" />

If the result isn't "All tests passed!", you should look under the "Test Results", it will appear failed test.
You can find failed tests in the path:
**test\unit_test_Task4\test_case**

🛠️ Fixing Instructions
- Edit and fix the files:
src/hcmcampaign.h  
src/hcmcampaign.cpp
- Do not touch other files except you need some special fix.
- Keep adjusting hcmcampaign.h and hcmcampaign.cpp until all tests pass.

📂 Project Structure
```
│── .vscode/ # VS Code configuration files
│ ├── c_cpp_properties.json
│ ├── launch.json
│ └── settings.json
│
│── include/ # Header files (.h)
│ ├── hcmcampaign.h
│ └── main.h
│
│── src/ # Source files (.cpp)
│ └── hcmcampaign.cpp
│
│── test/ # Unit tests
│ ├── unit_test_Task4/
│ │ └── test_case/ # Test case files
│ │
│ ├── unit_test_Task4.cpp
│ ├── unit_test_Task4.hpp
│ ├── unit_test.cpp
│ └── unit_test.hpp
│
│── LICENSE # License information
│── main.cpp # Main source file
│── main.hpp # Header for main
│── main.exe # Windows executable
│── main # Compiled executable (Linux/macOS)
│── run.bat # Script to compile & run on Windows
│── run.sh # Script to compile & run on Linux/macOS
│── README.md # Project documentation
```

📅 Milestones
Release for the 50th Anniversary (2025).

📜 License
This project is released under the MIT License.
You are free to use, modify, and distribute it with proper attribution.
