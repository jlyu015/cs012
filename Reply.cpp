#include "Reply.h"
#include "Message.h"


Reply::Reply() :Message() {
    
}

Reply::Reply(const string &author, const string &subject, const string &body,  unsigned id): Message(author, subject, body, id){
}

bool Reply::isReply() const {
    return true;
}
string Reply::toFormattedString() const {
    string bigString;
    
    bigString = "<begin_reply>\n";
    bigString = bigString + Message::toFormattedString();
    
    return bigString;
}