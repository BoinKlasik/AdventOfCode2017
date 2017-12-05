#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <limits.h>

template <class T>
void printIt(std::string prefix, T t) {
  std::ostringstream stream;
  stream << prefix << ": " << t << std::endl;
  OutputDebugStringA(stream.str().c_str());
}

int main() {
  int valid = 0;
  int total = 0;
  std::string fileName = "Text.txt";
  std::fstream fileStream(fileName);

  std::string line;
  while(std::getline(fileStream, line)) {
    if(line.length() == 0) {
      continue;
    }
    printIt("line", line);
    total++;
    std::vector<std::string> seenPassphrase;
    int start = 0;
    int space;
    while(space = line.find(' ', start)) {
      if(space == line.npos) {
        space = line.length();
      }
      std::string word = line.substr(start, space - start);
      start = space+1;
      if(std::find(seenPassphrase.begin(), seenPassphrase.end(), word) == seenPassphrase.end()) {
        seenPassphrase.emplace_back(word);
      } else {
        break;
      }
      if(space == line.length()) {
        valid++;
        break;
      }
    }
  }
  printIt("total", total);
  printIt("numValid", valid);
}
