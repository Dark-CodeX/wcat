/**
 * @file main.cc
 * @author Tushar Chaurasia (Dark-CodeX)
 * @brief The C file is a part of https://github.com/Dark-CodeX/wcat.git, written for entry point.
 * @copyright Copyright (c) 2023 - Tushar Chaurasia
 * @license GNU General Public License v3.0
 */

#include "./help/help.h"
#include "./out/out.hh"
#include "./parser/parser.hh"
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#include <Windows.h>
#endif

int main(int argc, char const **argv)
{
    if (argc == 1)
    {
        std::fprintf(stderr, "err: no arguments were passed, try using `--help` flag.\r\n");
        std::exit(EXIT_FAILURE);
    }
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::size_t skip_index = 1;
    openutils::optional_t<openutils::heap_pair<bool, bool>> flags = parse_argvs(argv + skip_index, skip_index);
    if (!flags)
        return EXIT_SUCCESS;
    out __out__(argv + skip_index);
    for (std::size_t i = 0; i < __out__.length(); i++)
    {
        std::printf("\033[1;34m%s\033[0m:\r\n", __out__.loc_N(i).c_str());
        openutils::u8sstring &content = __out__.read_next();

        std::setvbuf(stdout, nullptr, _IOFBF, content.length());

        for (std::size_t j = 0, line_no = 1; j < content.length(); j++)
        {
            if (flags.get().second()) // tab
            {
                if (content[j] == u8'\t')
                {
                    std::printf("^I");
                    continue;
                }
            }
            std::putc(content[j], stdout);
            if (flags.get().first()) // line
            {
                if (content[j] == u8'\n')
                {
                    std::printf("%zu    ", line_no++);
                }
            }
        }
        std::fflush(stdout);
    }
    return EXIT_SUCCESS;
}
