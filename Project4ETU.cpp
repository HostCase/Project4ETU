#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <unordered_map>
#include <sstream>
using namespace std;
const int maxWords = 50;
const int maxWordLength = 10;
void processString(const string& str, string& text, int &filein);
void removeExtraSpaces(string& text);
void limitWordsLength(string& text);
void removeExtraPunct(string& text);
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");
    string text;
    string choice;
    int filein = 0, whatyouwant = 0;
    cout << "Choose what we will do (from file - enter file)/(from console - enter console)\n";
    getline(cin, choice);
    do {
        if (!(filein)) {
            processString(choice, text, filein);
        }
        cout<<"What do you want to do with the file?\n0 - exit\n1 - Remove spaces\n2 - Remove extra punctuation\n5 - show text\n";
        cin >> whatyouwant;
        switch (whatyouwant) {
        case 1: {
            cout << "Removing spaces\n";
            removeExtraSpaces(text);
            cout << "Completed\n";
            break;
        }
        case 2: {
            cout << "Removing extra punctuation\n";
            removeExtraPunct(text);
            cout << "Completed\n";
            break;
        }
        case 5: {
            cout <<"Your text is "<< text << "\n";
        }
        }
    } while (whatyouwant);
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
                limitWordsLength(text);

            }
            filein = 1;
            fin.close();
            break;
        }
        case 2: {
            cout << "Enter the string: \n";
            getline(cin, text);
            limitWordsLength(text);
            filein = 1;
            break;
        }
        default:
            cout << "Unknown type\n";
        }
    }
}


void removeExtraSpaces(string& text) {
    string output;
    bool previousIsSpace = false;

    for (char c : text) {
        if (isspace(c)) {
            if (previousIsSpace) {
                continue;
            }
            else {
                output += ' ';
                previousIsSpace = true;
            }
        }
        else {
            output += c;
            previousIsSpace = false;
        }
    }
    output.erase(output.find_last_not_of(" \n\r\t") + 1);
    output.erase(0, output.find_first_not_of(" \n\r\t"));

    text = output;
}

void limitWordsLength(string& text) {
    istringstream stream(text);
    string word;
    string* words = new string[maxWords]; 
    int wordCount = 0;

    while (stream >> word) {
        if (word.length() > maxWordLength) {
            word = word.substr(0, maxWordLength);
        }
        if (wordCount < maxWords) {
            words[wordCount] = word;
            wordCount++;
        }
        else {
            break;
        }
    }
    text = "";
   
    
    for (int i = 0; i < wordCount; i++) {
        text += words[i] + " ";
    }
    text.pop_back(); 

    delete[] words; // ПРОГРАММИРУЕМ КАК УМЕЕМ
}



void removeExtraPunct(string& text) {
    string output;
    bool previousIsPunctuation = false;

    for (char c : text) {
        if (ispunct(c) && !(c=='.')) {
            if (previousIsPunctuation) {
            }
            else {
                output += c;
                previousIsPunctuation = true;
            }
        }
        else {
            output += c;
            previousIsPunctuation = false;
        }
    }

    text = output;
}