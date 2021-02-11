//
// Created by sz on 06.02.21.
//

#include "ReaderWriter.h"
#include <fstream>
#include <tgbot/tgbot.h>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

string ReaderWriter::readFile(int fileName) {
    ifstream input;

    //You might have to change this address.
    input.open("/home/sz/Codes/CLionProjects/Telegram-Bot/Database/" + std::to_string(fileName)+ ".txt");

    if (!input.is_open())
        return "The list is empty.";
    string result = "", temp1, temp2;

    while (true) {

        input >> temp1 >> temp2;

        if( input.eof() )
            break;

        if (!temp1.empty() && !temp2.empty())
            result += temp1 + " " + temp2 + "\n";

    }

    input.close();

    if (result.empty() || result == "")
        return "The list is empty.";
    else
        return result;
}



void ReaderWriter::writeToFile(int fileName, vector<string> ids, vector<int> coefficients, string transaction) {

    int tran = stoi(transaction);
    ofstream output;

    //You might have to change this address.
    output.open("/home/sz/Codes/CLionProjects/Telegram-Bot/Database/" + std::to_string(fileName) + ".txt", ios::app);

    if (!output.is_open())
        return;

    double sum = 0;

    for (int i = 0; i < coefficients.size(); i++)
        sum += coefficients.at(i);

    for (int i = 0; i < ids.size(); i++) {

        output << ids.at(i) << "\n";
        output << (tran / sum) * coefficients.at(i) << "\n";
    }
    output.close();
}