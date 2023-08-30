#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;
// George Krier
// gkrier

string program_name;
// No Changes needed, this method queries a user for input
bool GetMadLibFile(ifstream& inputfile){
    if (inputfile.is_open())
        inputfile.close();
    cout << "Please enter a valid Mad Libs File or 'exit' to close: ";
    string filename;
    getline(cin, filename);
    string temp = filename;
    transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c){return tolower(c);});
    if (filename == "exit"){
        cout << "Exiting program, Thanks for playing!\n";
        return false;
    }
    inputfile.open(temp, ifstream::in);
    if (!inputfile){
        cerr << program_name << ", Function: GetMadLibFile. Error File cannot be found/opened: " << filename << ".\n";
        return false;
    }
    return true;
}

// Is string in the format of a fill in the blank word
// If string starts with and ends with _ then return true, else false
bool IsFillInBlank(const string &word){
    return (word.at(0) == '_' && word.at(word.length()-1));
}

string GetUserResponse(string &fill_in){
    string out;

    // Remove leading and trailing _ character from fill in word type
    fill_in.replace(0, 1, "");
    fill_in.replace(fill_in.length() - 1, 1, "");
    //fill_in = fill_in.substr(1, fill_in.length() - 1);

    // Replace all _ characters in the middle of the fill in word to allow for multi-word fill in words
    size_t position;
    while ((position = fill_in.find("_")) != string::npos) {
        fill_in.replace(position, 1, " ");
    }

    cout << "Please enter a \"" << fill_in << "\": ";
    getline(std::cin, out);
    return out;
}

int main(int argc, char* argv[])
{
    program_name = argv[0];
    // Create the File reading ifstream.
    ifstream input_file;

    string line;
    string word;    
    
    stringstream output_stream("");

    while (GetMadLibFile(input_file))
    {
        
        while (getline(input_file, line)) {
            stringstream line_stream(line);
            
            while (line_stream >> word) {\
                if (IsFillInBlank(word)) {
                    word = GetUserResponse(word);
                }
                output_stream << word << " ";
            }
            
            output_stream << "\n";
        }

        cout << "Your MadLib!\n\n" << output_stream.str() << "\n";

        // Output the finished madlib like so "Your MadLib\n\n" followed by their madlib and a new line at the end
    }
}


