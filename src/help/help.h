/**
 * @file help.h
 * @author Tushar Chaurasia (Dark-CodeX)
 * @brief The header file is a part of https://github.com/Dark-CodeX/wcat.git, written for printing `--help`.
 * @copyright Copyright (c) 2023 - Tushar Chaurasia
 * @license GNU General Public License v3.0
 */

#ifndef HELP_DEFINED
#define HELP_DEFINED

#include <openutils/sstring/sstring.hh>
#include <openutils/vector/vector.hh>
#include <openutils/heap-pair/heap-pair.hh>
#include <openutils/optional/optional.hh>

static const char *help = "Usage: wcat [OPTION] <FILES>\r\n\r\n   --line        number all output line\r\n   --tab         display TAB characters as ^I\r\n   --help        display this help and exit\r\n   --version     display version and exit\r\n   --libs        shows libraries used in this project\r\n";
static const char *libs = "Copyright 2023 Tushar Chaurasia\n"
                          "    1. [sstring v" sstring_version "]      (https://github.com/Dark-CodeX/sstring.git)        Tushar Chaurasia\r\n"
                          "    2. [vector v" vector_t_version "]       (https://github.com/Dark-CodeX/vector.git)         Tushar Chaurasia\r\n"
                          "    3. [heap-pair v" heap_pair_version "]    (https://github.com/Dark-CodeX/heap-pair.git)      Tushar Chaurasia\r\n"
                          "    4. [optional v" optional_version "]     (https://github.com/Dark-CodeX/optional.git)       Tushar Chaurasia\r\n";

static const char *version = "wcat: v2.0.0\r\n";

#endif