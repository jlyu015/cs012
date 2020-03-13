#include <iostream>
#include <string>
using namespace std;

#include "User.h"

User::User() {
    username = "";
    password = "";
    
}

User::User(const string& uname, const string& pass) {
    username = uname;
    password = pass;

}

string User::getUsername() const {
    return username;
    
}
string User::getPassword() const {
    return password;
}
bool User::check(const string &uname, const string &pass) const {
    if (username == uname && password == pass) {
        if(username.size() != 0)
            return true;
        else
            return false;
    }
    else 
        return false;
    
}

bool User::setPassword(const string &oldpass, const string &newpass) {
    if (oldpass == password && password.size() != 0) {
        password = newpass;
        return true; 
    }
    else {
        return false;
    }
    
    
}