# 🏴‍☠️ CodeRun 2025: Pirate's Treasure Hunt

This Django application was built for the **CodeRun 2025 Challenge**. It acts as a companion tool to navigate the "Pirate's Map", interact with the external **Oracle API**, and crack the final 4-digit combination lock of the Treasure Chest.

## 🌟 Key Features

### 1. 🧭 The Oracle Navigator (`/oracle`)
The core of the application. It acts as a bridge between the user and the competition's API servers.
* **Automatic Mapping:** Sends instruction IDs to the external Azure API.
* **Response Parsing:** Automatically saves the API response (Direction, Distance, Description, Risk) into the local database.
* **Error Handling:** Manages 405/404 errors and connection timeouts gracefully.

### 2. 🔐 Treasure Chest Cracker
A specialized logic triggers **only** when the Oracle returns a description containing the word *"treasure"*.
* **Boss Fight Mode:** Reveals a 4-digit keypad UI (`TreasureChestForm`).
* **Brute-force Logger:** Every code attempt is logged in the database with `Risk Level: 100` to track trial history.
* **Validation:** Sends the 4-digit code (`digit1`...`digit4`) to the external check-endpoint to verify if the chest opens.

### 3. 📜 The Compass & Journal (`/compass`)
* **Journey Log:** Displays all collected instructions in a chronological list.
* **Data Persistence:** Uses SQLite to ensure no progress is lost if the server restarts.

### 4. 📊 Path Analytics (Smart Detail View)
* **Recursive Tracking:** Uses a **Linked List** structure in the database (`previous_instruction` ForeignKey to `self`).
* **Summary Engine:** When viewing a specific instruction, the app can backtrack through the entire chain to calculate:
    * **Total Distance Traveled** (Sum of all previous nodes).
    * **Average Risk Level** of the path taken.

## 🛠️ Tech Stack

* **Backend:** Python 3.x, Django
* **Database:** SQLite (Default)
* **External Integration:** Python `requests` library (REST API)
* **Architecture:** MVT (Model-View-Template)

## 📦 Database Structure (`models.py`)

The `Instruction` model is designed to handle the competition's specific data types:

| Field | Type | Purpose |
| :--- | :--- | :--- |
| `direction` | Enum | N, S, E, W, NE, NW, SE, SW, None |
| `distance` | Integer | Distance in km/miles |
| `risk_level` | Integer (0-100) | Danger level of the step |
| `previous_instruction` | OneToOne | Links to the previous step (Chain logic) |

## 🚀 How to Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/YOUR_USERNAME/coderun-pirates.git](https://github.com/YOUR_USERNAME/coderun-pirates.git)
    cd coderun-pirates
    ```

2.  **Install dependencies:**
    ```bash
    pip install django requests
    ```

3.  **Migrate the database:**
    ```bash
    python manage.py makemigrations
    python manage.py migrate
    ```

4.  **Run the server:**
    ```bash
    python manage.py runserver
    ```

5.  **Access the tool:**
    Open `http://127.0.0.1:8000/oracle` to start hunting.

## 🎮 Usage Guide

1.  **Start:** Go to the **Oracle** page.
2.  **Input:** Enter the Instruction ID you received (or start with the initial one).
3.  **Navigate:** The app will fetch the next step from the Azure Pirate Server and save it.
4.  **Analyze:** Use the **Compass** to see your full path.
5.  **The End:** When the description says "Treasure is found", the **Code Cracker** appears. Enter the 4 digits to claim victory.

---
*Built for CodeRun 2025.*
