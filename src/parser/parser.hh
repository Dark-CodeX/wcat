/**
 * @file parser/parser.hh
 * @author Tushar Chaurasia (Dark-CodeX)
 * @brief The header file is a part of https://github.com/Dark-CodeX/wcat.git, written for managing argv
 * @copyright Copyright (c) 2023 - Tushar Chaurasia
 * @license GNU General Public License v3.0
 */

#ifndef PARSER_DEFINED
#define PARSER_DEFINED

#include <openutils/heap-pair/heap-pair.hh>
#include <openutils/optional/optional.hh>
#include <openutils/sstring/sstring.hh>
#include "../out/out.hh"
#include "../help/help.h"

/// <summary>
/// FIRST -> --line
/// SECOND -> --tab
/// </summary>
static inline openutils::optional_t<openutils::heap_pair<bool, bool>> parse_argvs(const char **argv, std::size_t &skip_index)
{
    bool line = false, tab = false;
    std::size_t i = 0;
    while (*argv)
    {
        openutils::sstring args_i = *argv;
        if (args_i == "--line")
        {
            if (line == false)
            {
                line = true;
                i++;
            }
            else
            {
                std::fprintf(stderr, "err: cannot use `%s` flag two times, try using `--help`\r\n", args_i.c_str());
                std::exit(EXIT_FAILURE);
            }
        }
        else if (args_i == "--tab")
        {
            if (tab == false)
            {
                tab = true;
                i++;
            }
            else
            {
                std::fprintf(stderr, "err: cannot use `%s` flag two times, try using `--help`\r\n", args_i.c_str());
                std::exit(EXIT_FAILURE);
            }
        }
        else if (args_i == "--version")
        {
            std::fputs(version, stdout);
            return openutils::optnull;
        }
        else if (args_i == "--help")
        {
            std::fputs(help, stdout);
            return openutils::optnull;
        }
        else if (args_i == "--libs")
        {
            std::fputs(libs, stdout);
            return openutils::optnull;
        }
        else
        {
            if (out::is_file(args_i))
            {
                skip_index += i;
                break;
            }
            else
            {
                std::fprintf(stderr, "err: invalid flag `%s`, try using `--help`\r\n", args_i.c_str());
                std::exit(EXIT_FAILURE);
            }
        }
        argv++;
    }
    return openutils::heap_pair<bool, bool>(line, tab);
}

#endif