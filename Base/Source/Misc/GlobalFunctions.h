#include <string>
#include <vector>
//namespace GlobalFunctions
//{
//    void convertStringToUpperCaps(std::string zeStr)
//    {
//        for (std::string::iterator it = zeStr.begin(), end = zeStr.end(); it != end; ++it)
//        {
//            (*it) = toupper(*it);
//        }
//    }
//};

void convertStringToUpperCaps(std::string &zeStr);
bool loadKeysAndDataFromCSVFile(const std::string &zefileLocation, std::vector<std::string> &zeKeys, std::vector<std::string> &zeValues);
bool removingSpecificCharInStr(std::string &theStr, const char &theChar);
bool checkWhetherTheWordInThatString(const std::string &theWord, const std::string &theStr);