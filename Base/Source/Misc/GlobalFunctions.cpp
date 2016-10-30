#include "GlobalFunctions.h"
#include <fstream>
#include <sstream>

void convertStringToUpperCaps(std::string &zeStr)
{
    for (std::string::iterator it = zeStr.begin(), end = zeStr.end(); it != end; ++it)
    {
        (*it) = toupper(*it);
    }
}

bool loadKeysAndDataFromCSVFile(const std::string &zefileLocation, std::vector<std::string> &zeKeys, std::vector<std::string> &zeValues)
{
    std::ifstream file(zefileLocation.c_str());
    if (file.is_open())
    {
        bool loadingFromFirstLine = true;
        std::string data = "";
        while (getline(file, data))
        {
            if (data == "" || data == "\n" || data == "\r")
                continue;
            std::string Token;
            std::istringstream iss(data);
            if (loadingFromFirstLine)
            {
                while (getline(iss, Token, ','))
                {
                    convertStringToUpperCaps(Token);
                    zeKeys.push_back(Token);
                }
                loadingFromFirstLine = false;
            }
            else {
                while (getline(iss, Token, ','))
                {
                    zeValues.push_back(Token);
                }
                while (zeValues.size() % zeKeys.size() != 0)
                {
                    zeValues.push_back("");
                }
            }
        }
        return true;
    }
    return false;
}

bool removingSpecificCharInStr(std::string &theStr, const char &theChar)
{
    for (size_t num = 0, sizeOfStr = theStr.size(); num < sizeOfStr; ++num)
    {
        if (theStr[num] == theChar)
        {
            theStr.erase(num);
            return true;
            break;
        }
    }
    return false;
}

bool checkWhetherTheWordInThatString(const std::string &theWord, const std::string &theStr)
{
    if (theStr.find(theWord) != std::string::npos)
        return true;
    return false;
}
