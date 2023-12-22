#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <unordered_map>
using namespace std;
void processString(const string& str, string& text, int &filein);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");
    string text;
    string choice;
    int filein = 0;
    cout << "Choose what we will do (from file - enter file)/(from console - enter console)\n";
    getline(cin, choice);
    do {
        if (!(filein)) {
            processString(choice, text, filein);
        }
        cout<<"What do you want to do with the file?\n";


    } while (!(choice=="exit"));
    return 0;
}



void processString(const string& str,string &text,int &filein ) {
    unordered_map<string, int> stringMap{
        {"file", 1},
        {"console", 2},
    };

    auto it = stringMap.find(str);
    if (it != stringMap.end()) {
        switch (it->second) {
        case 1: {
            cout << "You choosed file\n";
            ifstream fin;
            string path;
            cout << "Enter the file name and extension, the file must be in txt format, saved in ANSI encoding:\n";
            getline(cin, path);
            fin.open(path);
            if (!fin.is_open()) {
                cout << "Opening error\n";
            }
            else {

                text = "";
                string line;
                while (getline(fin, line)) {
                    text += line + " ";
                }

            }
            filein = 1;
            fin.close();
            break;
        }
        case 2: {
            cout << "Enter the string: \n";
            getline(cin, text);
            filein = 1;
            break;
        }
        default:
            cout << "Unknown type\n";
        }
    }
}
