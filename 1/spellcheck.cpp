/*
Ali Rahman
DSA II Coding Assignment 1
This programming assignment contains a class used to define a HashTable
which is separated into a header and source file.  These files are used in a
separate file meant to spellcheck a document based on a dictionary file which is
loaded into the hashtable. The program asks for input of the file names and
checks the input file to see if there are any unknown words or any words that
are longer than 20 characters.  The program will output any of these words in
a separate file indicated by the user.
*/

#include "hash.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

int linelen, i, line, wordlen;
string dictname, inputname, outputname, buf, word;
ifstream dict, infile;
ofstream outfile;
bool skip, output;

int main(){

  hashTable *dictionary = new hashTable(1009);

  cout << "Enter name of dictionary: ";
  getline(cin, dictname);
  dict.open(dictname.c_str());
  //Error Checking
  if(!dict){
    cout << "Error: Unable to open dictionary file " << dictname << endl;
    return(-1);
  }

  //Begin Clock for Dictionary
  clock_t t1 = clock();

  //Adding Dictionary Words to HashTable
  while(dict >> word){
      //Lowercase Conversion
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      //Adding Word to HashTable
      dictionary->insert(word, NULL);
  }
  //End Clock for Dictionary
  clock_t t2 = clock();

  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Total time (in seconds) to load dictionary: " << timeDiff << endl;

  cout << "Enter name of input file: ";
  getline(cin, inputname);
  infile.open(inputname.c_str());
  //Error Checking
  if(!infile){
    cout << "Error: Unable to open input file " << inputname << endl;
    return(-1);
  }

  cout << "Enter name of output file: ";
  getline(cin, outputname);
  outfile.open(outputname.c_str());
  //Error Checking
  if(!outfile){
    cout << "Error: Unable to open output file " << outputname << endl;
    return(-1);
  }

  //Begin Clock for Reading Input
  clock_t t3 =  clock();

  while(getline(infile, buf)){
    line++;
    //Reset Word
    word.clear();
    wordlen = 0;
    //Reset Variables for new line
    linelen = buf.size();
    i = 0;
    skip = false;
    output = false;

    while(i <= linelen){
      //Checking Each Character Until Word Seperator Appears
      if(isalnum(buf[i]) || buf[i] == '\'' || buf[i] == '-'){
        if(isdigit(buf[i])){
          //Skipping Words with Numbers
            skip = true;
        }
        if(++wordlen <= 20){
          word += buf[i];
        }
        else {
          //Word Length Greater than 20
          if(!output){
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            outfile << "Long word at line " << line << ", starts: " << word << endl;
            output = true;
          }
          skip = true;
          //Continue until end of word Anyways To Avoid Error
        }
      }
      else {
        //End of Word
        if(skip){
          //No output
          skip = false;
          output = false;
        }
        else{
          transform(word.begin(), word.end(), word.begin(), ::tolower);
          if(wordlen != 0 && !(dictionary->contains(word))){
            outfile << "Unknown word at line " << line << ": " << word << endl;
          }
        }
        //Clearing word to avoid overlap with next word in same line
        word.clear();
        wordlen = 0;
      }
      // Move to next Line
      i++;
    }
  }

  clock_t t4 = clock();
  double timeRead = ((double) (t4 - t3)) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to check document: " << timeRead << endl;

  dict.close();
  infile.close();
  outfile.close();
  return 0;
}
