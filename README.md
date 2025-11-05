# 🏦 BANK MANAGEMENT SYSTEM (C++)

A **simple yet powerful console-based Bank Management System** built using **C++** and **file handling**.  
This system allows users to **create, view, modify, and delete bank accounts**, as well as perform **deposit and withdrawal operations** — all securely stored in a **binary file** for persistent data management.

---

## 🚀 Features

✅ **Create New Account** — Add new users with unique account numbers, names, and initial balances.  
💰 **Deposit / Withdraw Money** — Seamlessly update and manage account balances.  
📄 **Balance Enquiry** — Instantly check your account details and current balance.  
🧾 **View All Accounts** — Display a complete list of all account holders with their balances.  
🧹 **Modify or Delete Accounts** — Update account details or close accounts permanently.  
💾 **File-Based Data Storage** — All data is securely stored in a binary file (`account.dat`) for persistence.

---

## ⚙️ How It Works

The program uses **Object-Oriented Programming (OOP)** principles and **Binary File Handling** to simulate a basic yet realistic banking environment.  

It provides a simple **menu-driven interface** for users to interact with their accounts and perform operations efficiently.

---

## 🔍 Core Class: `Account`

### 🧩 Attributes:
- `accountNumber` → Unique ID for each account  
- `name` → Account holder’s name  
- `balance` → Current balance amount  

### ⚒️ Methods:
- `createAccount()` → Creates and stores a new account.  
- `showAccount()` → Displays account details.  
- `modifyAccount()` → Updates account holder’s information.  
- `deposit()` / `withdraw()` → Handles money transactions.  

---

## 📂 File Structure

```bash
.
├── main.cpp               # Main source code file (your provided code)
├── account.dat            # Binary file storing all account details (auto-created)
└── README.md              # Project documentation
