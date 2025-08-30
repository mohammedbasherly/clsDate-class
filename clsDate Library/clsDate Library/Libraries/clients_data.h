#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "C:\Programming\Libraries\global_funcs.h"
#include "C:\Programming\Libraries\matrix_lib.h"

using namespace global_funcs;
using namespace matrix_lib;

#include "C:\Programming\Libraries\funcs.h"
using namespace funcs;

enum enPermissions
{
    fullAccess = -1,
    ClientsList_pr = 1,
    AddNewClient_pr = 2,
    DeleteClient_pr = 4,
    UpdateClient_pr = 8,
    FindClient_pr = 16,
    Transactions_pr = 32,
    ManageUsers_pr = 64
};

struct stUser
{
    string username = "";
    string password = "";
    short permissions = -1;
};


namespace clients_data {
    //const string clientsFilePath = "clients.txt";

    struct stClinetData {
        string  accountNumber = "";
        string pinCode = "";
        string fullName = "";
        string phone = "";
        float accountBalance = -1;
    };

    stClinetData readClientData(string accountNumber = "", string msg = "")
    {
        stClinetData clientData;

        cout << msg;
        if (accountNumber == "")
            clientData.accountNumber = readString("Account Number: ");
        else
            clientData.accountNumber = accountNumber;

        clientData.pinCode = readString("Pin code: ");
        clientData.fullName = readString("Full Name: ");
        clientData.phone = readString("Phone Number: ");
        clientData.accountBalance = funcs::readFloatNumber("Account Balance: ");

        return clientData;
    }

    string convertClientDataRecordToLine(stClinetData& clientData, string delim = "#//#")
    {
        string record = "";

        record += clientData.accountNumber + delim;
        record += clientData.pinCode + delim;
        record += clientData.fullName + delim;
        record += clientData.phone + delim;
        record += to_string(clientData.accountBalance);

        return record;
    }

    stClinetData convertLineToClientDataRecord(string text, string delim = "#//#")
    {
        stClinetData clientData;

        vector<string> vTokens = splitStringIntoVector(text, delim);

        clientData.accountNumber = vTokens[0];
        clientData.pinCode = vTokens[1];
        clientData.fullName = vTokens[2];
        clientData.phone = vTokens[3];
        clientData.accountBalance = stof(vTokens[4]);

        return clientData;
    }

    void printClientDataCard(stClinetData& clientData)
    {
        cout << "Account Number : " << clientData.accountNumber << endl;
        cout << "Pin code       : " << clientData.pinCode << endl;
        cout << "Full Name      : " << clientData.fullName << endl;
        cout << "Phone Number   : " << clientData.phone << endl;
        cout << "Account Balance: " << clientData.accountBalance << endl;
    }

    vector<stClinetData> readClientsData()
    {
        vector<stClinetData> vClientsData;
        char addMore = 'y';
        short i = 0;

        cout << endl;
        do
        {
            i++;
            cout << "- Client " << i << " ...";
            vClientsData.push_back(readClientData());
            cout << endl;

            cout << "Client " << i << " is added successfully, do you want to add more clients? [y/n]? ";
            addMore = readCharacter();
            cout << endl;
        } while (addMore == 'y' || addMore == 'Y');

        return vClientsData;
    }

    vector<string> convertCLientsDataToLines(vector<stClinetData>& vClientsData)
    {
        vector<string> clientsDataLines;

        string* ptr;
        ptr = new string;
        *ptr = "";

        for (stClinetData& client : vClientsData)
        {
            *ptr = convertClientDataRecordToLine(client);
            clientsDataLines.push_back(*ptr);
        }
        delete ptr;

        return clientsDataLines;
    }

    void printClientsDataLines(vector<string>& lines)
    {
        for (string& line : lines)
        {
            cout << line << endl;
        }
    }

    void uploadClientsDataLinesToFile(string filePath, vector<string> lines, bool overwrite = false)
    {
        fstream file;
        if (overwrite)
            file.open(filePath, ios::out);
        else
            file.open(filePath, ios::out | ios::app);

        for (string& line : lines)
        {
            file << line << endl;
        }
        file.close();
    }

    void uploadClientDataLineToFile(string filePath, string line)
    {
        fstream file;
        file.open(filePath, ios::out | ios::app);
        file << line << endl;
        file.close();
    }

    vector<string> loadFileContentToVector(string filePath)
    {
        vector<string> vFile;

        fstream file;
        file.open(filePath, ios::in);

        string* ptrLine;
        ptrLine = new string;

        if (file.is_open())
        {
            while (getline(file, *ptrLine))
            {
                vFile.push_back(*ptrLine);
            }
            file.close();
        }

        delete ptrLine;
        return vFile;
    }

    bool isAccountNumberFound(vector<stClinetData>& vClientsData, string accountNumber)
    {
        for (stClinetData client : vClientsData)
        {
            if (client.accountNumber == accountNumber)
                return true;
        }
        return false;
    }

    bool isAccountNumberFound(string filePath, string accountNumber, string delim = "#//#")
    {
        vector<string> vLines = loadFileContentToVector(filePath);
        for (string& line : vLines)
        {
            line = line.substr(0, line.find(delim));
            if (line == accountNumber)
                return true;
        }
        return false;
    }

    void addNewClient(string filePath, string delim = "#//#")
    {
        string accountNumber;
        do
        {
            accountNumber = readString("Account Number: ");
        } while (accountNumber.length() != 4);
        if (!isAccountNumberFound(filePath, accountNumber))
        {
            stClinetData client = readClientData(accountNumber);
            uploadClientDataLineToFile(filePath, convertClientDataRecordToLine(client, delim));
            cout << "\nClient is added succesfully <3\n";
        }
        else
            cout << "\nAccount Number (" << accountNumber << ") is already existed\n";
    }

    void addNewClients(string filePath, string delim = "#//#")
    {
        char addMore = 'y';
        do
        {
            addNewClient(filePath, delim);
            addMore = readCharacter("do you want to add a new one? [y/n]? ");
        } while (tolower(addMore) == 'y');

    }

    void copyFileContentIntoVector(string& filePath, vector<string>& vFile)
    {
        fstream file;

        file.open(filePath, ios::in);

        string* ptrLine;
        ptrLine = new string;

        if (file.is_open())
        {
            while (getline(file, *ptrLine))
            {
                vFile.push_back(*ptrLine);
            }
            file.close();
        }
    }

    vector<stClinetData> convertLinesToClientsDataRecords(vector<string>& vLines, string delim = "#//#")
    {
        vector<stClinetData> vClientsData;
        for (string& line : vLines)
        {
            vClientsData.push_back(convertLineToClientDataRecord(line, delim));
        }
        return vClientsData;
    }

    void showClientsDataHeader(short size)
    {
        cout << "\n\t\t\t\tClinets List [" << size << " Client(s)]\n";
        cout << " _________________________________________________________________________________________\n\n";
        cout << " | " << left << setw(15) << "AccountNumber";
        cout << " | " << left << setw(10) << "Pin Code";
        cout << " | " << left << setw(25) << "Client Name";
        cout << " | " << left << setw(12) << "Phone Number";
        cout << " | " << left << setw(12) << "Balance";
        cout << "\n _________________________________________________________________________________________\n\n";
    }

    void printClientData(stClinetData& client)
    {
        cout << " | " << left << setw(15) << client.accountNumber;
        cout << " | " << left << setw(10) << client.pinCode;
        cout << " | " << left << setw(25) << client.fullName;
        cout << " | " << left << setw(12) << client.phone;
        cout << " | " << left << setw(12) << client.accountBalance;
    }

    void printClientsData(vector<stClinetData>& vClients)
    {
        for (stClinetData& client : vClients)
        {
            printClientData(client);
            cout << endl;
        }
        cout << " _________________________________________________________________________________________\n\n";
    }

    void showAllClients(string filePath, string delim = "#//#")
    {
        vector<string> vClientsLines = loadFileContentToVector(filePath);
        vector<stClinetData> vClientsData = convertLinesToClientsDataRecords(vClientsLines, delim);
        if (vClientsData.size() != 0)
        {
            showClientsDataHeader(vClientsLines.size());
            printClientsData(vClientsData);
        }
        else
        {
            cout << "\nNo Clients in system yet !\n";
        }
    }

    void showAllClients(vector<stClinetData>& vClientsData)
    {
        showClientsDataHeader(vClientsData.size());
        printClientsData(vClientsData);
    }

    vector<stClinetData> convertClientsDataFileToVector(string filePath, string delim = "#//#")
    {
        vector<string> vClientsLines = loadFileContentToVector(filePath);
        vector<stClinetData> vClientsData = convertLinesToClientsDataRecords(vClientsLines, delim);

        return vClientsData;
    }

    void printClientDataCardByAccountNumber(string filePath, string accountNumber, string delim = "#//#", string msg = "")
    {
        vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
        for (stClinetData client : vClientsData)
        {
            if (client.accountNumber == accountNumber)
            {
                cout << msg << endl;
                printClientDataCard(client);
                return;
            }
        }
        cout << "\nClient with account number (" << accountNumber << ") is not found.\n";
    }

    void printClientDataCardByAccountNumber(vector<stClinetData>& vClientsData, string accountNumber, string msg = "")
    {
        for (stClinetData client : vClientsData)
        {
            if (client.accountNumber == accountNumber)
            {
                cout << msg << endl;
                printClientDataCard(client);
                return;
            }
        }
        cout << "\nClient with account number (" << accountNumber << ") is not found.\n";
    }

    stClinetData getClientByAccountNumber(vector<stClinetData>& vClientsData, string accountNumber)
    {
        stClinetData clientData;
        for (stClinetData& client : vClientsData)
        {
            if (client.accountNumber == accountNumber)
            {
                clientData = client;
            }
        }
        return clientData;
    }

    stClinetData getClientByAccountNumber(string filePath, string accountNumber)
    {
        stClinetData clientData;
        vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath);
        for (stClinetData client : vClientsData)
        {
            if (client.accountNumber == accountNumber)
                clientData = client;
        }
        return clientData;
    }

    void deleteClientByAccountNumber(string filePath, string accountNumber, string delim = "#//#")
    {
        vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
        if (isAccountNumberFound(vClientsData, accountNumber))
        {
            printClientDataCardByAccountNumber(vClientsData, accountNumber);
            cout << endl;
            char isSure = readCharacter("are you sure you want to delete this client? [y/n]? ");
            if (isSure == 'y' || isSure == 'Y')
            {
                fstream file;
                file.open(filePath, ios::out);
                string clientLine = "";
                for (stClinetData client : vClientsData)
                {
                    if (client.accountNumber != accountNumber)
                    {
                        clientLine = convertClientDataRecordToLine(client, delim);
                        file << clientLine << endl;
                    }
                }
                cout << "Client is deleted succefully.\n";
                file.close();
            }
        }
        else
        {
            cout << "Client with account number (" << accountNumber << ") is not found\n";
        }
    }

    void deleteClientByAccountNumber(vector<stClinetData>& vClientsData, string accountNumber)
    {
        vector<stClinetData> vClientsData2;
        if (isAccountNumberFound(vClientsData, accountNumber))
        {
            printClientDataCardByAccountNumber(vClientsData, accountNumber);
            cout << endl;
            char isSure = readCharacter("are you sure you want to delete this client? [y/n]? ");
            if (isSure == 'y' || isSure == 'Y')
            {
                for (stClinetData client : vClientsData)
                {
                    if (client.accountNumber != accountNumber)
                    {
                        vClientsData2.push_back(client);
                    }
                }
                vClientsData = vClientsData2;
                cout << "Client is deleted from Vector succefully.\n";
            }
        }
        else
        {
            cout << "Client with account number (" << accountNumber << ") is not found\n";
        }
    }

    void changeClientRecord(stClinetData& clientData, string accountNumber)
    {
        cout << "Account Number: " << accountNumber << endl;
        clientData.pinCode = readString("Pin code: ");
        clientData.fullName = readString("Full Name: ");
        clientData.phone = readString("Phone Number: ");
        clientData.accountBalance = funcs::readFloatNumber("Account Balance: ");
    }

    void saveClientsDataToFile(string filePath, vector<stClinetData>& vClientsData, string delim = "#//#")
    {
        fstream file;
        file.open(filePath, ios::out); // overwrite

        string line = "";
        for (stClinetData& client : vClientsData)
        {
            line = convertClientDataRecordToLine(client, delim);
            file << line << endl;
        }
        file.close();
    }

    void updateClientData(vector<stClinetData> vClientsData, string accountNumber)
    {
        if (isAccountNumberFound(vClientsData, accountNumber))
        {
            printClientDataCardByAccountNumber(vClientsData, accountNumber);
            cout << endl;
            char isSure = readCharacter("are you sure you want to update this client? [y/n]? ");
            if (isSure == 'y' || isSure == 'Y')
            {
                for (stClinetData& client : vClientsData)
                {
                    if (client.accountNumber == accountNumber)
                    {
                        changeClientRecord(client, accountNumber);
                        break;
                    }
                }
                cout << "\nCLient has been updated succefully.\n";
            }
        }
        else
        {
            cout << "\nClient with account number (" << accountNumber << ") is not found\n";
        }
    }

    void updateClientData(string filePath, string accountNumber, string delim = "#//#")
    {
        vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
        if (isAccountNumberFound(vClientsData, accountNumber))
        {
            printClientDataCardByAccountNumber(vClientsData, accountNumber);
            cout << endl;
            char isSure = readCharacter("are you sure you want to update this client? [y/n]? ");
            if (isSure == 'y' || isSure == 'Y')
            {
                for (stClinetData& client : vClientsData)
                {
                    if (client.accountNumber == accountNumber)
                    {
                        changeClientRecord(client, accountNumber);
                        break;
                    }
                }
                saveClientsDataToFile(filePath, vClientsData, delim);
                cout << "\nCLient has been updated succefully.\n";
            }
        }
        else
        {
            cout << "\nClient with account number (" << accountNumber << ") is not found\n";
        }
    }

    void printClientsBalances(string filePath, string delim = "#//#")
    {
        vector<stClinetData> vClients = convertClientsDataFileToVector(filePath, delim);
        float totalBalance = 0;
        if (vClients.size() != 0)
        {
            cout << "\n\t\t\tBalances List [" << vClients.size() << " Client(s)]\n";
            cout << " _________________________________________________________________________\n\n";
            cout << " | " << left << setw(15) << "AccountNumber";
            cout << " | " << left << setw(25) << "Client Name";
            cout << " | " << left << setw(12) << "Balance";
            cout << "\n _________________________________________________________________________\n\n";
            for (stClinetData& client : vClients)
            {
                cout << " | " << left << setw(15) << client.accountNumber;
                cout << " | " << left << setw(25) << client.fullName;
                cout << " | " << left << setw(12) << client.accountBalance;
                cout << endl;
                totalBalance += client.accountBalance;
            }
            cout << " _________________________________________________________________________\n";
            cout << "\n\t\t\tTotal Balances = " << totalBalance << endl;
        }
        else
        {
            cout << "\nNo Clients in system yet !\n";
        }
    }

    void depositToClientBalance(string accountNumber, string filePath, string delim = "#//#")
    {
        if (isAccountNumberFound(filePath, accountNumber, delim))
        {
            printClientDataCardByAccountNumber(filePath, accountNumber, delim);
            cout << endl;
            float depositAmount = funcs::readPositiveFloatNumber("Deposit Amount: ");
            vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
            for (stClinetData& client : vClientsData)
            {
                if (client.accountNumber == accountNumber)
                {
                    client.accountBalance += depositAmount;
                    saveClientsDataToFile(filePath, vClientsData, delim);
                    cout << "\n\nDeposit Transaction is done :)\n";
                    cout << "New Balance is: " << client.accountBalance << endl;
                    return;
                }
            }
        }
        else
        {
            cout << "\nAccount Number (" << accountNumber << ") is not found. Deposit is canceled!\n";
        }
    }

    bool depositToClientBalance(float depositAmount, string accountNumber, string filePath, string delim = "#//#")
    {
        if (isAccountNumberFound(filePath, accountNumber, delim))
        {
            vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
            for (stClinetData& client : vClientsData)
            {
                if (client.accountNumber == accountNumber)
                {
                    client.accountBalance += depositAmount;
                    saveClientsDataToFile(filePath, vClientsData, delim);
                    cout << "\n\nDeposit Transaction is done :)\n";
                    cout << "New Balance is: " << client.accountBalance << endl;
                    return true;
                }
            }
        }
        else
        {
            cout << "\nAccount Number (" << accountNumber << ") is not found. Deposit is canceled!\n";
        }

        return false;
    }

    void withdrawFromClientBalance(string accountNumber, string filePath, string delim = "#//#")
    {
        if (isAccountNumberFound(filePath, accountNumber, delim))
        {
            printClientDataCardByAccountNumber(filePath, accountNumber, delim);
            cout << endl;
            float withdraw = funcs::readPositiveFloatNumber("Withdraw Amount: ");
            vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
            for (stClinetData& client : vClientsData)
            {
                if (client.accountNumber == accountNumber)
                {
                    if (client.accountBalance >= withdraw)
                    {
                        client.accountBalance -= withdraw;
                        saveClientsDataToFile(filePath, vClientsData, delim);
                        cout << "\n\nWithdraw Transaction is done :)\n";
                        cout << "New Balance is: " << client.accountBalance << endl;
                    }
                    else
                    {
                        cout << "Withdraw amount is higher than the balance!\n";
                        cout << "Withdraw Transaction is canceled\n";
                    }
                    return;
                }
            }
        }
        else
        {
            cout << "\nAccount Number (" << accountNumber << ") is not found. Deposit is canceled!\n";
        }
    }

    bool withdrawFromClientBalance(float amount, string accountNumber, string filePath, string delim = "#//#")
    {
        if (isAccountNumberFound(filePath, accountNumber, delim))
        {
            vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
            for (stClinetData& client : vClientsData)
            {
                if (client.accountNumber == accountNumber)
                {
                    if (client.accountBalance >= amount)
                    {
                        client.accountBalance -= amount;
                        saveClientsDataToFile(filePath, vClientsData, delim);
                        cout << "\n\nWithdraw Transaction is done :)\n";
                        cout << "New Balance is: " << client.accountBalance << endl;
                        return true;
                    }
                    else
                    {
                        cout << "Withdraw amount is higher than the balance!\n";
                        cout << "Withdraw Transaction is canceled\n";
                        return false;
                    }
                }
            }
        }
        else
        {
            cout << "\nAccount Number (" << accountNumber << ") is not found. Deposit is canceled!\n";
        }
        
        return false;
    }

    short readPermissions()
    {
        char isAccess = readCharacter("You want to give full access? [y/n]? ");
        if (tolower(isAccess) == 'y')
            return -1;

        short permissions = 0;
        cout << "You want to give access to:\n";
        isAccess = readCharacter("Show Client List? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::ClientsList_pr;
        }
        isAccess = readCharacter("Add New Clients? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::AddNewClient_pr;
        }
        isAccess = readCharacter("Delete Clients? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::DeleteClient_pr;
        }
        isAccess = readCharacter("Update Clients Info? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::UpdateClient_pr;
        }
        isAccess = readCharacter("Find Clients? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::FindClient_pr;
        }
        isAccess = readCharacter("Transactions? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::Transactions_pr;
        }
        isAccess = readCharacter("Manage Users? [y/n]? ");
        if (tolower(isAccess) == 'y')
        {
            permissions = permissions | enPermissions::ManageUsers_pr;
        }

        if (permissions == 127)
            return -1;
        return permissions;
    }

    stUser readUser()
    {
        stUser user;
        user.username = global_funcs::readString("username: ");
        user.password = global_funcs::readString("password: ");
        user.permissions = readPermissions();
        return user;
    }

    stUser readUser(string username)
    {
        stUser user;
        user.username = username;
        user.password = global_funcs::readString("password: ");
        user.permissions = readPermissions();
        return user;
    }

    stUser convertUserLineToUser(string line)
    {
        stUser user;
        vector<string> vLine = splitStringIntoVector(line, "#//#");
        user.username = vLine[0];
        user.password = vLine[1];
        user.permissions = stoi(vLine[2]);
        return user;
    }

    vector<stUser> copyUsersFileContentIntoVector(string filePath)
    {
        vector<stUser> vUsers;
        vector<string> vLines = loadFileContentToVector(filePath);
        for (string& line : vLines)
        {
            if (line != "")
            {
                vUsers.push_back(convertUserLineToUser(line));
            }
        }
        return vUsers;
    }

    bool isUserFound(string filePath, stUser user)
    {
        vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
        for (stUser& vUser : vUsers)
        {
            if (vUser.username == user.username)
            {
                if (vUser.password == user.password)
                    return true;
            }
        }
        return false;
    }

    bool isUserFound(string filePath, string username)
    {
        vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
        for (stUser& user : vUsers)
        {
            if (user.username == username)
                return true;
        }
        return false;
    }

    void showUsersDataHeader(short size)
    {
        cout << "\n\t\t\t\tUsers List [" << size << " User(s)]\n";
        cout << " _________________________________________________________________________________________\n\n";
        cout << " | " << left << setw(15) << "Username";
        cout << " | " << left << setw(15) << "Password";
        cout << " | " << left << setw(15) << "Access";
        cout << "\n _________________________________________________________________________________________\n\n";
    }

    void printUserData(stUser& user)
    {
        cout << " | " << left << setw(15) << user.username;
        cout << " | " << left << setw(15) << user.password;
        cout << " | " << left << setw(15) << user.permissions;
    }

    void showAllUsers(string filePath, string delim)
    {
        vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
        showUsersDataHeader((short)vUsers.size());
        if (vUsers.size() > 0)
        {
            for (stUser& user : vUsers)
            {
                printUserData(user);
                cout << endl;
            }
            cout << "\n _________________________________________________________________________________________\n\n";
        }
        else
            cout << "No Users Yet!\n";
    }

    string convertUserToLine(stUser user, string delim = "#//#")
    {
        return user.username + delim + user.password + delim + to_string(user.permissions);
    }

    void addUserLineToFile(string filePath, string line)
    {
        fstream file;
        file.open(filePath, ios::out | ios::app);
        file << line << endl;
        file.close();
    }

    void addNewUser(string filePath, string delim = "#//#")
    {
        stUser user;
        do
        {
            user.username = readString("username: ");
            if (isUserFound(filePath, user.username))
                cout << "User [" << user.username << "] already exists!!\n";
            else
                break;
        } while (true);

        user = readUser(user.username);

        addUserLineToFile(filePath, convertUserToLine(user, delim));
        cout << "\nuser has been added succesfully <3\n";

    }

    void deleteUser(string filePath, string username, string delim = "#//#")
    {
        if (username == "Admin")
        {
            cout << "\nAdmin can not be DELETED!!\n";
            return;
        }

        stUser user;
        user.username = username;
        if (isUserFound(filePath, user.username))
        {
            user.password = readString("password: ");
            if (isUserFound(filePath, user))
            {
                vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
                fstream file;
                file.open(filePath, ios::out);
                for (stUser& vUser : vUsers)
                {
                    if (vUser.username != user.username)
                    {
                        string line = convertUserToLine(vUser, delim);
                        file << line << endl;
                    }
                }
                file.close();
                cout << "\nUser has been deleted succefully\n";
            }
            else
                cout << "Password is wrong!!\n";
        }
        else
        {
            cout << "\nuser [" << username << "] does not exist!!\n";
        }


    }

    void updateUser(string filePath, string username, string delim = "#//#")
    {
        if (username == "Admin")
        {
            cout << "\nAdmin can not be Updated from here!!\n";
            return;
        }

        stUser user;
        user.username = username;
        if (isUserFound(filePath, user.username))
        {
            user.password = readString("password: ");
            if (isUserFound(filePath, user))
            {
                vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
                fstream file;
                file.open(filePath, ios::out);
                for (stUser& vUser : vUsers)
                {
                    if (vUser.username == user.username)
                    {
                        cout << "Update user [" << user.username << "] info:\n";
                        vUser = readUser();
                    }
                    string line = convertUserToLine(vUser, delim);
                    file << line << endl;
                }
                file.close();
                cout << "\nUser has been Updated succefully\n";
            }
            else
                cout << "Password is wrong!!\n";
        }
        else
        {
            cout << "\nuser [" << username << "] does not exist!!\n";
        }
    }

    void printUserDataCard(stUser user)
    {
        cout << "----------------------------\n";
        cout << "Username   : " << user.username << endl;
        cout << "Password   : " << user.password << endl;
        cout << "Permissions: " << user.permissions << endl;
        cout << "----------------------------\n";
    }

    void findUser(string filePath, string username, string delim = "#//#")
    {
        if (isUserFound(filePath, username))
        {
            vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
            for (stUser& user : vUsers)
            {
                if (user.username == username)
                {
                    printUserDataCard(user);
                    return;
                }
            }
        }
        else
            cout << "user [" << username << "] does not exist!!\n";
    }

    stUser copyUserData(string filePath, string username, string delim = "#//#")
    {
        if (isUserFound(filePath, username))
        {
            vector<stUser> vUsers = copyUsersFileContentIntoVector(filePath);
            for (stUser& user : vUsers)
            {
                if (user.username == username)
                {
                    return user;
                }
            }
        }
        else
            return { "", "", 0 };
    }

    bool checkPermission(short permissions, enPermissions permissionScreen)
    {
        return permissions == -1 || ((permissions & permissionScreen) == permissionScreen);
    }

    bool isClientFound(stClinetData& client, string filePath, string delim = "#//#")
    {
        vector<stClinetData> vClients = convertClientsDataFileToVector(filePath, delim);
        for (stClinetData& C : vClients)
        {
            if (C.accountNumber == client.accountNumber)
            {
                if (C.pinCode == client.pinCode)
                    return true;
            }
        }

        return false;
    }

    stClinetData copyClientInfo(string accountNumber, string pinCode, string filePath, string delim = "#//#")
    {
        vector<stClinetData> vClients = convertClientsDataFileToVector(filePath, delim);

        for (stClinetData& client : vClients)
        {
            if (client.accountNumber == accountNumber && client.pinCode == pinCode)
                return client;
        }

        stClinetData client;
        return client;
    }

    short convertQuickWithdrawChoiceToAmount(short choice)
    {
        switch (choice)
        {
        case 1:
            return 20;
        case 2:
            return 50;
        case 3:
            return 100;
        case 4:
            return 200;
        case 5:
            return 400;
        case 6:
            return 600;
        case 7:
            return 800;
        case 8:
            return 1000;
        default:
            return 0;
        }
    }

    bool quickWithdraw(short choice, string accountNumber, string filePath, string delim = "#//#")
    {
        short amount = convertQuickWithdrawChoiceToAmount(choice);
        if (isAccountNumberFound(filePath, accountNumber, delim))
        {
            vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
            for (stClinetData& client : vClientsData)
            {
                if (client.accountNumber == accountNumber)
                {
                    if (client.accountBalance >= amount)
                    {
                        client.accountBalance -= amount;
                        saveClientsDataToFile(filePath, vClientsData, delim);
                        cout << "\n\nWithdraw Transaction is done :)\n";
                        cout << "New Balance is: " << client.accountBalance << endl;
                        return true;
                    }
                    else
                    {
                        cout << "Withdraw amount is higher than the balance!\n";
                        cout << "Withdraw Transaction is canceled\n";
                        return false;
                    }
                }
            }
        }
        else
        {
            cout << "\nAccount Number (" << accountNumber << ") is not found. Deposit is canceled!\n";
        }

        return false;
    }

}