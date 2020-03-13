#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "Message.h"

Message::Message() {
    author = "John Doe";
    subject = "yeet";
    body = "nada";
    id = 999;
    
}

Message::Message(const string &author, const string &subject, const string &body, unsigned id) {
    this->author = author;
    this->subject = subject;
    this->body = body;
    this->id = id;
    
}

// void Message::display() const {
//     cout << subject << endl;
//     cout << "from " << author << ": " << body << endl;
    
// }
string Message::toFormattedString() const {
    string bigString;
    ostringstream partString;
    partString << ":id: " << id << "\n";
    partString << ":subject: " << subject << "\n";
    partString << ":from: " << author << "\n";
    if (childList.size() != 0) {
        partString << ":children: ";
        for (unsigned i = 0; i < childList.size(); i++){
            partString << (childList.at(i))->getID();
			if(i != childList.size() - 1) {
				partString << " ";
                }
        }
        partString << "\n";
    }
    partString << ":body: " << body << "\n";
    partString << "<end>\n";
    bigString = partString.str();
    return bigString;
}
Message::~Message() {
    for(unsigned i = 0; i < childList.size(); ++i) {
        delete childList[i];
    }
}

void Message::print(unsigned tab) const {
    string space, fullBody;
    fullBody = body;
	for (unsigned x = 0; x < tab; x++){
		space += "  ";
	}
	
	if(tab != 0) {
		cout << endl;
    }

	cout << space << "Message #" << id << ": " << subject << endl;
	cout << space << "from " << author << ": ";

	for (unsigned i = 0; i < fullBody.size(); i++) {
        if(fullBody.at(fullBody.size()-1) == '\n'){
            fullBody.erase(fullBody.size() - 1);
        }
		cout << fullBody.at(i);
		if (fullBody.at(i) == '\n') {
			cout << space;
		}
	}
	cout << endl;

	if (childList.size() != 0)
	{
		for (unsigned i = 0; i < childList.size(); i++)
		{
			childList.at(i)->print(tab + 1);
		}
	}
}
const string & Message::getSubject() const {
    return subject;
}
unsigned Message::getID() const{
    return id;
}
void Message::addChild(Message *childMessage) {
    childList.push_back(childMessage);
}