#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cctype>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <numeric>
using namespace std;

int written = 0;
void menu();
string createLuhnAccountNo();
string createAccountPin();
string Search(string, int);
void listDetails(string, string);
vector<string> splitStr(string, char);
void backOrAbort();

// Formatting
void printh(string heading)
{
    cout << ">>  " << heading << "--"
         << "\n\n";
}

void printm(string msg)
{
    cout << "\n";
    int l = msg.length();
    for (int i = 0; i < l / 2 + 2; i++)
    {
        cout << "-~";
    }
    cout << "\n| " << msg << " |\n";
    for (int i = 0; i < l / 2 + 2; i++)
    {
        cout << "--";
    }
    cout << "\n\n";
}

void printo(int sno, string val)
{
    cout << "[" << sno << "] " << val << "\t\t";
    cout << endl;
}

void printd(string data, int index = 0)
{
    if (!index)
    {
        cout << " - " << data << " : ";
    }
    else
    {
        cout << " - " << data << " " << index << " : ";
    }
}

string tolower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

string itos(int val)
{
    string res = to_string(val);
    return res;
}

int stoi(string str)
{
    stringstream res(str);
    int x = 0;
    res >> x;
    return x;
}

void clrscr()
{
    system("cls");
}

void delay(unsigned int ms)
{
    clock_t goal = ms + clock();
    while (goal > clock())
        ;
}

void abort()
{
    printm("Thanks for using our banking application!");
    delay(2000);
    exit(0);
}

struct Account
{
    string name;
    string account_number;
    string account_pin;
    string branch;
    string account_type;
    unsigned int balance;
};

class Accounts
{
public:
    Account a;
    int total = 0;

    Accounts(string name = "undefined", string branch = "undefined", string account_type = "undefined", unsigned int balance = 0)
    {
        a.name = name;
        a.account_number = "00000000000000";
        a.account_pin = "0000";
        a.branch = branch;
        a.account_type = account_type;
        a.balance = balance;

        total++;
        written = 1;
    }

    void input()
    {
        clrscr();
        printh("Enter your basic details");

        printd("Name");
        cin >> a.name;
        cout << endl;

        printd("Branch Name");
        cin >> a.branch;
        cout << endl;

        printd("A/C type (Savings or Current)");
        cin >> a.account_type;
        cout << endl;

        printd("A/C balance");
        cin >> a.balance;
        cout << endl;

        printm("Your input has been recorded. Complete A/C detail will be displayed shortly");
    }
    void create()
    {
        a.account_number = createLuhnAccountNo();
        a.account_pin = createAccountPin();
    }
    void display()
    {
        clrscr();
        printh("Your A/C details are as follows");

        printd("Name");
        cout << a.name << endl;

        printd("Account number");
        for (int i = 0; i < 16; i++)
        {
            cout << a.account_number[i];
        }
        cout << endl;

        printd("Account pin");
        for (int i = 0; i < 4; i++)
        {
            cout << a.account_pin[i];
        }
        cout << endl;

        printd("Branch name");
        cout << a.branch << endl;

        printd("Account type");
        cout << a.account_type << endl;

        printd("Balance amount");
        cout << a.balance << endl;

        delay(10000);
        clrscr();
        printm("What next?");

        int c = 0;

        printo(1, "Login");
        printo(2, "Save and Go Back");
        printo(3, "Go Back without saving");
        printo(0, "Press any other key to abort");

        cout << "\n\n";
        printd("Enter your choice");
        cin >> c;

        switch (c)
        {
        case 1:
        {
            save();
            check();
            break;
        }
        case 2:
        {
            save();
            menu();
            break;
        }
        case 3:
        {
            menu();
            break;
        }
        default:
            abort();
            break;
        }
    }

    void save()
    {
        fstream fout;
        fout.open("Account.txt", ios::app);
        fout << a.name;
        fout << " ";
        fout << a.account_number;
        fout << " ";
        fout << a.account_pin;
        fout << " ";
        fout << a.branch;
        fout << " ";
        fout << a.account_type;
        fout << " ";
        fout << a.balance;
        fout << " ";
        fout << "\n";

        fout.close();
        printm("New A/C data saved successfully.");
        delay(2000);
    }

    void check()
    {
        clrscr();
        string input_ac_no;
        string input_ac_pin;
        printh("Enter following details to log in");
        printd("A/C number");
        cin >> input_ac_no;
        cout << endl;

        printd("A/C pin");
        cin >> input_ac_pin;
        cout << endl;

        fstream file;
        file.open("Account.txt", ios::in);

        string ac_no = Search(input_ac_no, 0);
        string ac_pin = Search(input_ac_pin, 0);

        file.close();

        bool found_no = false;
        bool found_pin = false;

        if (ac_no != "")
            found_no = true;
        if (ac_pin != "")
            found_pin = true;

        // cout << ac_no;
        // cout << ac_pin;

        if (found_no && found_pin)
        {
            int login_choice;
            printm("You have successfully logged in!");
            delay(4000);
            clrscr();

            printh("Logged In");
            cout << "\n\n";
            printo(1, "Read A/C details");
            printo(2, "Update A/C details");
            printo(3, "Delete A/C");
            printo(0, "Press any other key to abort");
            cout << "\n";
            printd("Choose your next step");
            cin >> login_choice;

            switch (login_choice)
            {
            case 1:
            {
                listDetails(ac_no, ac_pin);
                break;
            }
            case 2:
            {
                string prev, rep;
                printd("Enter value of item to be replaced");
                cin >> prev;
                printd("Enter updated value");
                cin >> rep;
                if (isdigit(prev[0]) || isdigit(rep[0]))
                    printm("Request denied : A/C number, A/C pin, balance cannot be updated");
                updateAcc(prev, rep);
                abort();
                break;
            }
            case 3:
            {
                string ac_name;
                cout << "\n\n";
                printd("Enter name to confirm A/C DELETION");
                cin >> ac_name;
                deleteAcc(ac_name);
                break;
            }
            default:
                abort();
            }
        }

        else
        {
            int ch;
            printh("Wrong A/C number or A/C pin");
            cout << "\n\n";
            printo(1, "Retry");
            printo(0, "Exit");
            cout << "\n";
            printd("Choose from given options");
            cin >> ch;

            switch (ch)
            {
            case 1:
                check();
                break;
            default:
                abort();
            }
        }
    }
    void deleteAcc(string ac_name_val)
    {
        string line;
        ifstream file;
        file.open("Account.txt");
        ofstream temp;
        temp.open("temp.txt");
        while (getline(file, line))
        {
            if (line.substr(0, ac_name_val.length()) != ac_name_val)
                temp << line << endl;
        }
        file.close();
        temp.close();

        remove("Account.txt");
        rename("temp.txt", "Account.txt");

        printm("Account has been deleted");
        cout << "\n\n";
        backOrAbort();
    }
    void updateAcc(string prev, string rep)
    {
        fstream file;
        file.open("Account.txt", ios::in);
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(prev, 0);
            if (pos != string::npos)
            {
                line.replace(pos, prev.length(), rep);
            }
        }
        file.close();

        printm("Value updated");
        cout << "\n\n";
        backOrAbort();
    }
};

string Search(string ss, int index)
{
    fstream file;
    int pos = 0;
    file.open("Account.txt", ios::in);
    string ch;
    string data = "";
    bool found = false;
    int i = 0;
    while (file >> ch)
    {
        if (isdigit(ch[0]))
        {
            if (found)
                break;
            else
            {
                pos++;
                data = "";
                i = 0;
            }
        }
        data += ch;
        data += " ";
        if (ss == ch)
        {
            found = true;
            goto label;
        }
        i++;
    }

label:
    if (!found)
        return "";
    file.close();

    return data;
}

void backOrAbort()
{
    int ch;
    printh("What next?");
    cout << "\n";
    printo(1, "Go Back");
    printo(0, "Exit");
    cout << "\n";
    printd("Choose from given options");
    cin >> ch;

    switch (ch)
    {
    case 1:
        menu();
        break;
    default:
        abort();
    }
}

vector<string> splitStr(string str, char dl)
{
    string word = "";
    int n = 0;
    str = str + dl;
    int l = str.length();
    vector<string> substr;
    for (int i = 0; i < l; i++)
    {
        if (str[i] != dl)
        {
            word = word + str[i];
        }
        else
        {
            if ((int)word.length() != 0)
                substr.push_back(word);

            word = "";
        }
    }
    return substr;
}

void listDetails(string ac_no, string ac_pin)
{
    clrscr();
    string attr_val;
    string attr[6] = {"Name", "A/C Number", "A/C Pin", "A/C Branch", "A/C Type", "Balance"};
    cout << "\n";
    fstream file;
    file.open("Account.txt", ios::in);
    string line;
    while (getline(file, line))
    {
        size_t pos = line.find(ac_no);
        if (pos != string::npos)
            attr_val = line;
    }
    char dl = ' ';
    vector<string> substr = splitStr(attr_val, dl);

    for (int i = 0; i < 6; i++)
    {
        cout << attr[i] << " : " << substr[i] << endl;
    }

    cout << "\n\n";
    backOrAbort();
}

void reverseStr(string &str)
{
    int l = str.length();
    for (int i = 0; i < l / 2; i++)
    {
        swap(str[i], str[l - i - 1]);
    }
}

string createLuhnAccountNo()
{
    srand(time(NULL));
    int check_sum;
    int sum = 0;
    string ac_no_str = "400000";

    for (int i = ac_no_str.length(); i <= 14; i++)
    {
        int random = (rand() % 10);
        ac_no_str += itos(random);
    }
    reverseStr(ac_no_str);
    for (int i = 0; i < ac_no_str.length(); i += 2)
    {
        sum = sum + (ac_no_str[i] * 2);
    }
    for (int i = 1; i < ac_no_str.length(); i += 2)
    {
        sum += ac_no_str[i];
    }

    int mod = sum % 10;
    if (mod == 0)
        check_sum = 0;
    else
        check_sum = (10 - mod);

    reverseStr(ac_no_str);

    ac_no_str += itos(check_sum);
    return ac_no_str;
}
string createAccountPin()
{
    srand(time(NULL));
    string pin_str;
    for (int i = 0; i < 4; i++)
    {
        int random = (rand() % 10);
        pin_str += itos(random);
    }
    return pin_str;
}

void menu()
{
    clrscr();
    Accounts ac;

    printm("S I M P L E   B A N K I N G   S Y S T E M");
    printh("Menu");

    printo(1, "Create new A/C");
    printo(2, "LogIn to A/C");
    printo(3, "Exit interface");

    cout << "\n\n";
    int choice = 0;
    printd("Enter your choice");
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        ac.input();
        ac.create();
        cout << "Creating A/C...";
        delay(4000);
        ac.display();
        break;
    }
    case 2:
    {
        ac.check();
        printd("Checking A/C...");
        delay(4000);
        break;
    }
    case 3:
    {
        abort();
        break;
    }
    default:
    {
        printm("Please enter in range [1-3]!");
        delay(2000);
        menu();
    }
    }
}

int main()
{
    menu();
    return 0;
}