#include "user.h"

using namespace std;

User::User(){
    id = 0; //kasih nilai awal biar ga error
    role = "customer";
}

//Register/load file
User::User(int uid, string uname, string upass, string urole, string ufull, string uaddr, string uphone){
    id = uid;
    username = uname;
    password = upass;
    role = urole;
    fullName = ufull;
    address = uaddr;
    phone = uphone;
}

//ambil data
int User::getId(){return id;}
string User::getUsername(){return username;}
string User::getPassword(){return password;}
string User::getRole(){return role;}
string User::getFullName(){return fullName;}
string User::getAddress(){return address;}
string User::getPhone(){return phone;}

//ubah data
void User::setId(int uid){id = uid;}
void User::setUsername(string uname){username = uname;}
void User::setPassword(string upass){password = upass;}
void User::setRole(string urole){role = urole;}
void User::setFullName(string ufull){fullName = ufull;}
void User::setAddress(string uaddr){address = uaddr;}
void User::setPhone(string uphone){phone = uphone;}

//logika cek password method login
bool User::login(string inputPassword){
    if (this->password == inputPassword){
        return true;
    } else {
        return false;
    }
}

//edit profile
void User::editProfile(string newName, string newAddr, string newPhone){
    this->fullName = newName;
    this->address = newAddr;
    this->phone = newPhone;
}