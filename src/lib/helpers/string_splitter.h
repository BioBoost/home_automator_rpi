#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace BiosHomeAutomator {

  class StringSplitter {

    public:
      template<typename Out>
      static void split(const std::string &s, char delim, Out result) {
          std::stringstream ss(s);
          std::string item;
          while (std::getline(ss, item, delim)) {
              *(result++) = item;
          }
      }

      static std::vector<std::string> split(const std::string &s, char delim) {
          std::vector<std::string> elems;
          split(s, delim, std::back_inserter(elems));
          return elems;
      }

      //Note that this solution does not skip empty tokens
      //In order to avoid it skipping empty tokens, do an empty() check: if (!item.empty()) elems.push_back(item
  };

};
