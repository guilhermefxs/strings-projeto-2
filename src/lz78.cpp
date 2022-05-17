#include <getopt.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <bitset>
#include "lz78.h"
using namespace std;

// void fileWriteBin(string filename, string input)
// {
//     string eightBits;
//     long temp;
//     char output;
//     ofstream out(filename);

//     for (int x = 0; x < input.length(); x += 8)
//     {
//         eightBits = input.substr(x, 8);
//         temp = strtol(eightBits.c_str(), 0, 2);
//         output = temp & 0xffl;
//         out << output;
//     }

//     out.close();
// }

char getBinFromString(string input)
{
    long temp;
    char output;
    temp = strtol(input.c_str(), 0, 2);
    output = temp & 0xffl;
    return output;
}

void fileWrite(string filename, string input)
{
	ofstream out(filename);
	out << input;
	out.close();
}


string stringToASCII(string &input)
{
    return bitset<8>(input[0]).to_string();
}

string decToBin(int &input)
{
    return bitset<8>(input).to_string();
}

int binToDec(char &input)
{
    bitset<8> dec(input);
    return dec.to_ulong();
}

void lz78Compress(std::string fileToCompress)
{
    // get filename
    std::string base_filename = fileToCompress.substr(fileToCompress.find_last_of("/\\") + 1);

    // remove extension from filename
    std::string::size_type const p(base_filename.find_last_of('.'));
    std::string file_without_extension = base_filename.substr(0, p);
    map<string, int> dictionary;
    string charInput;
    // string charCompressed;
    string character;
    string prefix;

    // ifstream t(fileToCompress);
    ifstream infile(fileToCompress, ifstream::in);
    string line;
    ofstream out(file_without_extension + ".myz");
    while (getline(infile, line))
    {   
        line += "\n";
        for (size_t x = 0; x < line.length(); ++x)
        {   
            if(dictionary.size() > 254){
                dictionary.clear();
            }
            character = line.substr(x, 1);
            if (dictionary.count(prefix + character))
                prefix += character;
            else
            {
                if (prefix.empty()){
                    char bynaryEmptyChar = getBinFromString("00000000");
                    // cout << "prefix: " << (int)bynaryEmptyChar << endl;
                    out << bynaryEmptyChar;
                }
                else{
                    char bynaryChar = getBinFromString(decToBin(dictionary[prefix]));
                    // cout << "prefix: " << (int)bynaryChar << endl;
                    out << bynaryChar;
                }            
                char bynaryChar = getBinFromString(stringToASCII(character));
                out << bynaryChar;
                // cout << "char: " << bynaryChar << endl;

                dictionary[prefix + character] = dictionary.size() + 1;

                prefix.clear();
            }
        }
    }
    out.close();
    // fileWriteBin("outputzip.txt", charCompressed);
}

void lz78Decompress(std::string fileToDecompress)
{
    map<int, string> dictionary;
    string charCompressed;
    string charDecompressed;
    string character;
    int codeword;

    // ifstream t(fileToDecompress);
    ifstream infile(fileToDecompress, ios::binary);
    
    char bytes[2];
    while(infile.read(bytes, 2)){
        if(dictionary.size() > 254){
                dictionary.clear();
            }
        codeword = binToDec(bytes[0]);
        character = bytes[1];

        if (codeword != 0)
            charCompressed += dictionary[codeword];
        charCompressed += character;
        int dictionarySize = dictionary.size();
        if (codeword != 0)
            dictionary[dictionarySize + 1] = dictionary[codeword] + character;
        else
            dictionary[dictionarySize + 1] = character;
    }

    // string line;
    // while (getline(infile, line))
    // {
    //     line += "\n";
    //     for (size_t x = 0; x < line.length(); ++ ++x)
    //     {
    //         codeword = binToDec(line[x]);
    //         character = line.substr(x + 1, 1);

    //         if (codeword != 0)
    //             charCompressed += dictionary[codeword];
    //         charCompressed += character;
    //         int dictionarySize = dictionary.size();
    //         if (codeword != 0)
    //             dictionary[dictionarySize + 1] = dictionary[codeword] + character;
    //         else
    //             dictionary[dictionarySize + 1] = character;
    //     }
    // }
    std::string::size_type const p(fileToDecompress.find_last_of('.'));
    std::string file_without_extension = fileToDecompress.substr(0, p);
    fileWrite(file_without_extension + "-decompressed.txt", charCompressed);
    // out.close();
}
