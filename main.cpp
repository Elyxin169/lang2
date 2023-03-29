#include <iostream>
#include <string.h>
#include <algorithm>
#include "headers/utils.hpp"

void doSet(types::line tokens);
void doPrint(std::vector<std::string> tokens, bool newline);
int counter = 0;
types::memory *memory;

types::memObj cmp1;
types::memObj cmp2;

int main(int argc, char const *argv[])
{
      std::vector<types::line> lines = utils::splitTokens(utils::readFile(argv[1]));
      // std::cout << test[0].tokens[2] << std::endl;

      memory = utils::initMem(10);
      for (; counter < lines.size(); counter++)
      {
            /*
            for (auto token : lines[counter].tokens){
                  std::cout << token << " ";
            }
            std::cout << std::endl;
            */
            if (lines[counter].tokens[0] == "set")
            {
                  doSet(lines[counter]);
            }
            if (lines[counter].tokens[0] == "print")
            {
                  std::vector<std::string> tmp(lines[counter].tokens.begin() + 1, lines[counter].tokens.end());
                  doPrint(tmp, false);
            }
            if (lines[counter].tokens[0] == "println")
            {
                  std::vector<std::string> tmp(lines[counter].tokens.begin() + 1, lines[counter].tokens.end());
                  doPrint(tmp, true);
            }
            if (lines[counter].tokens[0] == "goto")
            {
                  counter = atoi(lines[counter].tokens[1].c_str()) - 2;
            }
      }
      return 0;
}void doSet(types::line tokens)
{
      int location = std::stoi(tokens.tokens[1]);
      std::string type = tokens.tokens[2];
      std::string val;

      if (tokens.tokens.size() > 3) {
        for (int i = 3; i < tokens.tokens.size(); i++) {
          val += tokens.tokens[i];
          if (i != tokens.tokens.size() - 1) {
            val += " ";
          }
        }
      }

      types::type type_t;
      if (type == "i32")
      {
            type_t = types::i32;
            int value = std::stoi(val);
            memory->objects[location].data = malloc(type_t.size);
            memcpy(memory->objects[location].data, &value, type_t.size);
      }
      else if (type == "str")
      {
            type_t = types::str;
            val.erase(std::remove(val.begin(), val.end(), '\"'), val.end());
            memory->objects[location].data = malloc(type_t.size);
            memcpy(memory->objects[location].data, val.c_str(), type_t.size);
      }
      else
      {
            std::cerr << "Invalid type: " << type << std::endl;
            return;
      }

      memory->objects[location].type = type_t;
}



void doPrint(std::vector<std::string> tokens, bool newline)
{
      for (int i = 0; i < tokens.size(); i++)
      {
            if (tokens[i] == "")
                  break;
            else
            {
                  int address = atoi(tokens[i].c_str());
                  types::memObj *obj = &memory->objects[address];
                  if (obj->type.code == i32c)
                  {
                        std::cout << utils::voidPtr2I32(obj->data);
                  }
                  else if (obj->type.code == strc)
                  {
                        std::cout << static_cast<const char *>(obj->data);
                  }
            }
      }
      if (newline)
      {
            std::cout << "\n";
      }
}