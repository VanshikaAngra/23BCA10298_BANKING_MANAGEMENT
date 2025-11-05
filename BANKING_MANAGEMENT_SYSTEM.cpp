#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Account
{
private:
  int accountNumber;
  char name[50];
  double balance;

public:
  // Function to create a new account
  void createAccount()
  {
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter Initial Balance: ";
    cin >> balance;
    cout << "\nAccount Created Successfully!\n";
  }

  // Display account details
  void showAccount() const
  {
    cout << "\nAccount Number: " << accountNumber;
    cout << "\nAccount Holder Name: " << name;
    cout << "\nBalance: " << balance << endl;
  }

  // Modify account details
  void modifyAccount()
  {
    cout << "\nAccount Number: " << accountNumber;
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Modify Balance: ";
    cin >> balance;
  }

  // Deposit and withdraw methods
  void deposit(double amount)
  {
    balance += amount;
    cout << "\nAmount Deposited Successfully!";
  }

  void withdraw(double amount)
  {
    if (amount <= balance)
    {
      balance -= amount;
      cout << "\nAmount Withdrawn Successfully!";
    }
    else
    {
      cout << "\nInsufficient Balance!";
    }
  }

  // Getter functions
  int getAccountNumber() const { return accountNumber; }
  double getBalance() const { return balance; }
  string getName() const { return name; }
};

// Function declarations
void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositWithdraw(int, int);

int main()
{
  int choice;
  int num;

  do
  {
    cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
    cout << "\n1. Create New Account";
    cout << "\n2. Deposit Amount";
    cout << "\n3. Withdraw Amount";
    cout << "\n4. Balance Enquiry";
    cout << "\n5. All Account Holder List";
    cout << "\n6. Close an Account";
    cout << "\n7. Modify an Account";
    cout << "\n8. Exit";
    cout << "\n\nSelect Your Option (1-8): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      writeAccount();
      break;
    case 2:
      cout << "\nEnter Account Number: ";
      cin >> num;
      depositWithdraw(num, 1);
      break;
    case 3:
      cout << "\nEnter Account Number: ";
      cin >> num;
      depositWithdraw(num, 2);
      break;
    case 4:
      cout << "\nEnter Account Number: ";
      cin >> num;
      displayAccount(num);
      break;
    case 5:
      displayAll();
      break;
    case 6:
      cout << "\nEnter Account Number: ";
      cin >> num;
      deleteAccount(num);
      break;
    case 7:
      cout << "\nEnter Account Number: ";
      cin >> num;
      modifyAccount(num);
      break;
    case 8:
      cout << "\nThank You for Using Bank Management System!" << endl;
      break;
    default:
      cout << "\nInvalid Choice!";
    }
  } while (choice != 8);

  return 0;
}

// Write new account to file
void writeAccount()
{
  Account acc;
  ofstream outFile("account.dat", ios::binary | ios::app);
  acc.createAccount();
  outFile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
  outFile.close();
}

// Display a single account
void displayAccount(int n)
{
  Account acc;
  bool found = false;
  ifstream inFile("account.dat", ios::binary);
  if (!inFile)
  {
    cout << "\nFile could not be opened!";
    return;
  }
  cout << "\nACCOUNT DETAILS\n";
  while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account)))
  {
    if (acc.getAccountNumber() == n)
    {
      acc.showAccount();
      found = true;
    }
  }
  inFile.close();
  if (!found)
    cout << "\nAccount not found!";
}

// Modify existing account
void modifyAccount(int n)
{
  bool found = false;
  Account acc;
  fstream File("account.dat", ios::binary | ios::in | ios::out);
  if (!File)
  {
    cout << "\nFile could not be opened!";
    return;
  }

  while (!File.eof() && found == false)
  {
    File.read(reinterpret_cast<char *>(&acc), sizeof(Account));
    if (acc.getAccountNumber() == n)
    {
      acc.showAccount();
      acc.modifyAccount();
      int pos = (-1) * static_cast<int>(sizeof(Account));
      File.seekp(pos, ios::cur);
      File.write(reinterpret_cast<char *>(&acc), sizeof(Account));
      cout << "\nAccount Updated Successfully!";
      found = true;
    }
  }
  File.close();
  if (!found)
    cout << "\nAccount not found!";
}

// Delete an account
void deleteAccount(int n)
{
  Account acc;
  ifstream inFile("account.dat", ios::binary);
  ofstream outFile("temp.dat", ios::binary);
  if (!inFile)
  {
    cout << "\nFile could not be opened!";
    return;
  }

  while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account)))
  {
    if (acc.getAccountNumber() != n)
      outFile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
  }

  inFile.close();
  outFile.close();
  remove("account.dat");
  rename("temp.dat", "account.dat");
  cout << "\nAccount Deleted Successfully!";
}

// Display all account holders
void displayAll()
{
  Account acc;
  ifstream inFile("account.dat", ios::binary);
  if (!inFile)
  {
    cout << "\nFile could not be opened!";
    return;
  }

  cout << "\n\nACCOUNT HOLDER LIST\n";
  cout << "-----------------------------------------------\n";
  cout << left << setw(15) << "Acc No"
       << setw(25) << "Name"
       << setw(15) << "Balance" << endl;
  cout << "-----------------------------------------------\n";

  while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account)))
  {
    cout << left << setw(15) << acc.getAccountNumber()
         << setw(25) << acc.getName()
         << setw(15) << acc.getBalance() << endl;
  }

  inFile.close();
}

// Deposit or withdraw
void depositWithdraw(int n, int option)
{
  double amount;
  bool found = false;
  Account acc;
  fstream File("account.dat", ios::binary | ios::in | ios::out);
  if (!File)
  {
    cout << "\nFile could not be opened!";
    return;
  }

  while (!File.eof() && found == false)
  {
    File.read(reinterpret_cast<char *>(&acc), sizeof(Account));
    if (acc.getAccountNumber() == n)
    {
      acc.showAccount();
      if (option == 1)
      {
        cout << "\nEnter amount to deposit: ";
        cin >> amount;
        acc.deposit(amount);
      }
      else if (option == 2)
      {
        cout << "\nEnter amount to withdraw: ";
        cin >> amount;
        acc.withdraw(amount);
      }
      int pos = (-1) * static_cast<int>(sizeof(Account));
      File.seekp(pos, ios::cur);
      File.write(reinterpret_cast<char *>(&acc), sizeof(Account));
      cout << "\nRecord Updated!";
      found = true;
    }
  }
  File.close();
  if (!found)
    cout << "\nAccount not found!";
}