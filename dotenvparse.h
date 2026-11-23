#ifndef DOTENVPARSE
#define DOTENVPARSE
#include <map>
#include <string>

using namespace std;

class DotenvParse {
public:
    static map<string, string> envVariables;
    static void LoadEnvFile(string filePath);
};

#endif