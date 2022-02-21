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
    int skip = 1, print_ln = false, print_tab = false;
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
    if (skip == argc)
    {
        fprintf(stderr, "file input required after `--ln` flag\r\n");
        return 1;
    }
    init_wcat(&c, argv + skip, argc - skip);
    read_wcat(&c);
    print_wcat(&c, print_ln, print_tab);
    free_wcat(&c);
    return 0;
}
