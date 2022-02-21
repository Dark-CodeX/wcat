#include "./out/out.h"

int main(int argc, char const **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "no input file was given\r\n");
        return 1;
    }
    out_wcat c;
    int skip = 1, print_ln = false;
    if (strcmp(argv[1], "--ln") == 0)
        print_ln = true, skip++;
    if(skip == argc)
    {
        fprintf(stderr, "file input required after `--ln` flag\r\n");
        return 1;
    }
    init_wcat(&c, argv + skip, argc - skip);
    read_wcat(&c);
    print_wcat(&c, print_ln);
    free_wcat(&c);
    return 0;
}
