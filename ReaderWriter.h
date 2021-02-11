//
// Created by sz on 06.02.21.
//

#ifndef TELEGRAM_BOT_READERWRITER_H
#define TELEGRAM_BOT_READERWRITER_H
#include <string>
#include <vector>
#include <fstream>
#include <tgbot/tgbot.h>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;



using std::string;
using std::vector;

class ReaderWriter {
public:

    static string readFile(int fileName);
    static void writeToFile(int fileName, vector<string> ids, vector<int> coefficients, string transaction);


};


#endif //TELEGRAM_BOT_READERWRITER_H
