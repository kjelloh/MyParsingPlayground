#include <iostream>
#include <iomanip>
#include <string>
 
int main(int argc, char *argv[])
{
  std::string s{};
  do {
    std::cout << "\nEnter text to parse (input nothing,'q' or 'quit' to quit)>";
    std::getline(std::cin,s);
    std::cout << "\nSorry, parsing of " << std::quoted(s) << " not yet implemented";
  } while (s.size()>0 and s!="q" and s!="quit");
  return 0;
 }