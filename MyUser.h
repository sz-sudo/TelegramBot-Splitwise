//
// Created by sz on 07.02.21.
//

#ifndef TELEGRAM_BOT_MYUSER_H
#define TELEGRAM_BOT_MYUSER_H
#include <string>
#include <tgbot/Bot.h>

using std::string;

class MyUser {
public:

    void setChatID(long int chatID);
    void setName(string name);

    bool reminder(TgBot::Bot &bot);

    long int getChatID() const;
    string getName() const;


private:
    long int chatID;
    string name;


};


#endif //TELEGRAM_BOT_MYUSER_H
