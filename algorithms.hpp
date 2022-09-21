///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for four algorithms:
//
// run_length_encode
// longest_frequent_substring
// reformat_date
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

std::map<std::string, std::string> months({{"january", "01"},{"february", "02"},{"march", "03"},{"april", "04"},{"may", "05"},{"june", "06"},{"july", "07"},{"august", "08"},{"september", "09"},{"october","10"},{"november", "11"}, {"december", "12"}});



namespace algorithms {

  // Run-length-encode the given string.
  //
  // uncompressed must be a string containing only lower-case letters or spaces.
  //
  // A run is defined as a sequence of K>2 contiguous copies of the same
  // character c.
  // For example, "aaa" is a run with K=3 and c='a'.
  // This function returns a string based on uncompressed, where every run is
  // replaced with the string
  //   COUNTc
  // where COUNT is the base-10 representation of K. Non-run characters are
  // left as-is.
  //
  // Example inputs and outputs:
  //   "aaa" -> "3a"
  //   "heloooooooo there" -> "hel8o there"
  //   "footloose and fancy free" -> "f2otl2ose and fancy fr2e"
  //
  // Throws std::invalid_argument if the string contains invalid characters.
  std::string append_run(std::string &C, char& run_char, int run_length) {                
      if (run_length > 1) {                         // 1                                                 
          C.append(std::to_string(run_length));       // 1
      }
      C.push_back(run_char);                        // 1
      return C;                                     // 1
  }
  std::string run_length_encode(const std::string& uncompressed) {
      for (auto c: uncompressed){                                                // n 1    
        if ((int(c) < 97 || int(c) > 122) && (int(c) != 32)){                      // 1
          throw std::invalid_argument("Must be either lower case or spaces");        // 1
        }
      }
      std::string C = "";                                                        // 1
      if (uncompressed.size() == 0) {                                            // 1
          return C;                                                                // 1
      }
      char run_char  = uncompressed[0];                                          // 1
      int run_length = 1;                                                        // 1
      for (int i = 1; i < uncompressed.length(); i++) {                          // n 1
          if (uncompressed[i] == run_char) {                                       // 1
              run_length++;                                                        // 1
          }
          else {                                                                   // 1
              C = append_run(C, run_char, run_length);                             // 1
              run_char = uncompressed[i];                                          // 1
              run_length = 1;                                                      // 1
          }
      }
      C = append_run(C, run_char, run_length);                                  // 1
      return C;                                                                 // 1
}
  // Returns the longest substring of text, such that every character in the
  // substring appears at least k times in text.
  // If there are ties, the substring that appears first is returned.
  std::string longest_frequent_substring(const std::string& text, unsigned k) {

    std::map<char, int> freq;                                                   // 1

 for (auto c : text) {                                                          // n
     std::map<char, int>::iterator it = freq.find(c);                             // n
     if (it == freq.end()) {                                                      // 1
         freq.insert({ c,1 });                                                    // 1
     }
     else {                                                                       // 1
         it->second = it->second + 1;                                             // 1
     }
 }
 std::string best = "";                                                         // 1
 std::string cand;                                                              // 1
 if ((text.size() == 1) && k == 1) return text;                                 // 1 1
 for (int i = 0; i < text.length()-1; i++) {                                    // n 1
     for (int j = i + 1; j <= text.length(); j++) {                               // n 1
         bool verifier = true;                                                      // 1
         bool works = true;                                                         // 1
         cand = text.substr(i, j-i);                                                // n
         for (auto c : cand) {                                                      // n 1
             if (c == '_') verifier = false;                                          // 1 1
         }
         if (verifier) {                                                            // 1
             for (auto c : cand) {                                                  // n 1
                 if (freq.find(c)->second < k) {                                      // 1
                     works = false;                                                   // 1
                 }
             }
             if (works && (cand.size() > best.size())) {                            // 1
                 best = cand;                                                       // 1
             }
         }

     }
 }
 return best;                                                                       // 1
  }

std::string reformat_date(const std::string& input) {                                  
   std::string newInput = input;                                            // 1
  std::vector<std::string> parsedInput;                                     // 1
  std::vector<char> format;                                                 // 1
  transform(newInput.begin(), newInput.end(), newInput.begin(), ::tolower); // n
  bool foo = true;                                                          // 1
  int push_from = 0;                                                        // 1
  bool find_next = false;                                                   // 1        
  bool caseOne = false;                                                     // 1 
  bool caseTwo = false;                                                     // 1
  bool caseThree = false;                                                   // 1
  bool caseFour = false;                                                    // 1
  int found = 0;                                                            // 1
  for (int i = 0; i < newInput.size(); i++) {                                                                         // n

      if ((newInput[i] == ' ' || newInput[i] == ',' || newInput[i] == '/' || newInput[i] == '-') && !(find_next)) {     // 1
          if (found > 0) {                                                                                                 // 1
              find_next = true;                                                                                              // 1
              format.push_back(newInput[i]);                                                                                 // 1
              parsedInput.push_back(newInput.substr(push_from, i - push_from));                                              // n
          }
      }
      else if ((newInput[i] == ' ' || newInput[i] == ',' || newInput[i] == '/' || newInput[i] == '-') && find_next) {   // 1
          format.push_back(newInput[i]);                                                                                // 1                                                                 
      }   
      else if (find_next && (i == newInput.size() - 1)) {                                                               // 1
          std::string temp;                                                                                             // 1
          temp.push_back(newInput[i]);                                                                                  // 1
          parsedInput.push_back(temp);                                                                                  // 1
      } 
      else if (i == newInput.size() - 1) {                                                                              // 1
          parsedInput.push_back(newInput.substr(push_from, newInput.size() - push_from));                               // n
      } 
      else if (find_next) {                                                                                             // 1
          push_from = i;                                                                                                // 1
          find_next = false;                                                                                            // 1
      }
      else {                                                                                                            // 1
          if (found == 0) {                                                                                             // 1
              push_from = i;                                                                                            // 1
          }
          found++;                                                                                                      // 1
      }
  }
  if (parsedInput.size() != 3) {                                                                                   // 1
      throw std::invalid_argument("Invalid Input");                                                                // 1
  }
  if ((format[0] == '/') && (format[1] == '/')) {                                                                  // 1                                                           
      foo = true;                                                                                                  // 1
  }
  else if ((format[0] == ' ') && (format[1] == ',') && (format[2] == ' ')) {                                       // 1
      foo = true;                                                                                                  // 1
  }
  else if ((format[0] == '-') && (format[1] == '-')) {                                                             // 1
      foo = true;                                                                                                  // 1
  }
  else if (format[0] == ' ') {                                                                                     // 1
      throw std::invalid_argument("Invalid Input");                                                                // 1
  }

  std::vector<std::string> output = { "", "", "" };                                                                 // 1
  std::stringstream s;                                                                                              // 1
  std::string first = parsedInput[0];                                                                               // 1
  std::string second = parsedInput[1];                                                                              // 1
  std::string third = parsedInput[2];                                                                               // 1

  //Check first elements input
  for (auto it = months.begin(); it != months.end(); it++) {    // n
      std::string tempMonth = it->first.substr(0, 3);           // 1
      bool can_be_int = true;                                   // 1
      int iTempMonth;                                           // 1
      try {                               
          iTempMonth = std::stoi(first);                        // 1
      }
      catch (std::invalid_argument) {                           // 1
          can_be_int = false;                                   // 1
      } 
  
      if (tempMonth == first) {                                 // 1
          caseFour = true;                                      // 1
          output[1] = it->second;                               // 1
          break;                                                // 1
      }   
      else if (it->first == first) {                            // 1
          caseThree = true;                                     // 1
          output[1] = it->second;                               // 1
          break;                                                // 1
      }
      else if (can_be_int) {                                    // 1
          if (iTempMonth > 0 && iTempMonth < 13) {              // 1
              s << std::setw(2) << std::setfill('0') << iTempMonth;  // 1
              output[1] = s.str();                                   // 1
              s.str("");                                             // 1
              caseTwo = true;                                        // 1
              break;                                                 // 1
          }
          else if (iTempMonth > 1899 && iTempMonth < 2100) {         // 1
              caseOne = true;                                        // 1
              output[0] = first;                                     // 1
              break;                                                 // 1
          }
      }
  }

  //Check other inputs
  if (caseOne) {                                                    // 1
      if (stoi(second) > 0 && stoi(second) < 13) {                  // 1
          s << std::setw(2) << std::setfill('0') << second;         // 1
          output[1] = s.str();                                      // 1
          s.str("");                                                // 1
      }
      else {                                                        // 1
          throw std::invalid_argument("Invalid Input");             // 1
      }
      if (stoi(third) > 0 && stoi(third) < 32) {                    // 1
          s << std::setw(2) << std::setfill('0') << third;          // 1
          output[2] = s.str();                                      // 1
          s.str("");                                                // 1
      }
      else {                                                        // 1  
          throw std::invalid_argument("Invalid Input");             // 1
      }
  }
  else if (caseTwo) {                                               // 1
      if (stoi(second) > 0 && stoi(second) < 32) {                  // 1
          s << std::setw(2) << std::setfill('0') << second;         // 1
          output[2] = s.str();                                      // 1
          s.str("");                                                // 1
      }
      else {                                                        // 1
          throw std::invalid_argument("Invalid Input");             // 1
      }
      if (stoi(third) > 1899 && stoi(third) < 2100) {               // 1
          s << third;                                               // 1
          output[0] = s.str();                                      // 1
          s.str("");                                                // 1
      }
      else {                                                        // 1
          throw std::invalid_argument("Invalid Input");             // 1
      }
  }
  else if (caseThree || caseFour) {                                 // 1
      if (stoi(second) > 0 && stoi(second) < 32) {                  // 1
          s << std::setw(2) << std::setfill('0') << second;         // 1
          output[2] = s.str();                                      // 1
          s.str("");                                                // 1
      }
      else {                                                        // 1
          throw std::invalid_argument("Invalid Input");             // 1
      }
      if (stoi(third) > 1899 && stoi(third) < 2100) {               // 1
          output[0] = third;                                        // 1
      }
      else {                                                        // 1
          throw std::invalid_argument("Invalid Input");             // 1
      }
  }
  else {                                                            // 1
      throw std::invalid_argument("Invalid Input");                 // 1
  }
  for (int i = 0; i < 3; i++) {                                     // 3 although this is a loop, it always loops 3 times only
      for (auto c : output[i]) {                                       // n
          if (c > '9' || c < '0') {                                     // 1
              throw std::invalid_argument("invalid input");             // 1
          }
      }
  }
  s << output[0] << "-" << output[1] << "-" << output[2];           // 1
  return s.str();                                                   // 1
  }

}
