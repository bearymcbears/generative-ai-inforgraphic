#include "dotenvparse.h"
#include <fstream>
#include <iostream>

using namespace std;

map<string, string> DotenvParse::envVariables;

void DotenvParse::LoadEnvFile(string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open .env file at " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
       
        size_t delimiterPos = line.find('=');
        if (delimiterPos == string::npos) {
            cerr << "Warning: Invalid line in .env file: " << line << endl;
            continue;
        }

        string key = line.substr(0, delimiterPos);
        string value = line.substr(delimiterPos + 1);

        envVariables[key] = value;
    }
}