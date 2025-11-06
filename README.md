```markdown
# 🏦 Bank Management System in C

A simple **Bank Management System** built using **C language**.  
This project demonstrates the use of **file handling**, **structures**, and **basic data operations** in C to manage customer accounts effectively.

---

## 📘 Project Overview

This is a console-based application that allows a bank employee (or admin) to perform operations such as creating new accounts, updating details, depositing or withdrawing money, and deleting accounts.  
All account information is securely stored in a binary file (`bank.dat`), ensuring data persistence between sessions.

---

## ⚙️ Features

✅ Create a new bank account  
✅ Display all accounts  
✅ Search account by account number  
✅ Deposit money into an account  
✅ Withdraw money with balance check  
✅ Modify account details (name, balance, password)  
✅ Delete an account securely  
✅ Password-protected transactions  
✅ File-based data storage (`bank.dat`)

---

## 🧩 Technologies Used

- **Language:** C  
- **IDE/Editor:** VS Code / Code::Blocks / Dev-C++  
- **Concepts:** File Handling, Structures, Functions, Pointers

---

## 🗂️ Project Structure

```

Bank-Management-System-C/
│
├── bank.c          # Main source code file
├── bank.dat        # Data file (auto-generated)
├── README.md       # Project documentation
└── .gitignore      # (optional) to exclude compiled files

````

---

## 💻 How to Run

1. **Clone this repository**
   ```bash
   git clone https://github.com/your-username/Bank-Management-System-C.git
````

2. **Navigate to the project folder**

   ```bash
   cd Bank-Management-System-C
   ```
3. **Compile the program**

   ```bash
   gcc bank.c -o bank
   ```
4. **Run the executable**

   ```bash
   ./bank
   ```

---

## 📸 Sample Output

```
==================================================
              BANK MANAGEMENT SYSTEM
==================================================
1. Create New Account
2. Display All Accounts
3. Search Account by Number
4. Deposit Money
5. Withdraw Money
6. Modify Account
7. Delete Account
8. Exit
--------------------------------------------------
Enter your choice:
```

---

## 🔒 Security Features

* Each transaction requires a **password** to prevent unauthorized access.
* Data stored in a **binary file** prevents easy tampering.
* Deleted accounts are safely removed by marking and rewriting data files.

---

## 🚀 Future Enhancements

* Add interest calculation system
* Introduce admin login & roles
* Implement transaction history
* Create a GUI version using Python or C++

---

## 🧑‍💻 Author

**Laxya Gaba**
📧 [laxya@example.com](mailto:gabalaxya108@gmail.com)
📍 [GitHub Profile](https://github.com/laxxxgaba/bank-management-system-in-c)

---

```
```
