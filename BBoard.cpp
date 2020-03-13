    #include <iostream>
    #include <string>
    #include <vector>
    #include <sstream>
    #include <fstream>

    using namespace std;

    #include "BBoard.h"
    #include "Topic.h"
    #include "Reply.h"
    /* Constructs a board with a default title, 
         * empty user & message lists, 
         * and the "default" User
         */
    BBoard::BBoard() {
        title = "default title";
        current_user = nullptr;
    }

        /* Same as the default constructor except 
         * it sets the title of the board
         */
    BBoard::BBoard(const string &boardTitle) {
        title = boardTitle;
        current_user = nullptr;

    }
    BBoard::~BBoard() {
        for (unsigned i = 0; i < message_list.size(); ++i) {
            delete message_list.at(i);
        }
    } //new

    bool BBoard::loadUsers(const string &filename) {
        ifstream inFS;
        string username, password;

        inFS.open(filename);

        if(!inFS.is_open()) {
            return false;

        }
        while(inFS >> username >> password) {
                User currentUser(username, password);
                user_list.push_back(currentUser);
                //userList.push_back(currentUser);
                }
            inFS.close();
            return true;
    }

    bool BBoard::loadMessages(const string &datafile) {
        ifstream inFS;
        ofstream outFS;
        int childID;
        unsigned numMessages;
        int count = 0;
        unsigned id;
        vector<unsigned> child_list;
        string currString, discard, auth, subj, bod, children, headerType;
        Topic *currTopic = nullptr;
        Reply *currReply = nullptr;

        //cout << "checking valid file" << endl;
        inFS.open(datafile);

        if(!inFS.is_open()) {
            return false;
        }

        else {
            inFS >> numMessages;
            if(numMessages > 0) {
                for (unsigned i = 0; i < numMessages; ++i) {
                    inFS >> headerType;
                    //cout <<"headerType " << headerType;
                    bod = "";
                    children = "default, no children.";

                    //cout << "Went into topic branch" << endl;
                    inFS >> discard;
                    //cout << "discard: " << discard << endl;
                    inFS >> id; // takes id 
                    //cout <<"ID: "<< id << endl;
                    inFS >> discard; 
                    //cout << "Discard: " << discard << endl;
                    getline(inFS, subj); // takes subject 
                    subj.erase(0, 1);
                    //cout <<"Subject: |" << subj <<"|" <<endl;
                    inFS >> discard;
                    //cout << "Discard: " << discard << endl;
                    inFS>> auth; // takes author 
                    //cout << "Author: " << auth << endl;
                    //code to take in children line
                     inFS >> discard;
                    //cout << "Discard: " << discard << endl;
                    if(discard == ":children:") {
                        getline(inFS, children);
                        //cout << "WENT INTO THE CHILDREN BRANCH Children line: " << children << endl;
                        stringstream ss(children);
                        if(children.size() >= 2) {
                           int temp;
                            while (ss >> temp) {
                                childID = temp;
                                child_list.push_back(childID);
                            //cout <<"childid as int: " << childID << endl;
                            }


                            //cout <<"two children as ints:" << childID <<" " <<childID2 << endl;
                        }
                        inFS >> discard;
                        //cout << "Discard: |" << discard <<"|" << endl;
                    }

                        //currTopic->addChild();

                    if (discard == ":body:") {
                        //cout << "went into body branch" << endl;
                        string tempString;
                        inFS.ignore();
                        getline(inFS,currString);
                        //cout << "currString body: " << currString << endl;
                        bod += currString;

                        while(tempString != "<end>") {
                            getline(inFS, tempString);
                            if(tempString != "<end>") {
                                bod += "\n" + tempString;
                            }
                        }
                    }


                    if (headerType == "<begin_topic>") {
        //             cout << endl << "-----:CURRENT TOPIC THAT IS CONSTRUCTED:------" << endl;
        //             cout << "ID:" << id << endl;
        //             cout << "author:" << auth << endl;
        //             cout << "subject:" << subj << endl;
        //             cout << "children" << children << endl;
        //             cout << "Body:" << bod << endl;
        //             cout << "-----:CURRENT TOPIC THAT IS CONTRUCTED:------" << endl << endl;

                    currTopic = new Topic(auth, subj, bod, id);
                    message_list.push_back(currTopic);

                    }
                    else if(headerType == "<begin_reply>") {
        //             cout << endl << "-----:CURRENT REPLY THAT IS CONSTRUCTED:------" << endl;
        //             cout << "ID:" << id << endl;
        //             cout << "author:" << auth << endl;
        //             cout << "subject:" << subj << endl;
        //             cout << "children" << children << endl;
        //             cout << "Body:" << bod << endl;
        //             cout << "-----:CURRENT REPLY THAT IS CONTRUCTED:------" << endl << endl;

                    currReply = new Reply(auth, subj, bod, id);
                    message_list.push_back(currReply);
                    }
                     child_list.push_back(0);

                }
                 for(unsigned i = 0; i < child_list.size() - 1; ++i) {
                if(child_list.at(i) != 0){
                    (message_list.at(count))->addChild(message_list.at(child_list.at(i) - 1));
                }
                else
                    if(child_list.at(i) == 0 && child_list.at(i + 1) != 0) {
                        count++;
                    }

                }
            }
        inFS.close();
        return true;
        } //new
    }





    bool BBoard::saveMessages(const string &datafile) {
        ofstream outFS;
        
        outFS.open(datafile.c_str());
        if(outFS.is_open()) {
            outFS << message_list.size() << "\n";
            for (unsigned i = 0; i < message_list.size(); ++i) {
                outFS << message_list.at(i)->Message::toFormattedString();

            }
            outFS.close();
            return true;
        }
        
        return false;
    }//new





    //FIXME endls after choose action and 
    void BBoard::login() {
        string uname, pass;
        cout << "Welcome to " << title << endl;

        //cout << endl;

        while (current_user == nullptr) {
            cout << "Enter your username ('Q' or 'q' to quit): ";
            cin >> uname;
            if(uname == "q" || uname == "Q") { 
                cout << "Bye!" << endl;
                return;
            }
            cout << "Enter your password: ";
            cin >> pass;
            cin.ignore();
            //cout << endl;

            //If a match is found, it sets currentUser to the identified User from the list (remember, currentUser is now a pointer, not an actual object).

            for(unsigned i = 0; i < user_list.size(); ++i) {
                if(uname == user_list.at(i).getUsername() && pass == user_list.at(i).getPassword()) {
                    cout  << endl<< "Welcome back " << uname << "!" << endl << endl;

                    current_user = &user_list.at(i);
                    return;
                }

            }

                   cout << "Invalid Username or Password!" << endl << endl;

    //                cout << "Enter your username ('Q' or 'q' to quit): ";
    //                cin >> uname;
                    //cout << endl;
            }
    } 
    void BBoard::addReply() {
        int IDinput;
        string auth, bod, subj, tempString, bodyInput;
        unsigned id;
        Reply *currReply = nullptr;
        id = message_list.size() + 1;
        auth = current_user->getUsername();
        cout << "Enter Message ID (-1 for Menu): ";
        cin >> IDinput;
        while (IDinput != -1 && (IDinput < 1 || static_cast<unsigned>(IDinput) > message_list.size())) {
            cout << "Invalid message ID!!" << endl << endl;
            cout << "Enter Message ID (-1 for Menu): ";
            cin >> IDinput;
        }
        if(IDinput == -1) {
            return;
        }
        subj = "Re: " + message_list.at(IDinput - 1)->getSubject();

        cout << "Enter Body: ";

        cin.ignore();
        getline(cin, bodyInput);
        bod += bodyInput;
        while (bodyInput != "") {
            getline(cin, bodyInput);
            bod += "\n" + bodyInput;
        }
    //     cout << "ID: " << id << endl;
    //     cout << "Author: "<< auth << endl;
    //     cout << "Subject: " << subj << endl;
    //     cout << "Body: "<< bod << endl;
        currReply = new Reply(auth, subj, bod, id);
        message_list.push_back(currReply);
        message_list.at(IDinput-1)->addChild(currReply);

    }


    void BBoard::addTopic() {
        string auth, bod, subj, tempString, bodyInput;
        unsigned id;
        Topic *currTopic = nullptr;
        auth = current_user->getUsername();
        cin.ignore();
        cout << "Enter Subject: ";
        getline(cin, subj);
        //gets subject g
        id = message_list.size() + 1;
        cout << "Enter Body: ";
        cout << endl;
        getline(cin, bodyInput);
        bod += bodyInput;
        while (bodyInput != "") {
            getline(cin, bodyInput);
            bod += "\n" + bodyInput;
        }
    //     cout << "ID: " << id << endl;
    //     cout << "Author: "<< auth << endl;
    //     cout << "Subject: " << subj << endl;
    //     cout << "Body: |"<< bod << "|" << endl;

        currTopic = new Topic(auth, subj, bod, id);
        message_list.push_back(currTopic);
    }
    void BBoard::run() {
        char userInput = 'm';

        if (current_user == nullptr) {
            return;
        }
        //cout << endl;
        while (userInput != 'Q' && userInput != 'q') {
            cout << "Menu" << endl;
            cout << "- Display Messages ('D' or 'd')" << endl;
            cout << "- Add New Topic ('N' or 'n')" << endl;
            cout << "- Add Reply to a Topic ('R' or 'r')" << endl;
            cout << "- Quit ('Q' or 'q')" << endl;
            cout << "Choose an action: ";
            cin >> userInput; 

            if (userInput == 'D' || userInput == 'd') {
                cout << endl;
                display();
            }
            if (userInput == 'N' || userInput == 'n') {
                addTopic();
            }
            if (userInput == 'R' || userInput == 'r') {
                addReply();
            }
            if (userInput == 'Q' || userInput == 'q') {
                cout << "Bye!" << endl;
                return;
            }
        }


    }

    // void BBoard::addMessage() {
    //     string userMessage;
    //     string userTopic;

    //     cout << "Enter Subject: ";
    //     cin.ignore();
    //     getline(cin , userTopic);
    //     cout << endl;
    //     cout << "Enter Body: ";
    //     getline(cin, userMessage);
    //     cout << endl;
    //     cout << "Message Recorded!" << endl;

    //     Message currMessage(current_User->getUsername(), userTopic, userMessage);
    //     messageList.push_back(currMessage);
    // }


    void BBoard::display() const {
        if (message_list.size() == 0) {
            cout <<"Nothing to Display." << endl << endl;
        }
        else {
            for(unsigned i = 0; i < message_list.size(); ++i) {
                if(!message_list.at(i)->isReply()) {
                    cout <<"---------------------------------------------------------" << endl;
                    message_list.at(i)->print(0);
                }
            }
            cout <<"---------------------------------------------------------" << endl << endl;

        }
    //     else {

    //         cout << "---------------------------------------------------------" << endl;

    //         for (unsigned i = 0; i < messageList.size(); ++i) {
    //              cout << "Message #" << i + 1 << ": ";

    //              messageList.at(i).display();

    //              cout << "---------------------------------------------------------" << endl;
    //             }
    //         }   

    }
    // bool BBoard::userExists(const string &uname, const string &pass) const {
    //     for (unsigned i = 0; i < userList.size(); ++i) {
    //         if (userList.at(i).check(uname, pass)) {
    //                 return true;
    //         }

    //     }
    //      return false;
    // }