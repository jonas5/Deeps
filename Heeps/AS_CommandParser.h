#ifndef __AS_COMMANDPARSER_H_INCLUDED__
#define __AS_COMMANDPARSER_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <vector>
#include <string>
#include <sstream>

namespace Ashita
{
    namespace Commands
    {
        /**
         * Returns the input string split by the given delimiter.
         *
         * @param {const char*} input The string to be split.
         * @param {char} delim The delimiter to split the string by.
         * @returns {std::vector<std::string>} The vector of split string parts.
         */
        static std::vector<std::string> Split(const char* input, char delim)
        {
            std::vector<std::string> elems;
            std::stringstream ss(input);
            std::string item;
            while (std::getline(ss, item, delim))
            {
                elems.push_back(item);
            }
            return elems;
        }

        /**
         * Returns the arguments of a command input string.
         *
         * @param {const char*} input The command string to parse.
         * @param {std::vector<std::string>*} args The vector to hold the arguments.
         * @returns {size_t} The number of arguments found.
         */
        static size_t GetCommandArgs(const char* input, std::vector<std::string>* args)
        {
            if (args == nullptr)
                return 0;
            std::stringstream ss(input);
            std::string item;
            while (std::getline(ss, item, ' '))
            {
                if (item.length() > 0)
                    args->push_back(item);
            }
            return args->size();
        }
    }; // namespace Commands
}; // namespace Ashita

#endif // __AS_COMMANDPARSER_H_INCLUDED__