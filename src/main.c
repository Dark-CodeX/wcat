/**
 * @file main.c
 * @author Tushar Chaurasia (Dark-CodeX)
 * @brief The C file is a part of https://github.com/Dark-CodeX/wcat.git, written for managing command line.
 * @copyright Copyright (c) 2022 - Tushar Chaurasia
 * @license GNU General Public License v3.0
 */

#include "./out/out.h"
#include "./help.h"

int main(int argc, char const **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "no input file was given\r\n");
        return 1;
    }
    out_wcat c;
    int skip = 1;
    bool print_ln = false, print_tab = false;
    if (argc >= 4)
    {
        if ((strcmp(argv[1], "--ln") == 0 && strcmp(argv[2], "--tab") == 0) ||
            (strcmp(argv[2], "--ln") == 0 && strcmp(argv[1], "--tab") == 0))
            print_ln = true, print_tab = true, skip += 2;
    }
    else
    {
        if (strcmp(argv[1], "--ln") == 0)
            print_ln = true, skip++;
        if (strcmp(argv[1], "--tab") == 0)
            print_tab = true, skip++;
        if (strcmp(argv[1], "--help") == 0)
        {
            puts(help);
            return 0;
        }
        if (strcmp(argv[1], "--v") == 0)
        {
            puts("wcat: v0.1\r\n");
            return 0;
        }
    }
    if (skip == argc)
    {
        fprintf(stderr, "input file required after `[OPTION]` flag\r\n");
        return 1;
    }
    init_wcat(&c, argv + skip, argc - skip);
    read_wcat(&c);
    print_wcat(&c, print_ln, print_tab);
    free_wcat(&c);
    return 0;
}
