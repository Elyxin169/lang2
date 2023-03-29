#ifndef TYPES_H
#define TYPES_H 420
#include <vector>
#include <string>
namespace types
{
      #define i32c 1
      #define strc 2
      struct type{
            int code;
            int size;
      };
      struct line
      {
            std::vector<std::string> tokens;
      };
      class memObj
      {
      public:
            types::type type;
            void *data;
      };
      class memory
      {
      public:
            memObj *objects;
      };

      const type i32 = {i32c, sizeof(int32_t)};
      const type str = {strc, sizeof(std::string)};
}
#endif