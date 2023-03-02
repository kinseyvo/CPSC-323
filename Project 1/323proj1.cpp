#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

string keywords[] = { "void", "using", "namespace", "include", "main", "int", "float", "double", "string", "cout", "cin", "for", "std", "while", "return", "if", "else"};
char operators[] = {'+', '-', '++', '--', '*', '/', '=', '<', '>', '<=', '>=', '==', '||', '&', '&&', '+=', '-=', '%', '!=', '!'};
char integers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
char punctuation[] = { ';', ':'};

// Helper Functions
bool checkKeyword(string input);
bool checkIdentifer(string input);
void removeSpaces(vector<string>& input);

int main()
{
    vector<string> finalKeywords;
    vector<string> finalSeparators;
    vector<string> finalIdentifiers;
    vector<string> finalOperators;
    vector<string> finalIntegers;
    vector<string> finalReals;
    vector<string> finalPunctuations;
    string contents_of_file = "";
    string element;

    fstream file("input_sourcecode.txt");
    
    // Getting all contents of file and storing it in one string
    while (getline(file, element)) {
        contents_of_file = contents_of_file + element;
    }

    //Remove things after comment symbols
    for (int i = 0; i < contents_of_file.length(); i++) {
        if (contents_of_file[i] == '/' || contents_of_file[i + 1] == '*') {
            contents_of_file.erase(i, 11);
        }
    }

    cout << "token\t\t\t" << "lexeme" << endl;
    cout << "------------------------------" << endl;

    string content;
    for (int i = 0; i < contents_of_file.length(); i++) {
        // gets rid of spaces
        if (contents_of_file[i] != ' ' && contents_of_file[i] != '/') {
            content = content + contents_of_file[i];
        }

        else {
            // checks for C++ keywords
            if (checkKeyword(content)) {
                finalKeywords.push_back(content);
                //cout << "keyword\t\t\t" << content;
                content = "";
                //cout << endl;
            }

            // checks for separators
            else if (content == "," || content == "(" || content == ")" || content == "{" || content == "}" || content == "<<"
                || content == ">>" || content == "[" || content == "]" || content == "'" || content == "#") {
                finalSeparators.push_back(content);
                //cout << "separator\t\t" << content;
                content = "";
                //cout << endl;
            }
            
            // uses keyword checker to get C++ identifers and operators
            else if (checkKeyword(content) == false) {
                if (checkIdentifer(content) == true) {
                    if (content == "+" || content == "-" || content == "++" || content == "--" || content == "*" || content == "/" || content == "="
                        || content == "<" || content == ">" || content == "<=" || content == ">= " || content == "==" || content == "||" || content == "&"
                        || content == "&&" || content == "+=" || content == "-=" || content == "%" || content == "!" || content == "!=") {
                        finalOperators.push_back(content);
                        //cout << "operator\t\t" << content;
                        content = "";
                        //cout << endl;
                    }
                    // used isdigit to check if the next part of the content file is an integer
                    else if (isdigit(content[0])) {
                        if (content[1] == punctuation[0] || content[1] == punctuation[1]) {
                            finalPunctuations.push_back(content);
                            //cout << "punctuation\t\t" << content;
                            content = "";
                            //cout << endl;
                        }
                        if (isdigit(content[0]) == false) {
                            finalReals.push_back(content);
                            //cout << "real\t\t\t" << content;
                            content = "";
                            //cout << endl;
                        }
                        finalIntegers.push_back(content);
                        //cout << "integer\t\t\t" << content;
                        content = "";
                        //cout << endl;
                    }
                    finalIdentifiers.push_back(content);
                    //cout << "identifer\t\t" << content;
                    content = "";
                    //cout << endl;
                }
            }
        }
    }

    //Using vector to print elements of each token in list form
    cout << "keyword\t\t\t";
    removeSpaces(finalKeywords);
    for (int i = 0; i < finalKeywords.size(); i++) {
        cout << finalKeywords.at(i) << ", ";
    }
    cout << endl << "separator\t\t";
    removeSpaces(finalSeparators);
    for (int i = 0; i < finalSeparators.size(); i++) {
        cout << finalSeparators.at(i) << ", ";
    }
    cout << endl << "identifer\t\t";
    removeSpaces(finalIdentifiers);
    for (int i = 0; i < finalIdentifiers.size(); i++) {
        cout << finalIdentifiers.at(i) << ", ";
    }
    cout << endl << "operator\t\t";
    removeSpaces(finalOperators);
    for (int i = 0; i < finalOperators.size(); i++) {
        cout << finalOperators.at(i) << ", ";
    }
    cout << endl << "integer\t\t\t";
    removeSpaces(finalIntegers);
    for (int i = 0; i < finalIntegers.size(); i++) {
        cout << finalIntegers.at(i) << ", ";
    }
    cout << endl << "real\t\t\t";
    removeSpaces(finalReals);
    for (int i = 0; i < finalReals.size(); i++) {
        cout << finalReals.at(i) << ", ";
    }
    cout << endl << "punctuation\t\t\t";
    removeSpaces(finalPunctuations);
    for (int i = 0; i < finalPunctuations.size(); i++) {
        cout << finalPunctuations.at(i) << ", ";
    }
}

bool checkKeyword(string input) {
    for (int i = 0; i < 17; i++) {
        if (keywords[i] == input) {
            return true;
        }
    }
    return false;
}

bool checkIdentifer(string input) {
    if (input != "") {
        return true;
    }
    return false;
}

void removeSpaces(vector<string>& input) {
    for (int i = 0; i < input.size(); i++) {
        if (input.at(i) == "") {
            input.erase(input.begin() + i);
        }
    }
}