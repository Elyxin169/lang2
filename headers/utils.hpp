#ifndef UTILS_H
#define UTILS_H 69
#include <fstream>
#include <string>
#include <sstream>
#include "types.hpp"
namespace utils
{
      std::string readFile(const std::string &filePath)
      {
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                  throw std::runtime_error("Failed to open file: " + filePath);
            }
            std::string content((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));
            file.close();
            return content;
      }
      std::vector<types::line> splitTokens(const std::string &inputString, const char delimiter = '\n')
      {
            std::vector<types::line> lines;

            std::stringstream ss(inputString);
            std::string lineString;

            while (std::getline(ss, lineString, delimiter))
            {
                  types::line l;
                  std::stringstream lineSs(lineString);
                  std::string token;

                  while (lineSs >> token)
                  {
                        l.tokens.push_back(token);
                  }

                  lines.push_back(l);
            }

            return lines;
      }
      types::memory *initMem(int size)
      {
            types::memory *mem = new types::memory;
            mem->objects = new types::memObj[size];
            return mem;
      }

      int voidPtr2I32(void *ptr)
      {
            return *(int *)ptr;
      }
}
#endif