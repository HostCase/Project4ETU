#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxWords = 50;
const int maxWordLength = 10;
void processString(const string& str, string& text, int &filein);
void removeExtraSpaces(string& text);
void limitWordsLength(string& text);
void removeExtraPunct(string& text);
void correctLetterCase(string& text);
void separateWords(const string& text);
void removeChars(string& text);
void removeChar(string& text);
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
        cout<<"What do you want to do with the file?\n0 - exit\n1 - Remove spaces\n2 - Remove extra punctuation\n3 - limit word lengt\n4 - Correct letter case\n5 - Group text\n6 - Remove symbol from string\n7 - show text\n";
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
        case 3: {
            cout << "Limiting word lenght\n";
            limitWordsLength(text);
            cout << "Completed\n";
            break;
        }
        case 4: {
            cout << "Correcting letter case\n";
            correctLetterCase(text);
            cout << "Completed\n";
            break;
        }
        case 5: {
            cout << "Grouping starting\n";
            limitWordsLength(text);
            separateWords(text);
            cout << "Completed\n";
            break;
              }
        case 6: {
            cout << "Starting programm to remove symbols from string\n";
            removeChar(text);
            cout << "Completed\n";
        }
        case 7: {
            cout <<"Your text is "<< text << "\n";
            break;
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


void removeExtraSpaces(string& text) {
    string output;
    bool previousIsSpace = false;

    for (char c : text) {
        if (isspace(c)) {
            if (!previousIsSpace) {
                output += ' ';
            }
            previousIsSpace = true;
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
        text += words[i];
        if (i < wordCount - 1) {
            text += " ";
        }
        if (i == (wordCount - 1)) {
            text += ".";
        }
    }

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

void correctLetterCase(string& text) {
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i]) && (i == 0 || text[i - 1] == ' ')) {
            text[i] = toupper(text[i]);
        }
        else {
            text[i] = tolower(text[i]);
        }
    }
}


void separateWords(const string& text) {
    string litters_words, digit_words, mix_words;
    string word;
    istringstream stream(text);
    while (stream >> word) {
        if (all_of(word.begin(), word.end(), isalpha)) {
            litters_words += word + " ";
        }
        else if (all_of(word.begin(), word.end(), isdigit)) {
            digit_words += word + " ";
        }
        else {
            mix_words += word + " ";
        }
    }

    cout << "Words only with litters " << litters_words << endl;
    cout << "Words only with digits " << digit_words << endl;
    cout << "Worlds mixed " << mix_words << endl;
}


void removeChar(string& text) {
    char input;
    cout << "Enter symbol that you want remove from string:\n ";
    cin >> input;
    text.erase(remove(text.begin(), text.end(), input), text.end());
}