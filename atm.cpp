#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>
#include <chrono>
#include <ctime>
#include <algorithm>

class Transaction {
public:
    std::string date;
    std::string type;
    double amount;
    
    Transaction(const std::string& date,const std::string& type, double transAmount)
        : date(date), type(type), amount(transAmount) {}  // Corrected constructor
};

class Account {
public:
    int account_no;
    std::string password;
    double balance;
    std::vector<Transaction> transactions;
   
    static int next_account_no;
    static std::string default_password;
    
    
    Account(double initial_balance)
        : account_no(next_account_no++), password(default_password), balance(initial_balance) {}
};
    
//Initialize account num and password
int Account::next_account_no = 1;  
std::string Account::default_password = "123";

//clean the screen
void clearScreen() {
    // Clear the screen,linux use "clear"
    //system("clear") for linux
    system("cls");
}

//Get current time
std::string ctime() {
    
  std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::string time = std::ctime(&currentTime);

  // Remove the trailing newline character
  time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());

  return time;
}

int main(){
    std::vector<Account> mainlist;
    std::vector<Transaction> transHistory;
    int account_no;
    std::string password;
    int option;
    
    //create 10 accounts.
    for(int i=0;i<10;i++){
    mainlist.push_back(Account(5000));
    
    }
    
    //first page
    std::cout<<"Login Window:\n"<<"=============\n"<<"Enter your Account no:\n"<<std::endl;
    std::cin >> account_no;
    std::cout<<"Enter your password\n"<<std::endl;
    std::cin >> password;
    
    //verify account number and password.
    while(1>account_no || account_no<10 && password!="123"){
        clearScreen();
        std::cout<<"Login Window:\n"<<"=============\n"<<"Enter your Account no:\n"<<std::endl;
        std::cin >> account_no;
        std::cout<<"Enter your password\n"<<std::endl;
        std::cin >> password;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
        
        
        //second page, let user choose options
        while(true){
          clearScreen();
        std::cout<<"Main Window\n"<<"=============\n"<<"Choose one of the following options:\n"<<
        "(1)Show balance\n"<<"(2)Show Deposit\n"<<"(3)Withdrwaw\n"<<"(4)Show All Transactions\n"
        <<"Enter your choice:\n"<<std::endl;
           std::cin>> option;

           //Show balance
           if(option == 1){
              clearScreen();
              std::cout << "Main Window-->Show Balance\n"<<"==============================================="<<std::endl;
              std::cout << "Your current Balance is: " << mainlist[account_no - 1].balance << "\n";
              
              std::cout << "-----------------------------------------------";
              std::cout << "Press Enter to continue...";
              std::cin.get();
           }
          
           
           //Deposit
           if(option == 2){
              double deposit;
              clearScreen();
              std::cout << "Main Window-->Deposit(Enter the following information)\n"<< "===============================================\n"<<
              "The amount you want to deposit: "<<std::endl;
              std::cin >> deposit;
              std::string currentTime = ctime();
              
              std::cout << "-----------------------------------------------\n";
              
              //Deposit must >0
              if(deposit>0){
                transHistory.push_back(Transaction(currentTime," deposit ", deposit));
                mainlist[account_no-1].balance = mainlist[account_no-1].balance + deposit;
              } else{
                std::cout << "Invalid input, please try again." << std::endl;
              }

              std::cout << "Well Done. This was added to your balance successfully...Press Enter to go back to the Main Window";
              std::cin.get();
           }
           
           //Withdraw
           if(option == 3){
              double withdrawNum;
              clearScreen();
              std::cout << "Main Window-->Wtihdraw(Enter the following information)\n"<< "===============================================\n"<<
              "The amount you want to withdraw: "<<std::endl;
              std::cin >> withdrawNum;
              std::string currentTime = ctime();
              
              std::cout << "-----------------------------------------------\n";

              //Withdraw amount cannot exceed current balance and bigger than 0
              if(withdrawNum>0 && withdrawNum <= mainlist[account_no-1].balance){
                transHistory.push_back(Transaction(currentTime," withdraw ", withdrawNum));
                mainlist[account_no-1].balance = mainlist[account_no-1].balance - withdrawNum;
                std::cout << "Please take your money then...Press Enter to go back to the Main Window";
              } else{
                std::cout << "Invalid input, please try again." << std::endl;
                std::cout << "Press Enter to go back to the Main Window";
              }
              std::cin.get();
           }
           

           //Show transaction
           if(option == 4){
              clearScreen();
              std::cout << "Main Window-->Show All Transactions\n"<< "===============================================\n"
              << "Account no: "<< account_no << "\n" <<
              "-----------------------------------------------\n"<< std::endl;
              for(Transaction& trans : transHistory) { // Loop through each transaction
                 std::cout << "Date: " << trans.date << " |Type: " << trans.type << " |Amount: " << trans.amount << std::endl;
                 std::cout << "-----------------------------------------------\n";
              }
              std::cout << "Press Enter to go back to the Main Window";
              std::cin.get();
           }
           
           //if user inputs string or other numbers, clear input and give them new chance.
           if(std::cin.fail())
           { 
             std::cin.clear();
           }
           
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    return 0;
}



