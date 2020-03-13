#ifndef __BBOARD_H__
#define __BBOARD_H__

#include <string>
#include <vector>
using namespace std;

#include "Message.h"
#include "User.h"

class BBoard {
 private:
   string title;
	vector<User> user_list;
	const User * current_user;
	vector<Message *> message_list;
    
    //helper functions
  
 public:
	BBoard();
	BBoard(const string &);
	~BBoard();
	bool loadUsers(const string &);
	bool loadMessages(const string &);
	bool saveMessages(const string &);
	void login();
	void run(); 
 private:
    void addTopic();
    void addReply();
    void addUser();
    void display() const;
    const User * getUser(const string &name, const string &pw) const;
};

#endif