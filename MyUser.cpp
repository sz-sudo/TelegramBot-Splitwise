//
// Created by sz on 07.02.21.
//

#include "MyUser.h"
#include <fstream>
#include <tgbot/tgbot.h>
#include <string>

using std::string;

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

void MyUser::setChatID(long int chatID) {
    this->chatID = chatID;
}

void MyUser::setName(string name) {
    this->name = name;
}

long int MyUser::getChatID() const {
    return this->chatID;
}

string MyUser::getName() const {
    return this->name;
}

bool MyUser::reminder(TgBot::Bot &bot) {
    bool result = false;

    ifstream input;
    
    //You might have to change this address.
    input.open("/home/sz/Codes/CLionProjects/Telegram-Bot/Database/" + std::to_string(this->chatID)+ ".txt");

    if (!input.is_open())
        return false;

    string temp1, temp2;

    while (true) {

        input >> temp1 >> temp2;

        if( input.eof() )
            break;

        if (atof(temp2.c_str()) > 0)
        {
            result = true;

            bot.getApi().sendMessage(stoi(temp1), "You owe "+ bot.getApi().getChat(this->chatID)->firstName + " " + temp2 +".");
        }


    }

    input.close();
    return result;


}