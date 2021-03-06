﻿#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <typeinfo>
#include <string> 
#include <stdio.h>
#include <algorithm>
#include <windows.h>

using namespace std;

bool is_digits(const string& str) // Funkcija, kas izslēdz burtus un citas rakstzīmes, lasot datus no tastatūras.
{
    return all_of(str.begin(), str.end(), isdigit);
}

char Mass[255] = ""; // Global variables
string currency;
string transactionType;
string accountNum;
string amount;
string date;
string transTime;
string line;
string logs;
SYSTEMTIME st;

void curr() { // Valūtas aprēķināšana

    ifstream file("Transaction.txt");
    
    if (file.is_open())
    {
        while (getline(file, line)) {

            if (Mass[44] == '8' && Mass[45] == '4' && Mass[46] == '0' && line == "usd") {
                currency = "usd";
                logs = logs +"Currency value: usd\n";
               // cout << currency << endl;
                return;
            }
            else if (Mass[44] == '9' && Mass[45] == '7' && Mass[46] == '8' && line == "eur") {
                currency = "eur";
                logs = logs + "Currency value: eur\n";
               // cout << currency << endl;
                return;
            }
            else if (Mass[44] == '8' && Mass[45] == '2' && Mass[46] == '6' && line == "gbp") {
                currency = "gbp";
                logs = logs + "Currency value: gbp\n";
               // cout << currency << endl;
                return;
            }
            else if (Mass[44] == '6' && Mass[45] == '4' && Mass[46] == '3' && line == "rub") {
                currency = "rub";
                logs = logs + "Currency value: rub\n";
               // cout << currency << endl;
                return;
            }
        }
    }
    else {
        cout << "Invalid file path" << endl;
        logs = logs + "Invalid file path\n";
    }
    file.close();
}

void transact() { // Transakcijas tipa aprēķināšana

    ifstream file("Transaction.txt");

    if (file.is_open())
    {
        while (getline(file, line)) {

            if (Mass[0] == '0' && Mass[1] == '0' && line == "purchase") {
                transactionType = "purchase";
                logs = logs + "Transaction type: purchase\n";
                // cout << transactionType << endl;
                return;
            }
            else if (Mass[0] == '0' && Mass[1] == '1' && line == "withdrawal") {
                transactionType = "withdrawal";
                logs = logs + "Transaction type: withdrawal\n";
               // cout << transactionType << endl;
                return;
            }
        }
    }
    else {
        cout << "Invalid file path" << endl;
        logs = logs + "Invalid file path\n";
    }
    file.close();
}

void accNum() { // Akaunta numura aprēķināšana

    int i;

    for (int i = 2; i < 18; i++) {

        accountNum += Mass[i];
    }

    int len = accountNum.length(); // Šifrēšana

    for (int i = 0; i < len * 0.75; ++i)
    {
        if (accountNum[i] == '1' || accountNum[i] == '2' || accountNum[i] == '3' || accountNum[i] == '4' || accountNum[i] == '0' || accountNum[i] == '5'
            || accountNum[i] == '6' || accountNum[i] == '7' || accountNum[i] == '8' || accountNum[i] == '9')
            accountNum[i] = '*';
    }
    logs = logs + "Account number: " + accountNum + "\n";
   // cout << accountNum << endl;
}

void amountSub() { // Summa

    int i;

    for (int i = 18; i < 30; i++) {

        amount += Mass[i];
    }

    amount.insert(10, string("."));
    amount.erase(0, min(amount.find_first_not_of('0'), amount.size() - 1)); // функция удаления нулей перед суммой.  

    logs = logs + "Amount value: " + amount + "\n";
   // cout << amount << endl;
}

void tDate() { // Data

    int i;

    for (int i = 34; i <= 35; i++) {

        date += Mass[i];
    }

    for (int i = 36; i <= 37; i++) {

        date += Mass[i];
    }

    for (int i = 30; i < 34; i++) {

        date += Mass[i];
    }

    date.insert(2, string("."));
    date.insert(5, string("."));

    logs = logs + "Date value: " + date + "\n";

   // cout << date << endl;
}

void tTime() { // Laiks

    int i;

    for (int i = 38; i < 42; i++) {

        transTime += Mass[i];
    }

    transTime.insert(2, string(":"));

    logs = logs + "Transaction time: " + transTime + "\n";

   // cout << transTime << endl;
} 

void messageFile() { // message faila radīšana

    GetLocalTime(&st);

    string path = "messageFile.xml";

    ofstream file;
    
    file.open(path);

    if (!file.is_open())
    {
        cout << "Unable to create file"<< endl;
    }
    else {
        file << "<root>\n<msg-list>\n    <msg>"<< transactionType << " with card " << accountNum << " on " << date << " " << transTime << ",\n" << 
          "amount " << amount << " " << currency << ".</msg>\n" << "</msg-list>\n" << "<totals cnt='1' " << "sum='" << amount << "' " <<
            "date='" << st.wYear << ".0" << st.wMonth << "." << st.wDay << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << "'/>\n"<< "</root>" << endl;
    }
    file.close();
    logs = logs + "Message file created\n";
} 

void logFile() {

    int a = st.wYear; // Variables for date and time
    string year = to_string(a);
    int b = st.wMonth;
    string month = to_string(b);
    int c = st.wDay;
    string day = to_string(c);
    int d = st.wHour;
    string hour = to_string(d);
    int e = st.wMinute;
    string minute = to_string(e);
    int f = st.wSecond;
    string second = to_string(f);
    int g = st.wMilliseconds;
    string milliseconds = to_string(g); 

    string address = "trn2msg" + year + month + day + ".log";
    ofstream file;
    logs = logs + hour + ":" + minute + ":" + second + ":" + milliseconds + " - Log file created\n";

    file.open(address);

    file << logs << endl;

    file.close();
}

void main()
{
    setlocale(LC_ALL, "");

    string counter;

    cin >> counter;

    if (is_digits(counter) == true && counter.size() == 47) { // Pārbaude ciparus
    }
     else {
        cout << "Please enter 47 numbers" << endl;
        exit(0);
    }
    strcpy_s(Mass, counter.c_str());

    logs = logs + "User entered transaction information\n";

    curr();
    transact();
    accNum();
    amountSub();
    tDate();
    tTime();
    messageFile();
    
    cout << "<root>\n<msg-list>\n    <msg>" << transactionType << " with card " << accountNum << " on " << date << " " << transTime << ",\n" <<
        "amount " << amount << " " << currency << ".</msg>\n" << "</msg-list>\n" << "<totals cnt='1' " << "sum='" << amount << "' " <<
        "date='" << st.wYear << ".0" << st.wMonth << "." << st.wDay << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << "'/>\n" << "</root>" << endl;
    
    logs = logs + "The user received information about the transaction\n";

    logFile();

    system("PAUSE");
}



