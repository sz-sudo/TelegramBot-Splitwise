#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>
#include "ReaderWriter.h"

using namespace std;
using namespace TgBot;
#include "MyUser.h"

int main()
{
    string token = ""; // Paste your token here 
    TgBot::Bot bot("TOKEN");// Paste your token here

    vector<BotCommand::Ptr> commands;
    vector<string> ids;
    vector<int> coefficients;
    bool idEntered = false, transactionEntered = false;
    MyUser *myUser = new MyUser;

    BotCommand::Ptr cmdArray(new BotCommand);
    cmdArray->command = "start";
    cmdArray->description = "Starts the bot";
    commands.push_back(cmdArray);


    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "person";
    cmdArray->description = "Receives the ID";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "status";
    cmdArray->description = "A full list of debts and loans";
    commands.push_back(cmdArray);


    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "reminder";
    cmdArray->description = "A reminder will be sent to those who owe you money";
    commands.push_back(cmdArray);


    bot.getApi().setMyCommands(commands);

    vector<BotCommand::Ptr> vectCmd;
    vectCmd = bot.getApi().getMyCommands();

    for(std::vector<BotCommand::Ptr>::iterator it = vectCmd.begin(); it != vectCmd.end(); ++it) {
        printf("cmd: %s -> %s\r",(*it)->command.c_str(),(*it)->description.c_str());
    }


    bot.getEvents().onCommand("start", [&bot, &myUser](TgBot::Message::Ptr message) {

        myUser->setName(bot.getApi().getChat(message->chat->id)->firstName);
        myUser->setChatID(bot.getApi().getChat(message->chat->id)->id);

        bot.getApi().sendMessage(message->chat->id, "Hi " + myUser->getName()+ "\nYour chat id is: " + to_string(myUser->getChatID()));


        });


    bot.getEvents().onCommand("person", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Please enter the ID and the coefficient!\n For example: 123456789 3");


    });

    bot.getEvents().onCommand("status", [&bot, &myUser](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Here is a full list of debts and loans:");

        bot.getApi().sendMessage(message->chat->id, ReaderWriter::readFile(myUser->getChatID()));
    });

    bot.getEvents().onCommand("reminder", [&bot, &myUser, &token](TgBot::Message::Ptr message) {

        myUser->setChatID(bot.getApi().getChat(message->chat->id)->id);

        if (myUser->reminder(bot))
            bot.getApi().sendMessage(message->chat->id, "A reminder has been sent to those who owe you money!");

    });

    bot.getEvents().onNonCommandMessage([&bot, &idEntered, &transactionEntered, &ids, &coefficients, &myUser](TgBot::Message::Ptr message){

        printf("User wrote %s\n", message->text.c_str());

        if ((StringTools::startsWith(message->text, "+") || StringTools::startsWith(message->text, "-")) && idEntered == true) {
            idEntered = false;
            transactionEntered = true;

            myUser->setChatID(bot.getApi().getChat(message->chat->id)->id);

            bot.getApi().sendMessage(message->chat->id, "Done!");
            ReaderWriter::writeToFile(myUser->getChatID(), ids, coefficients, message->text);
            ids.clear();
            coefficients.clear();
        }

        else if (!(StringTools::startsWith(message->text, "+") || StringTools::startsWith(message->text, "-")) && transactionEntered == false) {
            idEntered = true;

            string id = message->text.substr(0, message->text.find(" "));
            string cof = message->text.substr(message->text.find(" ") + 1, message->text.size());

            ids.push_back(id);
            if (cof.empty() || cof == " " || cof == "")
                coefficients.push_back(1);
            else
                coefficients.push_back(stoi(cof));
            bot.getApi().sendMessage(message->chat->id, "Enter the transaction (must include sign) or enter another ID");
        }

        else if(transactionEntered == false)
        {
            bot.getApi().sendMessage(message->chat->id, "No valid ID was entered.");
        }

    });


    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;

}