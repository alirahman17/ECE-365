#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

bool merge[1001][1001];     // Initialized to 0 because global

void strChk(ifstream &infile, ofstream &outfile){
  string a, b, c;
  while(infile >> a && infile >> b && infile >> c){
    // Check Lengths for edge case where there are extra characters after merge
    if(a.length() + b.length() != c.length()){
      outfile << "*** NOT A MERGE ***" << endl;
      continue;
    }
    memset(merge, false, sizeof(merge));    // Reset Global array for next iter
    for(int i = 0; i <= a.length(); i++){
      for(int j = 0; j <= b.length(); j++){ // Loop through all letter combo
        if(i == 0 && j > 0){
          if(c[j-1] == b[j-1]){       // Checking Edge case for string B
            if(j == 1){
              merge[i][j] = true;     // Initial position for string B
            } else{
              merge[i][j] = merge[i][j-1];  // Use Value of previous col
            }
            continue;
          }
        } else if(i > 0 && j == 0){   // Checking Edge case for string A
          if(c[i-1] == a[i-1]){
            if(i == 1){
              merge[i][j] = true;     // Initial position for string A
            } else{
              merge[i][j] = merge[i-1][j];  // Use Value of previous row
            }
            continue;
          }
        }
        if(i > 0 && j > 0){     // All other cases
          merge[i][j] = false;
          // If letter of prev row or col match check current index
          if(merge[i-1][j] || merge[i][j-1]){
            if(a[i - 1] == b[j - 1] && c[i + j - 1] == a[i-1])
              merge[i][j] = true; // if letters match for both
            else if(merge[i - 1][j] && c[i + j - 1] == a[i-1])
              merge[i][j] = true; // if letters match for string A
            else if(merge[i][j - 1] && c[i + j - 1] == b[j-1])
              merge[i][j] = true; // if letters match for string B
          }
        }
      }
    }
    // Output String if Valid Merge
    if(merge[a.length()][b.length()] == 1){
      int i = a.length();
      int j = b.length();
      while(i > 0 && j >= 0){
        if(merge[i][j] && (j == 0 || !merge[i][j-1])){
          c[i + j - 1] = toupper(c[i + j - 1]);
          i--;  // If string A matches or on edge transform letter of C toupper
        } else{
          j--;  // Else decrease index for string B, do nothing to C
        }
      }
      outfile << c << endl;
    } else{
      outfile << "*** NOT A MERGE ***" << endl;
    }
  }
}

int main(){
  string inputfile, outputfile;
  ifstream infile;
  ofstream outfile;

  // IO Setup
  cout << "Enter name of input file: ";
  getline (cin,inputfile);

  cout << "Enter name of output file: ";
  getline (cin,outputfile);

  infile.open(inputfile.c_str());
  if(!infile){                            // error handling for inputfile
    cerr << "ERROR: Unable to open " << inputfile;
    return(-1);
  }

  outfile.open(outputfile.c_str());
  if(!outfile){                           // error handling for outputfile
    cerr << "ERROR: Unable to open " << outputfile;
    return(-1);
  }

  strChk(infile, outfile);                // Function to check merges

  infile.close();
  outfile.close();
  return 0;
}
