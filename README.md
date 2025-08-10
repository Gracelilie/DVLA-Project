# DVLA Vehicle & Driver Management System

A command-line application built with C++ to simulate a vehicle and driver management system for the Driver and Vehicle Licensing Agency (DVLA). This project demonstrates fundamental Object-Oriented Programming (OOP) principles through the creation and management of driver and vehicle data.

---

## Features

* **Driver & Vehicle Registration:** Register new drivers and vehicles, capturing essential information.
* **Unique ID Generation:** The system automatically generates unique license numbers and vehicle registration plates.
* **License Validity:** Utilizes the `ctime` library to check the validity of driver's licenses based on their issue and expiry dates.
* **License Renewal:** Allows for the renewal of expired licenses, updating the expiry date.
* **Data Persistence (Simulated):** Uses C++ vectors to store and manage all registered data in memory during runtime.

---

## Technologies Used

* **Language:** C++
* **Key Libraries:** `iostream`, `string`, `vector`, `ctime`
* **Concepts:** Object-Oriented Programming (OOP)

---

## How to Run

To get the program up and running on your local machine, follow these simple steps:

1.  **Clone the repository:**
    ```bash
    git clone [your-repository-url]
    ```
2.  **Navigate to the project directory:**
    ```bash
    cd [your-project-folder]
    ```
3.  **Compile the source code with a C++ compiler (e.g., g++):**
    ```bash
    g++ main.cpp -o dvla_system
    ```
    (Note: Replace `main.cpp` with the name of your source file.)
4.  **Execute the program:**
    ```bash
    ./dvla_system
    ```
