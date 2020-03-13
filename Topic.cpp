#include "Topic.h"
#include "Message.h"

Topic::Topic() :Message() {
    
}

Topic::Topic(const string &author, const string &subject, const string &body, unsigned id): Message(author, subject, body, id) {

}

bool Topic::isReply() const {
    return false;
}

string Topic::toFormattedString() const {
    string bigString;
    
    bigString = "<begin_topic>\n";
    bigString = bigString + Message::toFormattedString();
    
    return bigString;
}