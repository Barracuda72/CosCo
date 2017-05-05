#include <iostream>
#include <string>

#include "NOAFile.h"
#include "ERIFile.h"

int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    //NOAFile *f = new NOAFile(std::string(argv[1]));
    //f->extractTo(std::string(argv[2]));
    ERIFile *f = new ERIFile(std::string(argv[1]));
    delete f;
  } else
    std::cout << "Please specify archive and destination!" << std::endl;
}
