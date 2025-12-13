#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

class User {
private:
    int id;
    string username;
    string password;
    string role;
    string fullName;
    string address;
    string phone;

public:
    // Constructor
    User();
    User(int uid, string uname, string upass, string urole, string ufull, string uaddr, string uphone);

    // Getter
    int getId();
    string getUsername();
    string getPassword();
    string getRole();
    string getFullName();
    string getAddress();
    string getPhone();

    // Setter
    void setId(int uid);
    void setUsername(string uname);
    void setPassword(string upass);
    void setRole(string urole);
    void setFullName(string ufull);
    void setAddress(string uaddr);
    void setPhone(string uphone);

    // Method Login
    bool login(string inputPassword);
    void editProfile(string newName, string newAddr, string newPhone);
};

#endif